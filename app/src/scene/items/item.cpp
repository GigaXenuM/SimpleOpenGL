#include "item.h"

Scene::Item::Item(unsigned int element, unsigned int pointCount)
    : _element(element), _pointCount(pointCount)
{
}

unsigned int Scene::Item::getElement() const
{
    return _element;
}

unsigned int Scene::Item::getPointCount() const
{
    return _pointCount;
}
