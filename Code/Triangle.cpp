#include "Triangle.h"
#include <iostream>

Triangle::Triangle(vec3 a, vec3 b, vec3 c, Material *m) : Plane(normalize(cross(b - a, c - a)), a, m)
{

    // rebem tres punts per separat (així garantim que són tres) i els guardem
    // en un vector de vèrtexs
    vertices = std::vector<vec3>();
    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
}




bool Triangle::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    // primer comprovem que el raig impacti amb el pla del triangle,
    // en cas contrari mai impactarà amb el triangle
    if (Plane::hit(r, t_min, t_max, rec)){

        // enllaç de la fórmula per veure si el punt d'impacte amb el pla
        // pertany al triangle:
        // http://www.cs.princeton.edu/courses/archive/fall2000/cs426/lectures/raycast/sld018.htm

        vec3 rayOrigin = r.initialPoint();
        vec3 planeHitPoint = rec.p;

        vec3 vect1;
        vec3 vect2;

        // per cada parella aresta del triangle (és a dir cada parella de vèrtexs),
        // calculem els vectors resultants d'anar del punt d'origen del raig a
        // aquests vèrtexs, i mirarem en funció de cada aresta si es pot descartar
        // que pertanyi al triangle
        for (int i = 0; i < 3; i++){

            switch(i){

                case 0:
                    vect1 = vertices[0] - rayOrigin;
                    vect2 = vertices[1] - rayOrigin;
                    break;

                case 1:
                    vect1 = vertices[1] - rayOrigin;
                    vect2 = vertices[2] - rayOrigin;
                    break;

                case 2:
                    vect1 = vertices[2] - rayOrigin;
                    vect2 = vertices[0] - rayOrigin;
                    break;

                default: break;

            }

            // obtenim la normal determinada pels dos vectors
            vec3 norm = normalize(cross(vect2, vect1));

            // si l'operació algebraica dóna resultat negatiu, descartem
            // l'impacte amb el triangle
            float dist = dot(-rayOrigin, norm);
            if ((dot(planeHitPoint, norm) + dist) < 0){
                return false;
            }
        }

        return true;
    }

    return false;
}

