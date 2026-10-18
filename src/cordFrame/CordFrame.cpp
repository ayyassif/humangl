#include "CordFrame.hpp"

CordFrame::CordFrame() {}

CordFrame::CordFrame(const Mat4& model, Part part)
    : model(model),
      part(part),
      firstModel(model)
{}

void CordFrame::addChild(CordFrame *child)
{
    children.push_back(child);
}

const Mat4& CordFrame::getModel() const
{
    return model;
}

const Mat4& CordFrame::getFirstModel() const
{
    return firstModel;
}

const Part& CordFrame::getPart() const
{
    return part;
}

Part& CordFrame::getPart()
{
    return part;
}

const std::vector<CordFrame*>& CordFrame::getChildren() const
{
    return children;
}

void CordFrame::setModel(const Mat4& model)
{
    this->model = model;
}
