#pragma once

#include "../Core/DCoordinates3.h"

namespace cagd
{
namespace spiral_on_cone
{
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace viviani
{
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);

}

namespace lissajou
{
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace hypocycloid
{
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace cycloid
{
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace rose
{
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

namespace spring
{
extern GLdouble u_min, u_max;

DCoordinate3 d0(GLdouble);
DCoordinate3 d1(GLdouble);
DCoordinate3 d2(GLdouble);
}

//----------SURFACES----------------
namespace sphere {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

namespace tube {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

namespace paralelogram {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

namespace revolvingCurve {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);

}

namespace torus {
extern GLdouble u_min, u_max, v_min, v_max,a,b;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);
}

namespace cone {
extern GLdouble u_min, u_max, v_min, v_max;
DCoordinate3 d00(GLdouble, GLdouble);
DCoordinate3 d10(GLdouble, GLdouble);
DCoordinate3 d01(GLdouble, GLdouble);
}
}
