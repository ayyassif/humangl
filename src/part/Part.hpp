#ifndef PART_HPP
#define PART_HPP

#include "Math.hpp"

class Part
{
private:
    Mat4  model;
    Vec3 color;
public:
    Part();
    Part(const Mat4& model, const Vec3& color);

    Mat4 getModel() const;
    Vec3 getColor() const;
};


#endif