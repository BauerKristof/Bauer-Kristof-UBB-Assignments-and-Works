#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

//---Spiral on cone curve---//

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0.0);
}


//---Viviani's Curve---//
GLdouble viviani::u_min = -TWO_PI;
GLdouble viviani::u_max = TWO_PI;

DCoordinate3 viviani::d0(GLdouble u)
{
    return DCoordinate3(2 * (1 + cos(u)), 2 * sin(u), 4 * sin(u / 2));
}

DCoordinate3 viviani::d1(GLdouble u)
{
    return DCoordinate3(-2 * sin(u), 2 * cos(u), 2 * cos(u / 2));
}

DCoordinate3 viviani::d2(GLdouble u)
{
    return DCoordinate3(-2 * cos(u), -2 * sin(u), -1 * sin(u / 2));
}

//-Lissajou's Curve--//


GLdouble lissajou::u_min = -1.0;
GLdouble lissajou::u_max = +1.0;

DCoordinate3 lissajou::d0(GLdouble u)
{
    return DCoordinate3(sin(5.0*u + 1.5707), sin(4.0*u), u);
}

DCoordinate3 lissajou::d1(GLdouble u)
{
    return DCoordinate3(5.0*cos(5.0*u + 1.5707), 4.0*cos(4.0*u), 1.0);
}

DCoordinate3 lissajou::d2(GLdouble u)
{
    return DCoordinate3(-25.0*sin(5.0*u + 1.5707), -16.0*sin(4.0*u), 0.0);
}

//---HypoCycloid Curve---//


GLdouble hypocycloid::u_min = -3.0;
GLdouble hypocycloid::u_max = +3.0;

DCoordinate3 hypocycloid::d0(GLdouble u)
{
    return DCoordinate3(5.0*cos(u)+cos(5.0*u), 5.0*sin(u)-sin(5.0*u), u);
}

DCoordinate3 hypocycloid::d1(GLdouble u)
{
    return DCoordinate3(-5.0*sin(u)-5.0*sin(5.0*u), 5.0*cos(u)-5.0*cos(5.0*u), 1.0);
}

DCoordinate3 hypocycloid::d2(GLdouble u)
{
    return DCoordinate3(-5.0*cos(u)-25.0*cos(5.0*u), -5.0*sin(u)+25.0*sin(5.0*u), 0.0);
}


//---Simple Cycloid Curve---//
GLdouble cycloid::u_min = 0.0;
GLdouble cycloid::u_max = 125.1324;

DCoordinate3 cycloid::d0(GLdouble u)
{
    return DCoordinate3(2.0*(u-sin(u)), 2.0*(1.0-cos(u)), u);
}

DCoordinate3 cycloid::d1(GLdouble u)
{
    return DCoordinate3(2.0*(1.0-cos(u)), 2.0*sin(u), 1.0);
}

DCoordinate3 cycloid::d2(GLdouble u)
{
    return DCoordinate3(sin(u), 2.0*cos(u), 0.0);
}

//---Rose Curve---//

GLdouble rose::u_min = -3.14;
GLdouble rose::u_max = 3.14;

DCoordinate3 rose::d0(GLdouble u)
{
    return DCoordinate3((1 / 2 + cos(3 * u)) * cos(u),
                        (1 / 2 + cos(3 * u)) * sin(u));
}

DCoordinate3 rose::d1(GLdouble u)
{
    return DCoordinate3(-3 * sin(3 * u) * cos(u) - sin(u) * (1 / 2 * cos(3 * u)),
                        -3 * sin(3 * u) * sin(u) + cos(u) * (1 / 2 + cos(3 * u)));
}

DCoordinate3 rose::d2(GLdouble u)
{
    return DCoordinate3(-3 * (3 * cos(3 * u) * cos(u) - sin(u) * sin(3 * u)) - 1 * cos(u) * (1 / 2 + cos(3 * u)) + 3 * sin(u) * sin(u),
                        -3 * (3 * cos(3 * u) * sin(u)) + sin(3 * u) * cos(u) -1 * sin(u) * (1 / 2 + cos(3 * u)) - 3 * cos(u) * sin(3 * u));
}

//---Spring Curve---//

GLdouble spring::u_min = -3.14;
GLdouble spring::u_max = +3.14;

DCoordinate3
spring::d0(GLdouble u)
{
    return DCoordinate3(u, cos(2 * u), sin(2 * u));
}

