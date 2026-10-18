#include "Part.hpp"

Part::Part() {}

Part::Part(const Mat4& model, const Vec3& color) : model(model), color(color / 255), firstColor(this->color) {}

Vec3 Part::getColor() const
{
    return color;
}

void Part::setColor(const float c[3])
{
    color = Vec3(c[0], c[1], c[2]);
}

Vec3 Part::getFirstColor() const
{
    return firstColor;
}

Mat4 Part::getModel() const
{
    return model;
}
