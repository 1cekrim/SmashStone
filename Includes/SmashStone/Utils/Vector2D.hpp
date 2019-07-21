#ifndef SMASHSTONE_UTILS_VECTOR2D_HPP
#define SMASHSTONE_UTILS_VECTOR2D_HPP

#include <ostream>
#include <cmath>

namespace SmashStone::Utils
{
template<class T>
class Vector2D
{
    template<class U>
    friend std::ostream& operator<<(std::ostream& stream, const Vector2D<U>& vec2d);
    template<class U>
    friend Vector2D<U> operator*(const U& lhs, const Vector2D<U>& rhs);

 public:
    T x_, y_;

    Vector2D() = delete;
    Vector2D(const T _x, const T _y);

    Vector2D(const Vector2D& vec2d);
    Vector2D& operator=(const Vector2D& rhs);
    Vector2D& operator+=(const Vector2D& rhs);
    Vector2D& operator-=(const Vector2D& rhs);
    Vector2D& operator*=(const T& rhs);
    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator-(const Vector2D& rhs) const;
    Vector2D operator/(const T& rhs) const;
    Vector2D operator*(const T& rhs) const;

    const bool operator==(const Vector2D& rhs) const;

    void Swap(Vector2D& rhs);

    const float Norm(const float& l) const;

    const T Dot(const Vector2D& rhs) const;

    Vector2D Normalized(void) const;
};
}  // namespace SmashStone::Utils

#include <SmashStone/Utils/Vector2D-impl.hpp>
#endif  // SMASHSTONE_UTILS_VECTOR2D_HPP