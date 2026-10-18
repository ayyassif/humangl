#ifndef PART_HPP
#define PART_HPP

#include "Math.hpp"

class Part
{
private:
    Mat4 model;
    Vec3 color;
    Vec3 firstColor;
public:
    Part();
    Part(const Mat4& model, const Vec3& color);

    Mat4 getModel() const;
    Vec3 getColor() const;
    void setColor(const float c[3]);
    Vec3 getFirstColor() const;
};


#endif