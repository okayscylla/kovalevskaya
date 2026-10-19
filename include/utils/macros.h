#pragma once

#define assertEqual(i, j)                       (std::fabs((i) - (j)) < EPSILON)
#define notZero(i)                              (std::fabs(i) > EPSILON)
#define isZero(i)                               (std::fabs(i) < EPSILON)
#define lessThanZero(i)                         ((std::fabs(i) > EPSILON) && (i < 0.f))
#define moreThanZero(i)                         ((std::fabs(i) > EPSILON) && (i > 0.f))

#define klog(...)                               (std::print("KOV: " __VA_ARGS__))

#define Translate(x, y, z)                      Mat4({1,0,0,x,0,1,0,y,0,0,1,z,0,0,0,1})
#define Scale(x, y, z)                          Mat4({x,0,0,0,0,y,0,0,0,0,z,0,0,0,0,1})
#define Shear(x_y, x_z, y_x, y_z, z_x, z_y)     Mat4({1,x_y,x_z,0,y_x,1,y_z,0,z_x,z_y,1,0,0,0,0,1})
#define RotateX(r)                              Mat4({1,0,0,0,0,std::cosf(r),-(std::sinf(r)),0,0,std::sinf(r),std::cosf(r),0,0,0,0,1}) // TODO: implement scaling around arbitary line
#define RotateY(r)                              Mat4({std::cosf(r),0,std::sinf(r),0,0,1,0,0,-(std::sinf(r)),0,std::cosf(r),0,0,0,0,1})
#define RotateZ(r)                              Mat4({std::cosf(r),-(std::sinf(r)),0,0,std::sinf(r),std::cosf(r),0,0,0,0,1,0,0,0,0,1})

#define White                                   Colour(1,1,1)
#define Black                                   Colour(0,0,0)

#define DefaultWorld                            World({new Sphere(0,Material(Colour(0.8,1.0,0.6),0.1,0.7,0.2,200)),&(new Sphere(1))->transform(Scale(0.5,0.5,0.5))},{new PointLight(Point(-10,10,-10))})