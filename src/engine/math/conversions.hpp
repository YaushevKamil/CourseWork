#ifndef MATH_CONVERSIONS_HPP
#define MATH_CONVERSIONS_HPP

namespace math {
    const float PI  = 3.14159265359f;
    const float TAU = 6.28318530717f;
    const float degToRad = PI / 180.0f;
    const float radToDeg = 180.0f / PI;
    const float kEpsilon = 1E-06f;

    inline float Deg2Rad(float degrees) {
        return degrees * degToRad;
    }
    inline double Deg2Rad(double degrees) {
        return degrees * degToRad;
    }

    inline float Rad2Deg(float radians) {
        return radians * radToDeg;
    }
    inline double Rad2Deg(double radians) {
        return radians * radToDeg;
    }
}

#endif //MATH_CONVERSIONS_HPP
