#ifndef MATH_H
#define MATH_H
#include <algorithm>
#include <cmath>
namespace Core {
class Math {
public:
    template<typename T>
    static inline T lerp(T a, T b, T t) {
       return  a + t * (b - a);
    }

    inline float dbToLinear(float dB) {
        if(dB <= -96.0f) return 0.0f;
        return powf(10.0f, dB / 20.0f);
    }

    template <typename T>
    inline T clamp(T min, T max, T val) {
        return std::max(min, std::min(max, val));
    }

};
}
#endif // MATH_H
