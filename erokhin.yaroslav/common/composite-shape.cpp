//
// Created by Yaroslav on 27.04.2018.
//

#include "composite-shape.hpp"
#include <memory>
#include <cmath>
#include <iostream>

erokhin::CompositeShape::CompositeShape():
    access_(false),
    posit_({0, 0}),
    digest_(nullptr),
    size_(0u)
{
}

erokhin::CompositeShape::CompositeShape(const std::shared_ptr<erokhin::Shape> figure):
        access_(false),
        posit_({0, 0}),
        digest_(nullptr),
        size_(0u)
{
    add(figure);
}

double erokhin::CompositeShape::getArea() const
{
    double area = 0;
    if (size_ != 0)
    {
        for (unsigned int i = 0; i < size_; i++)
        {
            area += digest_[i]->getArea();
        }
    }
    return (area);
}

erokhin::rectangle_t erokhin::CompositeShape::getFrameRect() const
{
    if (size_ == 0)
    {
        return {0, 0, posit_};
    }
    else
    {
        return {(maxXY().x - minXY().x), (maxXY().y - minXY().y), posit_};
    }
}

void erokhin::CompositeShape::move(const double dx, const double dy)
{
    posit_.x += dx;
    posit_.y += dy;
    if (size_ != 0)
    {
        for (unsigned int i = 0; i < size_; i++)
        {
            digest_[i]->move(dx, dy);
        }
    }
}

void erokhin::CompositeShape::move(const point_t &p)
{
    if (size_ != 0)
    {
        point_t d;
        d.x = p.x - posit_.x;
        d.y = p.y - posit_.y;
        for (unsigned int i = 0; i < size_; i++)
        {
            digest_[i]->move(d.x, d.y);
        }
    }
    posit_ = p;
}

void erokhin::CompositeShape::scale(const double x)
{
    if (!access_)
    {
        throw std::invalid_argument("method can't be used now");
    }
    if (x < 0.0)
    {
        throw std::invalid_argument("scale");
    }
    for (unsigned int i = 0; i < size_; i++)
    {
        digest_[i]->scale(x);
    }
}

void erokhin::CompositeShape::add(const std::shared_ptr<Shape> figure)
{
    if (figure == nullptr)
    {
        throw::std::invalid_argument("It can not be empty figure!");
    }
    if (size_ == 0u)
    {
        std::unique_ptr<std::shared_ptr<Shape> []> copy(new std::shared_ptr<Shape> [size_ + 1]);
        copy[size_] = figure;
        digest_ = std::move(copy);
        posit_.x = digest_[0]->getFrameRect().pos.x;
        posit_.y = digest_[0]->getFrameRect().pos.y;
        size_++;
        access_ = true;
    }
    else
    {
        std::unique_ptr<std::shared_ptr<Shape> []> copy(new std::shared_ptr<Shape> [size_ + 1]);
        for (unsigned int i = 0; i < size_; i++)
        {
            copy[i] = digest_[i];
        }
        copy[size_] = figure;
        digest_ = std::move(copy);
        size_++;
    }
}

void erokhin::CompositeShape::rotate(const double degrees)
{
    if (size_ != 0)
    {
        double radns = degrees * M_PI / 180;
        point_t pos = {0, 0};
        rectangle_t temprect = {0 , 0, pos};
        for (unsigned int i = 0; i < size_; i++)
        {
            temprect = digest_[i]->getFrameRect();
            pos.x = posit_.x + (temprect.pos.x - posit_.x) * cos(radns) - (temprect.pos.y - posit_.y) * sin(radns);
            pos.y = posit_.y + (temprect.pos.y - posit_.y) * cos(radns) + (temprect.pos.x - posit_.x) * sin(radns);
            digest_[i]->move(pos);
            digest_[i]->rotate(degrees);
        }
        posit_.x = (maxXY().x + minXY().x) / 2.0;
        posit_.y = (maxXY().y + minXY().y) / 2.0;
    }
}

erokhin::point_t erokhin::CompositeShape::maxXY() const
{
    double maxX = digest_[0]->getFrameRect().pos.x + ((digest_[0]->getFrameRect().width) / 2.0);
    double maxY = digest_[0]->getFrameRect().pos.y + ((digest_[0]->getFrameRect().height) / 2.0);
    for(unsigned int i = 0; i < size_; i++)
    {
        if ((digest_[i]->getFrameRect().pos.x + ((digest_[i]->getFrameRect().width) / 2.0)) > maxX)
        {
            maxX = digest_[i]->getFrameRect().pos.x + ((digest_[i]->getFrameRect().width) / 2.0);
        }
        if ((digest_[i]->getFrameRect().pos.y + ((digest_[i]->getFrameRect().height) / 2.0)) > maxY)
        {
            maxY = digest_[i]->getFrameRect().pos.y + ((digest_[i]->getFrameRect().height) / 2.0);
        }
    }
    return {maxX, maxY};
}

erokhin::point_t erokhin::CompositeShape::minXY() const
{
    double minX = digest_[0]->getFrameRect().pos.x - (digest_[0]->getFrameRect().width / 2.0);
    double minY = digest_[0]->getFrameRect().pos.y - (digest_[0]->getFrameRect().height / 2.0);
    for(unsigned int i = 0; i < size_; i++)
    {
        if ((digest_[i]->getFrameRect().pos.x - digest_[i]->getFrameRect().width / 2.0) < minX)
        {
            minX = digest_[i]->getFrameRect().pos.x - digest_[i]->getFrameRect().width / 2.0;
        }
        if ((digest_[i]->getFrameRect().pos.y - digest_[i]->getFrameRect().height / 2.0) < minY)
        {
            minY = digest_[i]->getFrameRect().pos.y - digest_[i]->getFrameRect().height / 2.0;
        }
    }
    return {minX, minY};
}

void erokhin::CompositeShape::viewName() const
{
    std::cout << "CompositeShape ";
}
