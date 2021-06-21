#include <iostream>
#include <string>
//#include "function.h"
using namespace std;

namespace oj
{
    class Shape3D
    {
        double volume;

    public:
        double getVolume();

    protected:
        void setVolume(double volume);
    };

    class Sphere : public Shape3D
    {
        double radius;
        double pi;

    public:
        Sphere(double, double);
    };

    class Cone : public Shape3D
    {
        double radius;
        double height;
        double pi;

    public:
        Cone(double, double, double);
    };

    class Cuboid : public Shape3D
    {
        double length;
        double width;
        double height;

    public:
        Cuboid(double, double, double);
    };

    class Cube : public Cuboid
    {
    public:
        Cube(double);
    };
}

namespace oj
{
    void Shape3D::setVolume(double v)
    {
        volume = v;
    }

    double Shape3D::getVolume()
    {
        return volume;
    }
}


oj::Sphere::Sphere(double radius, double pi){
    if(radius <= 0 || pi <= 0)   setVolume(0);
    else    setVolume(4*pi*radius*radius*radius/3);
}

oj::Cone::Cone(double radius, double height, double pi){
    if(radius <= 0 || height <= 0 || pi <= 0)    setVolume(0);
    else    setVolume(pi*radius*radius*height/3);
}

oj::Cuboid::Cuboid(double length, double width, double height){
    if(length <= 0 || width <= 0 || height <= 0)    setVolume(0);
    else    setVolume(length*width*height);
}

oj::Cube::Cube(double length) : Cuboid(length, length, length){
    if(length <= 0)    setVolume(0);
    else    setVolume(length*length*length);
}

int main(void)
{
    using namespace oj;

    string s;
    double a, b, c;
    double totalVolume = 0.0, totalPerimeter = 0.0;

    while(cin >> s) {
        if(s == "Sphere") {
            cin >> a >> b;
            Sphere sphere(a, b);
            totalVolume += sphere.getVolume();
            //cout << "Sphere : " << sphere.getVolume() << endl;
        }
        if(s == "Cone") {
            cin >> a >> b >> c;
            Cone cone(a, b, c);
            totalVolume += cone.getVolume();
            //cout << "Cone : " << cone.getVolume() << endl;
        }
        if(s == "Cuboid") {
            cin >> a >> b >> c;
            Cuboid cuboid(a, b, c);
            totalVolume += cuboid.getVolume();
            //cout << "Cuboid : " << cuboid.getVolume() << endl;
        }
        if(s == "Cube") {
            cin >> a;
            Cube cube(a);
            totalVolume += cube.getVolume();
            //cout << "Cube: " << cube.getVolume() << endl;
        }
        //if(s == "e") break;
    }

    cout << totalVolume << endl;

    return 0;
}
