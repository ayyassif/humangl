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
public:
    CordFrame();
    CordFrame(const Mat4& model, Part part);

    void addChild(CordFrame *child);
    const Mat4 &getModel() const;
    const Mat4 &getFirstModel() const;
    const Part &getPart() const;
    const std::vector<CordFrame*>& getChildren() const;

    void setModel(const Mat4& model);
};

#endif