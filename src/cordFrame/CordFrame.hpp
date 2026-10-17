#ifndef CORDFRAME_HPP
#define CORDFRAME_HPP

#include <vector>
#include "Mat4.hpp"
#include "Part.hpp"

class CordFrame
{
private:
    std::vector<CordFrame> children;

    Part part;
    Mat4 model;
public:
    CordFrame();
    CordFrame(const Mat4& model, Part part);

    void addChild(const CordFrame &child);
};

CordFrame::CordFrame() {}

CordFrame::CordFrame(const Mat4& model, Part part)
    : model(model),
      part(part)
{}

void CordFrame::addChild(const CordFrame &child)
{
    children.push_back(child);
}

#endif