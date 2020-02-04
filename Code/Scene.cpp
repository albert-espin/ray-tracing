#include "Scene.h"

Scene::Scene()
{
    // variables per definir la càmera
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;

    // mida de finestra en píxels
    int pixelsX = 600;
    int pixelsY = 400;

    // creació de la càmera
    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);

   // TODO: Cal crear els objectes de l'escena
    RandomScene();

    // TODO: Cal afegir llums a l'escena (Fase 2)
    setUpLights();
}

Scene::~Scene()
{
    for(unsigned int i = 0; i < objects.size(); ++i){

        if(objects[i]){

            if (dynamic_cast<Sphere*>(objects[i]))
                    delete (Sphere *)(objects[i]);

            else if (dynamic_cast<Plane*>(objects[i]))
                delete (Plane *)(objects[i]);

            else if (dynamic_cast<Triangle*>(objects[i]))
                delete (Triangle *)(objects[i]);

            else if (dynamic_cast<Cube*>(objects[i]))
                delete (Cube *)(objects[i]);

            else if (dynamic_cast<BoundaryObject*>(objects[i]))
                delete (BoundaryObject *)(objects[i]);

            else if (dynamic_cast<Volume*>(objects[i]))
                delete (Volume *)(objects[i]);
        }
    }


    for (Light * light : lights){

        if (light){

            if (dynamic_cast<PointLight*>(light))
                    delete (PointLight *)(light);
        }
    }

    delete cam;
}

// TODO: Metode que genera una escena random de numObjects de tipus esfera, a diferents posicions,
// amb diferents radis i diferents materials. S'usa drand48 per generar numeros random

