#ifndef SMASHSTONE_UTILS_VECTOR2D_HPP
#define SMASHSTONE_UTILS_VECTOR2D_HPP

namespace SmashStone::Utils
{
template<class T>
class Vector2D
{
    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec2d);
    friend Vector2D operator*(const int& lhs, const Vector2D& rhs);
    friend Vector2D operator*(const Vector2D& lhs, const int& rhs);
public:
    T x_, y_;

    Vector2D();
    Vector2D(const T _x, const T _y);

    Vector2D(const Vector2D& vec2d);
    Vector2D& operator=(const Vector2D& rhs);

    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator-(const Vector2D& rhs) const;

    Vector2D(Vector2D&& vec2d) = delete;

    ~Vector2D();

    static void Swap(Vector2D& rhs);

    const float Norm(const float& l) const;
};
}  // namespace SmashStone::Utils
#endif  // SMASHSTONE_UTILS_VECTOR2D_HPP