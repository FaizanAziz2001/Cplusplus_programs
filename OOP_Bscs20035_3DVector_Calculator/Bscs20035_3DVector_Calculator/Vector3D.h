#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class Vector3D
{
    double x, y, z;

public:
    Vector3D(double tx = 0, double ty = 0, double tz = 0);
    void print();
    void ReadValues(ifstream& Rdr); // should read from file
    void init(double a, double b, double c);
    void PrintAddress();
    double Magnitude();   // sqrt(x*x + y*y + z*z)
    Vector3D UnitVector(); // x /mag , y/mag , z/mag
    Vector3D Add(Vector3D V);
    Vector3D Subtract(Vector3D V);
    Vector3D CrossProduct(Vector3D V);
    double DotProduct(Vector3D V);
    static Vector3D UnitX();   // return (1,0,0) 
    static Vector3D UnitY();   // return (0,1,0)
    static Vector3D UnitZ();   // return (0,0,1)
    Vector3D ProjectionAtV(Vector3D V);
    double Area_Parrallelogram(Vector3D V);
    double Area_Traingle(Vector3D V);
    ~Vector3D();
};