void Scene::RandomScene() {

    // DISPOSICIÓ D'OBJECTES PER A LA FASE 1

    /*
    // creació d'esferes
    objects.push_back(new Sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(0.5, 0.2, 0.7))));
    objects.push_back(new Sphere(vec3(0,-1,-1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5))));
    objects.push_back(new Sphere(vec3(1,-1,-1), 0.5, new Lambertian(vec3(0.8, 0.6, 0.2))));
    objects.push_back(new Sphere(vec3(-1,-1,-1), 0.5, new Lambertian(vec3(0.6, 0.8, 0.2))));
    objects.push_back(new Sphere(vec3(-1,0,-1), -0.45, new Lambertian(vec3(0.2, 0.6, 0.8))));
    //objects.push_back(new Sphere(vec3(-2.7,0,0), 2, new Lambertian(vec3(0.2, 0.6, 0.8))));

    // creació de plans
    //objects.push_back(new Plane(vec3(1, 0, 0), vec3(5,0,0), new Lambertian(vec3(0.5, 0.2, 0.7))));
    //objects.push_back(new Plane(vec3(0, 1, 0), vec3(5,0,0), new Lambertian(vec3(0.5, 0.2, 0.7))));
    //objects.push_back(new Plane(vec3(0, 0, 1), vec3(5,-20,0), new Lambertian(vec3(0.5, 0.2, 0.7))));

    // creació de triangles
    objects.push_back(new Triangle(vec3(-1,-2,2), vec3(1,-2,2), vec3(2,2,2), new Lambertian(vec3(0.5, 0.2, 0.7))));
    objects.push_back(new Triangle(vec3(-4,0,-1), vec3(3,0,2), vec3(7,0,0), new Lambertian(vec3(0.5, 0.2, 0.7))));
    //objects.push_back(new Triangle(vec3(-1,0,-1), vec3(1,0,2), vec3(3,0,0), new Lambertian(vec3(0.5, 0.2, 0.7))));
    //objects.push_back(new Triangle(vec3(-100,100,0), vec3(100,10,0), vec3(100,100,0), new Lambertian(vec3(0.5, 0.2, 0.7))));
    //objects.push_back(new Triangle(vec3(0,100,200), vec3(0,1000,300), vec3(0,500,300), new Lambertian(vec3(0.5, 0.2, 0.7))));

    // creació de cubs
    objects.push_back(new Cube(vec3(-5,-1,-1), vec3(-3,1,1), new Lambertian(vec3(0.2, 0.6, 0.8))));
    */
    // creació d'una malla
    //objects.push_back(new BoundaryObject("../P1/resources/peo1K.obj", new Lambertian(vec3(0.5, 0.5, 0.5), vec3(0.2, 0.2, 0.2), vec3(1, 1, 1), 1.f, 10.f)));

    //objects.push_back(new Triangle(vec3(-4,0,-1), vec3(3,0,2), vec3(7,0,0), new Lambertian(vec3(0.5, 0.2, 0.7))));
    //objects.push_back(new Cube(vec3(-5,-1,-1), vec3(-3,1,1), new Lambertian(vec3(0.2, 0.6, 0.8))));


    // DISPOSICIÓ D'OBJECTES PER A LA FASE 2

    /*
    objects.push_back(new Sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(0.5, 0.5, 0.5), vec3(0.2, 0.2, 0.2), vec3(1, 1, 1), 1.f, 10.f)));
    objects.push_back(new Sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(0.8, 0.8, 0.0), vec3(0.2, 0.2, 0.2), vec3(1, 1, 1), 1.f, 10.f)));

    // esfera metàl·lica
    objects.push_back(new Sphere(vec3(-3, 1, 1), 1.0, new Metal(vec3(0.7, 0.6, 0.5), vec3(0.2, 0.2, 0.2), vec3(0.7, 0.7, 0.7), 1.f, 10.f)));

    float nt = 1.5f;
    float ni = 1.f;
    float nit = ni/nt;
    // esfera transparent
    //objects.push_back(new Sphere(vec3(0, 1, 0), 1.0, new Transparent(vec3(1, 1, 1), nit)));

    // esfera transparent amb tots els altres atributs
    objects.push_back(new Sphere(vec3(0, 1, 0), 1.0, new Transparent(vec3(1, 1, 1), nit, vec3(0.7, 0.6, 0.5), vec3(0.2, 0.2, 0.2), vec3(0.7, 0.7, 0.7), 1.f, 10.f)));
    */


    // DISPOSICIÓ D'OBJECTES PER A LA FASE 3
    /*
    // esferes
    objects.push_back(new Sphere(vec3(0, 1, 0), 1.0, new Transparent(vec3(1, 1, 1), 1.f/1.5f)));
    objects.push_back(new Sphere(vec3(- 2.5, 1, 0.5),1.0,new Lambertian ( vec3 ( 0.8,0.2,0.1))));
    objects.push_back(new Sphere( vec3(1,1,-2 ), 1.f,new Metal(vec3( 0.4,0.4, 0.4), vec3(0.7 , 0.5,0.15 ), vec3(0.5), 1.f, 75.0f)));
    objects.push_back(new Sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(0.8, 0.8, 0.0), vec3(0.2, 0.2, 0.2), vec3(1, 1, 1), 1.f, 10.f)));

    // cub
    //objects.push_back(new Cube(vec3(-5,-1,-1), vec3(-3,1,1), new Lambertian(vec3(0.2, 0.6, 0.8))));

    // volum
    objects.push_back(new Volume(2, 2, 2, 40, new Isotropic(new TextureConstant(2, 2, 2, vec3(0.7, 0.7, 0.7)))));
    //objects.push_back(new Volume(2, 2, 2, 40, new Isotropic(new TextureChecker(2, 2, 2, vec3(1, 0.2, 0.2), vec3(0.2, 0.2, 1)))));
    */

    // DISPOSICIÓ D'OBJECTES PER A LES VISUALITZACIONS FINALS DE LA PRÀCTICA


    // ESCENA 1
    /*objects.push_back(new Plane(vec3(1, 0, 0), vec3(0,0,0), new Metal(vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.8), vec3(0.2, 0.2, 0.2), 1.f, 10.f)));
    objects.push_back(new Plane(vec3(0, 1, 0), vec3(0,0,0), new Metal(vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), 1.f, 10.f)));
    objects.push_back(new Plane(vec3(0, 0, 1), vec3(0,0,0), new Metal(vec3(0.8, 0.8, 0.8), vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.8), 1.f, 10.f)));
    objects.push_back(new Sphere(vec3(2,1,2), 0.5, new Metal(vec3(0.1, 0.8, 0.8), vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.8), 1.f, 10.f)));
    objects.push_back(new Sphere(vec3(3,2,3), 0.7, new Lambertian(vec3(0.8, 0.8, 0.0), vec3(0.2, 0.2, 0.2), vec3(1, 1, 1), 1.f, 10.f)));
    objects.push_back(new Sphere(vec3(0,0,0), 0.7, new Lambertian(vec3(0.8, 0.3, 0.0), vec3(0.2, 0.2, 0.2), vec3(0.3, 0.3, 0.3), 1.f, 10.f)));
    */

    // ESCENA 2
    // esferes
    objects.push_back(new Sphere(vec3(0, 1, 0), 1.0, new Transparent(vec3(1, 1, 1), 1.f/1.5f)));
    objects.push_back(new Sphere(vec3(- 2.5, 1, 0.5),1.0,new Lambertian ( vec3 ( 0.8,0.2,0.1))));
    objects.push_back(new Sphere( vec3(1,1,-2 ), 1.f,new Metal(vec3( 0.4,0.4, 0.4), vec3(0.7 , 0.5,0.15 ), vec3(0.5), 1.f, 75.0f)));
    objects.push_back(new Sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(0.8, 0.8, 0.0), vec3(0.2, 0.2, 0.2), vec3(1, 1, 1), 1.f, 10.f)));
    objects.push_back(new Sphere(vec3(1, 2, -2), 1.3, new Transparent(vec3(1, 1, 1), 1.f/1.2f)));
    objects.push_back(new Sphere(vec3(1, 2, 2.5), 1.3, new Transparent(vec3(1, 1, 1), 1.f/1.8f)));


    // cubs
    objects.push_back(new Cube(vec3(-5,-1,-1), vec3(-3,1,1), new Lambertian(vec3(0.2, 0.6, 0.8))));
    objects.push_back(new Cube(vec3(-5,-1,2), vec3(-3,1,8), new Metal(vec3(0.2, 0.6, 0.8), vec3(0.7 , 0.5,0.15 ), vec3(0.5), 1.f, 75.0f)));

    // triangles
    objects.push_back(new Triangle(vec3(-4,0,-1), vec3(3,0,2), vec3(7,0,0), new Metal(vec3(0.5, 0.2, 0.7),vec3(0.7 , 0.5,0.15 ), vec3(0.5), 1.f, 75.0f)));
}

