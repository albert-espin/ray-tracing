#include "BoundaryObject.h"
#include <unistd.h>

BoundaryObject::BoundaryObject(string s, Material *m) : Object(m)
{ 

  readObj(s);
  // Cal recorrer l'estructura de l'objecte segons cara-vertexs que es carrega

  // recorrem les cares i obtenim el seu equivalent en triangles
  for (Cara face : cares){

      // cal assegurar-se que la cara sigui un triangle (tingui tres vèrtexs)
      if (face.idxVertices.size() == 3){

          vec4 vert1 = vertexs[face.idxVertices[0]];
          vec4 vert2 = vertexs[face.idxVertices[1]];
          vec4 vert3 = vertexs[face.idxVertices[2]];
          vec3 a = vec3(vert1.x, vert1.y, vert1.z);
          vec3 b = vec3(vert2.x, vert2.y, vert2.z);
          vec3 c = vec3(vert3.x, vert3.y, vert3.z);
          triangles.push_back(new Triangle(a, b, c, m));

      }
  }


  vertexs.clear();
  cares.clear();
}

BoundaryObject::~BoundaryObject() {

    for (Triangle * triangle : triangles){

        delete triangle;
    }
}

bool BoundaryObject::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    bool hasEverIntersected = false;

    HitInfo bestHitInfo;

    // recorrem tots els triangles de la malla, i ens quedem amb el punt d'intersecció
    // més proper (menor t)
    for (Triangle * triangle : triangles){

        if (triangle->hit(r, t_min, t_max, rec)){

            hasEverIntersected = true;

            if (rec.t < bestHitInfo.t){
                bestHitInfo = rec;
            }
        }
    }

    if (hasEverIntersected){
        rec = bestHitInfo;
    }

    return hasEverIntersected;
}

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
void BoundaryObject::readObj(string filename){

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    cout << "DIRECTORI ACTUAL: " << cwd;

    FILE *fp = fopen(filename.c_str(),"r");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                string sx(ReadFile::words[1]);
                string sy(ReadFile::words[2]);
                string sz(ReadFile::words[3]);
                double x = atof(sx.c_str());
                double y = atof(sy.c_str());
                double z = atof(sz.c_str());

                if (nwords == 5) {
                    string sw(ReadFile::words[4]);
                    double w = atof(sw.c_str());
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(vec4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara (&ReadFile::words[1], nwords-1, this, 0);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }
    fclose(fp);
}

/**
 * @brief BoundaryObject::construeix_cara
 * @param words
 * @param nwords
 * @param objActual
 * @param vindexUlt
 */
void BoundaryObject::construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9')) {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(objActual->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}
