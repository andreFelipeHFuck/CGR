#include "rapiobj.hpp"

#include <iostream>
#include <string>
#include <vector>

#include<GL/glut.h>

typedef struct point3D
{
    GLfloat x, y, z;
}Point3D;

using namespace std;


void printPoint(Point3D point){
    cout << point.x << ","
         << point.y << ","
         << point.z << endl;
}

vector<Point3D> readObjFile(string arq){
    rapidobj::Result result = rapidobj::ParseFile(arq);
    vector<Point3D> points;
    Point3D point;

    const int SIZE_POSITIONS = result.attributes.positions.size();
    for(int i=0; i<SIZE_POSITIONS; i+=3){
        point.x = result.attributes.positions[i];
        point.y = result.attributes.positions[i+1];
        point.z = result.attributes.positions[i+2];

        points.push_back(point);
    }

    return points;
}


