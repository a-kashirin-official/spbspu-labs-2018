//
// Created by Yaroslav on 29.05.2018.
//

#include "matrix.hpp"
#include <memory>
#include <cmath>
#include <iostream>

erokhin::Matrix::Matrix():
        map_(nullptr),
        rows_(0u),
        columns_(0u)
{
}

erokhin::Matrix::Matrix(const erokhin::Matrix & rhs):
        map_(new std::shared_ptr<Shape>[rhs.rows_ * rhs.columns_]),
        rows_(rhs.rows_),
        columns_(rhs.columns_)
{
    for (unsigned int i = 0; i < rows_ * columns_; i++)
    {
        map_[i] = rhs.map_[i];
    }
}

erokhin::Matrix::Matrix(erokhin::Matrix &&rhs):
        map_(std::move(rhs.map_)),
        rows_(rhs.rows_),
        columns_(rhs.columns_)
{
    rhs.rows_ = 0u;
    rhs.columns_ = 0u;
}

erokhin::Matrix & erokhin::Matrix::operator=(const erokhin::Matrix &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    map_.reset(new std::shared_ptr<Shape>[rhs.rows_ * rhs.columns_]);
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    for (unsigned int i = 0; i < rows_ * columns_; i++)
    {
        map_[i] = rhs.map_[i];
    }
    return *this;
}

erokhin::Matrix & erokhin::Matrix::operator=(erokhin::Matrix &&rhs)
{
    map_ = std::move(rhs.map_);
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    rhs.rows_ = 0;
    rhs.columns_ = 0;
    return *this;
}

std::unique_ptr<std::shared_ptr<erokhin::Shape>[]> erokhin::Matrix::operator[](const unsigned int index) const
{
    if (index >= rows_)
    {
        throw std::out_of_range ("Invalid index");
    }
    std::unique_ptr<std::shared_ptr<Shape> []> mass(new std::shared_ptr<Shape>[columns_]);
    for(unsigned int i = 0; i < columns_; i++)
    {
        mass[i] = map_[index * columns_ + i];
    }
    return mass;
}

void erokhin::Matrix::add(const std::shared_ptr<erokhin::Shape> figure)
{
    if (figure == nullptr)
    {
        throw std::invalid_argument("It can not be empty figure!");
    }
    if ((rows_ == 0) && (columns_ == 0))
    {
        map_.reset(new std::shared_ptr<Shape>[1]);
        rows_ = 1;
        columns_ = 1;
        map_[0] = figure;
        return;
    }
    unsigned int count1 = 0;
    for(unsigned int i = 0; i < rows_; i++)
    {
        unsigned int count2 = 0;
        for(unsigned int j = 0; j < columns_; j++)
        {
            if (map_[i * columns_ + j] == nullptr)
            {
                map_[i * columns_ + j] = figure;
                return;
            }
            if (controlCross(map_[i * columns_ + j], figure) == true)
            {
                count2 = j + 1;
                break;
            }
            count2 = j + 1;
        }
        if (count2 == columns_)
        {
            std::unique_ptr<std::shared_ptr<Shape> []> newmap(new std::shared_ptr<Shape>[rows_ * (columns_ + 1)]);
            for(unsigned int m = 0; m < rows_; m++)
            {
                for(unsigned int n = 0; n < columns_; n++)
                {
                    newmap[m * columns_ + n + m] = map_[m * columns_ + n];
                }
            }
            columns_++;
            newmap[(i + 1) * columns_ - 1] = figure;
            map_ = std::move(newmap);
            return;
        }
        count1 = i + 1;
    }
    if (count1 == rows_)
    {
        std::unique_ptr<std::shared_ptr<Shape> []> newmap(new std::shared_ptr<Shape>[(rows_ + 1) * columns_]);
        for (unsigned int i = 0; i < rows_ * columns_; i++)
        {
            newmap[i] = map_[i];
        }
        newmap[rows_ * columns_] = figure;
        rows_++;
        map_ = std::move(newmap);
    }
}

bool erokhin::Matrix::controlCross(const std::shared_ptr<erokhin::Shape> figure1,
                                   const std::shared_ptr<erokhin::Shape> figure2)
{
    if (figure1 == nullptr || figure2 == nullptr)
    {
        throw std::invalid_argument("Figures can't be empty!");
    }
    erokhin::rectangle_t frame1 = figure1->getFrameRect();
    erokhin::rectangle_t frame2 = figure2->getFrameRect();
    return ((fabs(frame1.pos.x - frame2.pos.x) < frame1.width / 2 + frame2.width / 2) &&
            fabs(frame1.pos.y - frame2.pos.y) < frame1.height / 2 + frame2.height / 2);
}

unsigned int erokhin::Matrix::getRows() const
{
    return rows_;
}

unsigned int erokhin::Matrix::getColumns() const
{
    return columns_;
}

void erokhin::Matrix::viewMap() const
{
    for(unsigned int i = 0; i < rows_; i++)
    {
        for(unsigned int j = 0; j < columns_; j++)
        {
            if (map_[i * columns_ + j] != nullptr)
            {
                map_[i * columns_ + j]->viewName();
            }
        }
        std::cout << std::endl;
    }
}
