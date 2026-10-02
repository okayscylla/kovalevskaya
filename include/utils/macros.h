#pragma once

#define assertEqual(i, j)           (std::fabs((i) - (j)) < EPSILON)
#define notZero(i)                  (std::fabs(i) > EPSILON)
#define klog(...)                   (std::print("KOV: " __VA_ARGS__))

#define Translate(x, y, z)          Mat4({1,0,0,x,0,1,0,y,0,0,1,z,0,0,0,1})
#define Scale(x, y, z)              Mat4({x,0,0,0,0,y,0,0,0,0,z,0,0,0,0,1})
#define RotateX(r)                  Mat4({1,0,0,0,0,std::cosf(r),-(std::sinf(r)),0,0,std::sinf(r),std::cosf(r),0,0,0,0,1}) // TODO: implement scaling around arbitary line
#define RotateY(r)                  Mat4({std::cosf(r),0,std::sinf(r),0,0,1,0,0,-(std::sinf(r)),0,std::cosf(r),0,0,0,0,1})
#define RotateZ(r)                  Mat4({std::cosf(r),-(std::sinf(r)),0,0,std::sinf(r),std::cosf(r),0,0,0,0,1,0,0,0,0,1})