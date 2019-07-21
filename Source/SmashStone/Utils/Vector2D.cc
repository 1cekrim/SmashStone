#include <SmashStone/Utils/Vector2D.hpp>

#include <cmath>

namespace SmashStone::Utils
{
template<class T>
Vector2D<T>::Vector2D(const T _x, const T _y) : x_(_x), y_(_y)
{
    // Do nothing
}

template<class T>
Vector2D<T>::Vector2D(const Vector2D<T>& vec2d) : Vector2D(vec2d.x_, vec2d.y_)
{
    // Do nothing
}

template<class T>
Vector2D<T>& Vector2D<T>::operator=(const Vector2D<T>& rhs)
{
    Vector2D<T> temp(rhs);

    Swap(temp);

    return *this;
}

template<class T>
Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<T>& rhs)
{
    this->x_ += rhs.x_;
    this->y_ += rhs.y_;

    return *this;
}

template<class T>
Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<T>& rhs)
{
    this->x_ -= rhs.x_;
    this->y_ -= rhs.y_;

    return *this;
}

template<class T>
Vector2D<T>& Vector2D<T>::operator*=(const T& rhs)
{
    this->x_ *= rhs;
    this->y_ *= rhs;

    return *this;
}

template<class T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& rhs) const
{
    return Vector2D<T>(this->x_ + rhs.x_, this->y_ + rhs.y_);
}

template<class T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& rhs) const
{
    return Vector2D<T>(this->x_ - rhs.x_, this->y_ - rhs.y_);
}

template<class T>
Vector2D<T> Vector2D<T>::operator/(const T& rhs) const
{
    return Vector2D<T>(this->x_ / rhs, this->y_ / rhs);
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
Vector2D<T> operator*(const T& lhs, const Vector2D<T>& rhs)
{
    return Vector2D<T>(rhs.x_ * lhs, rhs.y_ * lhs);
}

template<class T>
Vector2D<T> Vector2D<T>::operator*(const T& rhs) const
{
    Vector2D<T> temp = *this;
    temp._x *= rhs;
    temp._y *= rhs;
    return temp;
}

template<class T>
const float Vector2D<T>::Norm(const float& p) const
{
    return powf((powf(this->x_, p) + powf(this->y_, p)), static_cast<float>(1 / p));
}

template<class T>
const T Vector2D<T>::Dot(const Vector2D<T>& rhs) const
{
    return this->x_ * rhs.x_ + this->y_ * rhs.y_;
}

template<class T>
Vector2D<T> Vector2D<T>::Normalized(void) const
{
    const float d = Norm(2);
    return Vector2D<T>(this->x_ / d, this->y_ / d);
}
}  // namespace SmashStone::Utils