/*
** TODO: Metode que testeja la interseccio contra tots els objectes de l'escena (Fase 1)
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {

    // TODO: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode hit per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig,
    // pero no en aquesta funcio.


    // En aquest mètode processem els hits amb l'escena del raig passat per paràmetre, tenint en compte
    // el rang de t a evaluar. Es retorna true si s'intersecciona amb algun objecte, false en cas contrari.
    // Si hi ha intersecció, ens quedarem amb la més propera (i.e. t més petita), ja que és la que primer
    // toparia amb el raig cronològicament; la seva informació serà accessible fora del mètode ja que se
    // sobreescriurà la referència de hitInfo passada per paràmetre amb la informació de l'impacte

    //primer suposem que no hi ha hit
    bool anyHitOccurred = false;

    //creem un nou hitInfo per trobal la intersecció més propera, que per defecte s'inicialitza amb t
    // amb valor pràcticament infinit, de manera que l'anirem actualitzant quan tinguem hits més propers
    HitInfo bestInfo;

    //es recorren tots els objectes
    for (Object *obj : objects) {

        //si trobem un hit actualitzem els valor si escau
        if (obj->hit(raig, t_min, t_max, info)) {

            // indiquem que s'ha produït un hit
            anyHitOccurred = true;

            //s'actualitza el valor quan trobem un hit més proper
            if (info.t < bestInfo.t) {
                bestInfo = info;
            }
        }
    }

    //s'actualitza la info del hit (si hi ha hagut algun), que podrà ser accedida fora
    // d'aquesta funció ja que s'assigna a la referència passada
    if (anyHitOccurred){
        info = bestInfo;
    }

    return anyHitOccurred;
}



void Scene::setUpLights(){

    // es configura la llum d'ambient global
    vec3 ambient = vec3(.01, .01, .01);
    setAmbientLight(ambient);

    // afegim una llum puntual
    lights.push_back(new PointLight(vec3(2.,8.,10.), vec3(.4, .4, .4), vec3(.5, .5, .5), vec3(1., 1., 1.), .5, 0, .01));


}

void Scene::setAmbientLight(vec3 & ambient){
    globalAmbientLightIntensity = ambient;
}




/*
** TODO: Funcio ComputeColor es la funcio recursiva del RayTracing.
** A modificar en la Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** A modificar en la Fase 2 per a tractar reflexions
**
*/


