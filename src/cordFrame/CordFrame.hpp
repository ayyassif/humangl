#ifndef CORDFRAME_HPP
#define CORDFRAME_HPP

#include <vector>
#include "Mat4.hpp"
#include "Part.hpp"

class CordFrame
{
private:
    std::vector<CordFrame*> children;

    Part part;
    Mat4 model;
    Mat4 firstModel;
    Vec3 scale = Vec3(1.0f);
public:
    CordFrame();
    CordFrame(const Mat4& model, Part part);

    void addChild(CordFrame *child);
    const Mat4 &getModel() const;
    Mat4 getFirstModel() const;
    const Vec3 &getScale() const;
    Part &getPart();
    const Part &getPart() const;
    const std::vector<CordFrame*>& getChildren() const;

    void setModel(const Mat4& model);
    void setScale(const Vec3& newScale);
};

#endif