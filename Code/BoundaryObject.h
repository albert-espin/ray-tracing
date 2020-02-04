#ifndef BOUNDARYOBJECT_H
#define BOUNDARYOBJECT_H

#include <vector>


#include <iostream>
#include <string.h>

#include "Object.h"
#include "Cara.h"
#include "ReadFile.h"
#include "Triangle.h"

using namespace std;

// Classe que representa una malla de cares a l'espai
class BoundaryObject : public Object
{
public:
    BoundaryObject(string s, Material *m);
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    virtual ~BoundaryObject();

private:


    string nom;
    vector<Cara> cares; // cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits

    // triangles que formen la malla
    vector<Triangle *> triangles;

    void readObj(string filename);
    void construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt);

};

#endif // BOUNDARYOBJECT_H