vec3 Scene::ComputeColor (Ray &ray, int depth) {

    vec3 color;


    /* TODO: Canviar aquesta assignacio pel color basat amb la il.luminacio basada amb Phong-Blinn segons
     * el material de l'objecte i les llums per la fase 2 de la practica
     * En aquestesta fase 2,  cal fer que tambe es tinguin en compte els rebots de les reflexions.

       Inicialment s'ha posat la direccio del raig per tenir un color diferents per a cada pixel pero
       hitInfo ha d'anar tenint el color actualitzat segons els rebots.
    */


    //informació de la intersecció
    HitInfo *hitInfo = new HitInfo();

    //indica si ha ocorregut, o no, un hit (per evitar surface acne, afegim un epsilon
    // a partir de la segona crida recursiva)
    bool anyHitOccurred = hit(ray, (depth == 0) ? T_MIN : T_MIN + EPSILON, T_MAX, *hitInfo);

    //si hi ha hit generem el color de diferent manera
    if (anyHitOccurred) {

        vec3 point = hitInfo->p;
        vec3 normal = hitInfo->normal;
        const Material * material = hitInfo->mat_ptr;

        // es comprova que el depth és inferior o igual al màxim establert
        if (depth <= MAXDEPTH) {

            color = blinnPhong(point, normal, material, true);

            // apliquem reflexió/refracció

                // es crea el nou raig secundari
                Ray secondaryRay;

                // factor obtingut (K de reflexió/refracció)
                vec3 secondaryFactor;

                // s'utilitza el mètode scatter del material per configurar el raig secundari
                material->scatter(ray, *hitInfo, secondaryFactor, secondaryRay);

                color += secondaryFactor * ComputeColor(secondaryRay, depth + 1);
        }


    //si no hi ha hit posem el degradat
    } else {

        /*//la nostra t serà l'eix y
        float t = ray.direction.y;

        //color de sortida
        vec3 startColor(0.5f, 0.7f, 1.f);

        //càlcul del degradat
        color = 0.5f * (((1.f - t) * startColor) + 1.f);*/

        // establim un color de fons fixe
        color = vec3(.75,.87,1);
    }


    //alliberem memòria
    delete hitInfo;

    return color;
}




vec3 Scene::blinnPhong(vec3 point, vec3 normal, const Material * material, bool ombra){

    // intensitat de llum que resultarà d'acumular els components difús, ambient i especular
    vec3 resultIntensity(0, 0, 0);

    // S'aplica la intensitat vde llum ambient global: Ka * Ia_global
    resultIntensity += material->getAmbient() * globalAmbientLightIntensity;

    // es recorren totes les llums de l'escena i les tenim en compte per la il·luminació
    // (les components ambient, difusa, especular)
    for (Light * light : lights){

        // vector del punt a la llum
        vec3 surfaceToLightVect(light->getPosition() - point);

        // distància del punt d'intersecció a la llum
        float dist = length(surfaceToLightVect);

        // L: vector del punt a la llum normalitzat
        surfaceToLightVect = normalize(surfaceToLightVect);

        // raig de la superfície de a la llum
        Ray * rayToLight = new Ray(point, surfaceToLightVect);

        // factor d'ombra
        float shadowFactor;

        // si no hem de calcular ombres, no hi haurà cap enfosquiment
        if (!ombra) shadowFactor = 1.f;

        // en cas contrari computem el factor fent servir el raig a la llum
        else{

            // T del raig del punt a la llum: serà la nostra T màxima, ja que no volem
            // mirar més enllà de la llum
            float light_T = length((light->getPosition() - point) / surfaceToLightVect);

            shadowFactor = computeShadowFactor(*rayToLight, light_T);
        }


        // contribució en ambient: Ka * Ia
        vec3 iterAmbient = material->getAmbient() * light->getAmbient();

        // contribució en difús: Kd * Id
        vec3 iterDiffuse = material->getDiffuse() * light->getDiffuse() * std::max<float>(0.f, dot(surfaceToLightVect, normal));

        // V: vectod des de la superfície a la càmera
        vec3 surfaceToCameraVect = normalize(cam->origin - point);

        // H: vector entre el vector a la llum i el vector a la càmera (L + V)
        vec3 inBetweenVectorLV = normalize(surfaceToLightVect + surfaceToCameraVect);

        // contribució en especular: Ks * Is * dot(N, H)^shininess
        vec3 iterSpecular = material->getSpecular() * light->getSpecular() * pow(std::max<float>(0.f, dot(normal, inBetweenVectorLV)), material->getShininess());

        // intensitat de la llum de la iteració actual, que contribuirà a la global
        // amb un factor d'atenuació per distància; la part ambient s'aplica sempre
        // igual, però l'especular i la difosa està afectada pel factor d'ombra
        vec3 iterIntensity = iterAmbient + shadowFactor * (iterDiffuse + iterSpecular);


        // s'aplica el factor d'atenuació a l'hora d'afegir la intensitat de la llum
        // de la iteració a la de l'escena
        resultIntensity += light->obtainAttenuationFactorAtDistance(dist) * iterIntensity;


        // s'elimina el raig creat per detectar ombres
        delete rayToLight;
    }



    return resultIntensity;
}



float Scene::computeShadowFactor(Ray & pointToLightRay, float light_T){

    HitInfo lightHitInfo;

    // determinem si s'impacta amb un objecte en anar del punt d'origen del raig a la llum
    bool isLightBlockedByObject = hit(pointToLightRay, T_MIN + EPSILON, light_T, lightHitInfo);

    // TODO: amb transparències, calcular amb un procediment el factor


    return isLightBlockedByObject ? 0.f : 1.f;

}









