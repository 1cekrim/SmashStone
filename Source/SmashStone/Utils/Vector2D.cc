#include <SmashStone/Utils/Vector2D.hpp>

#include <iostream>
#include <cmath>

namespace SmashStone::Utils
{
template<class T>
Vector2D<T>::Vector2D(const T _x, const T _y) : x_(_x), y_(_y)
{
    // Do nothing
}

Vector2D<float>::Vector2D() : Vector2D(0.0f, 0.0f)
{
    // Do nothing
}

template<class T>
Vector2D<T>::Vector2D(const Vector2D& vec2d) : Vector2D(vec2d.x_, vec2d.y_)
{
    // Do nothing
}

template<class T>
Vector2D<T>& Vector2D<T>::operator=(const Vector2D& rhs)
{
    Vector2D<T> temp(rhs);

    Swap(temp);

    return *this;
}

template<class T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D& rhs) const
{
    return Vector2D<T>(this->x_ + rhs.x_, this->y_ + rhs.y_);
}

template<class T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D& rhs) const
{
    return Vector2D<T>(this->x_ - rhs.x_, this->y_ - rhs.y_);
}

template<class T>
void Vector2D<T>::Swap(Vector2D<T>& rhs)
{
    T& tx = this->x_;
    this->x_ = rhs.x_;
    rhs.x_ = tx;

    T& ty = this->y_;
    this->y_ = rhs.y_;
    rhs.y_ = ty;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const Vector2D<T>& vec2d)
{
    stream << "Vector2D(" << vec2d.x_ << ", " << vec2d.y_ << ")";

    return stream;
}

template<class T>
Vector2D<T> operator*(const int& lhs, const Vector2D<T>& rhs)
{
    return Vector2D<T>(rhs.x_ * lhs, rhs.y_ * lhs);
}

template<class T>
Vector2D<T> operator*(const Vector2D<T>& lhs, const int& rhs)
{
    return Vector2D<T>(lhs.x_ * rhs, lhs.y_ * rhs);
}

template<class T>
const float Vector2D<T>::Norm(const float& p) const
{
    return powf((powf(this->x_, p) + powf(this->y_, p)), static_cast<float>(1 / p));
}
}  // namespace SmashStone::Utils