DCoordinate3
spring::d1(GLdouble u)
{
    return DCoordinate3(1.0, -2 * sin(2 * u), 2 * cos(2 * u));
}

DCoordinate3
spring::d2(GLdouble u)
{
    return DCoordinate3(0, -4 * cos(2 * u), -4 * sin(2 * u));
}

//------------SURFACES-------------------------

GLdouble sphere::u_min = 0;
GLdouble sphere::u_max = PI;
GLdouble sphere::v_min = 0;
GLdouble sphere::v_max = TWO_PI;

DCoordinate3
sphere::d00(GLdouble u, GLdouble v)
{

  return DCoordinate3(sin(u) * cos(v), sin(u) * sin(v), cos(u));
}

DCoordinate3
sphere::d10(GLdouble u, GLdouble v)
{

  return DCoordinate3(cos(v) * cos(u), cos(u) * sin(v), -1 * sin(u));
}

DCoordinate3
sphere::d01(GLdouble u, GLdouble v)
{

  return DCoordinate3(-1 * sin(v) * sin(u), sin(u) * cos(v), 0);
}

//-----------------------------

GLdouble tube::u_min = -0;
GLdouble tube::u_max = 3;
GLdouble tube::v_min = 0;
GLdouble tube::v_max = TWO_PI;

DCoordinate3
tube::d00(GLdouble u, GLdouble v)
{

  return DCoordinate3(2 * sin(v), 2 * cos(v), u);
}

DCoordinate3
tube::d10(GLdouble u, GLdouble v)
{

  return DCoordinate3(0, 0, 1);
}

DCoordinate3
tube::d01(GLdouble u, GLdouble v)
{

  return DCoordinate3(2 * cos(v), -2 * sin(v), 0);
}

//--------------------------------------

GLdouble paralelogram::u_min = -1;
GLdouble paralelogram::u_max = 1;
GLdouble paralelogram::v_min = -1;
GLdouble paralelogram::v_max = 1;

DCoordinate3
paralelogram::d00(GLdouble u, GLdouble v)
{

  return DCoordinate3(u, v, u * v);
}

DCoordinate3
paralelogram::d10(GLdouble u, GLdouble v)
{

  return DCoordinate3(1, 0, v);
}

DCoordinate3
paralelogram::d01(GLdouble u, GLdouble v)
{

  return DCoordinate3(0, -2 * sin(v), 2 * cos(v));
}

//--------------------------------------

GLdouble revolvingCurve::u_min = -PI;
GLdouble revolvingCurve::u_max = PI;
GLdouble revolvingCurve::v_min = -PI;
GLdouble revolvingCurve::v_max = PI;

DCoordinate3
revolvingCurve::d00(GLdouble u, GLdouble v)
{

  return DCoordinate3(cos(u) * cos(v), u, cos(u) * sin(v));
}

DCoordinate3
revolvingCurve::d10(GLdouble u, GLdouble v)
{

  return DCoordinate3(cos(v) * -1 * sin(u), 1, -sin(u) * sin(v));
}

DCoordinate3
revolvingCurve::d01(GLdouble u, GLdouble v)
{

  return DCoordinate3(cos(u) * -1 * sin(v), 0, cos(u) * cos(v));
}

//--------------------------------

GLdouble torus::u_min = 0;
GLdouble torus::u_max = TWO_PI;
GLdouble torus::v_min = 0;
GLdouble torus::v_max = TWO_PI;

GLdouble torus::a = TWO_PI;
GLdouble torus::b = PI;

DCoordinate3 torus::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((a+b*cos(u))*cos(v), b*sin(u), (a+b*cos(u))*sin(v));
}

DCoordinate3 torus::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-b*cos(v)*sin(u), b*cos(u), -b*sin(v)*sin(u));
}

DCoordinate3 torus::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-(b*cos(u)+a)*sin(v), 0, (b*cos(u)+a)*cos(v));
}
//-------------------------------
GLdouble cone::u_min = 1;
GLdouble cone::u_max = TWO_PI;
GLdouble cone::v_min = 1;
GLdouble cone::v_max = TWO_PI;

DCoordinate3 cone::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((1-v)*cos(TWO_PI*u), (1-v)*sin(TWO_PI*u), v);
}

DCoordinate3 cone::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-TWO_PI*(1-v)*sin(TWO_PI*u), TWO_PI*(1-v)*cos(TWO_PI*u), 0);
}

DCoordinate3 cone::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-cos(TWO_PI*u), -sin(TWO_PI*u), 1);
}
