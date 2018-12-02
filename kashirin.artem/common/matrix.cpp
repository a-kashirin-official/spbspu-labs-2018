#include "matrix.hpp"
#include <cmath>
#include <stdexcept>

using namespace kashirin;

Matrix::Matrix(const std::shared_ptr< Shape > figure):
figures_(nullptr),
layerNumber_(0),
layerSize_(0)
{
    if (figure == nullptr)
    {
        throw std::invalid_argument("null ptr");
    }
    addShape(figure);
}

Matrix::Matrix(const Matrix & matrix):
figures_(new std::shared_ptr< Shape >[matrix.layerNumber_ * matrix.layerSize_]),
layerNumber_(matrix.layerNumber_),
layerSize_(matrix.layerSize_)
{
    for (int i = 0; i < layerNumber_ * layerSize_; ++i)
    {
        figures_[i] = matrix.figures_[i];
    }
}

Matrix::Matrix(Matrix && matrix):
figures_(nullptr),
layerNumber_(matrix.layerNumber_),
layerSize_(matrix.layerSize_)
{
    figures_.swap(matrix.figures_);
    matrix.layerSize_ = 0;
    matrix.layerNumber_ = 0;
}

Matrix & Matrix::operator=(const Matrix & matrix)
{
    if (this != & matrix)
    {
        layerNumber_ = matrix.layerNumber_;
        layerSize_ = matrix.layerSize_;
        std::unique_ptr< std::shared_ptr< Shape >[] > newFigures(new
        std::shared_ptr< Shape >[layerNumber_ * layerSize_]);
        for (int i = 0; i < layerNumber_ * layerSize_; ++i)
        {
            newFigures[i] = matrix.figures_[i];
        }
        figures_.swap(newFigures);
    }
    return *this;
}

Matrix & Matrix::operator=(Matrix && matrix)
{
    if (this != & matrix)
    {
        layerNumber_ = matrix.layerNumber_;
        layerSize_ = matrix.layerSize_;
        figures_.reset();
        figures_.swap(matrix.figures_);
        matrix.layerNumber_ = 0;
        matrix.layerSize_ = 0;
    }
    return *this;
}

Matrix::~Matrix()
{
    figures_.reset();
    figures_ = nullptr;
    layerSize_ = 0;
    layerNumber_ = 0;
}

void Matrix::addShape(const std::shared_ptr< Shape > figure)
{
    if (layerNumber_ == 0)
    {
        std::unique_ptr<std::shared_ptr< Shape >[]> newFigures(new std::shared_ptr< Shape >[(layerNumber_ + 1) * (layerSize_ + 1)]);
        layerNumber_++;
        layerSize_++;
        figures_.swap(newFigures);
        figures_[0] = figure;
    }
    else
    {
        bool addedFigure = false;
        for (int i = 0; !addedFigure; ++i)
        {
            for (int j = 0; j < layerSize_; ++j)
            {
                if (!figures_[i * layerSize_ + j])
                {
                    figures_[i * layerSize_ + j] = figure;
                    addedFigure = true;
                    break;
                }
                else
                {
                    if (checkOverlapping(i * layerSize_ + j, figure))
                    {
                        break;
                    }
                }
                
                if (j == (layerSize_ - 1))
                {
                    std::unique_ptr<std::shared_ptr< Shape >[]> newFigures(new std::shared_ptr
                    < Shape >[layerNumber_ * (layerSize_ + 1)]);
                    layerSize_++;
                    for (int n = 0; n < layerNumber_; ++n)
                    {
                        for (int m = 0; m < layerSize_ - 1; ++m)
                        {
                            newFigures[n * layerSize_ + m] = figures_[n * (layerSize_ -1) + m];
                        }
                        newFigures[(n + 1) * layerSize_ - 1] = nullptr;
                    }
                    newFigures[(i + 1) * layerSize_ - 1] = figure;
                    figures_.swap(newFigures);
                    addedFigure = true;
                    break;
                }
            }
            if ((i == (layerNumber_ - 1)) && !addedFigure)
            {
                layerNumber_++;
                std::unique_ptr<std::shared_ptr< Shape >[]> newFigures(new std::shared_ptr
                                                                       < Shape >[layerNumber_ * layerSize_]);
                for (int n = 0; n < ((layerNumber_ - 1) * layerSize_); ++n)
                {
                    newFigures[n] = figures_[n];
                }
                for (int n = ((layerNumber_ - 1) * layerSize_); n < (layerNumber_ * layerSize_); ++n)
                {
                    newFigures[n] = nullptr;
                }
                newFigures[(layerNumber_ - 1) * layerSize_] = figure;
                figures_.swap(newFigures);
                addedFigure = true;
            }
        }
    }
}

bool Matrix::checkOverlapping(const int index, std::shared_ptr< Shape > figure) const
{
    rectangle_t FigureFrameRectN = figure->getFrameRect();
    rectangle_t FigureFrameRectM = figures_[index]->getFrameRect();
    point_t newPoints[4] = {
        {FigureFrameRectN.pos.x - FigureFrameRectN.width / 2, FigureFrameRectN.pos.y + FigureFrameRectN.height / 2},
        {FigureFrameRectN.pos.x + FigureFrameRectN.width / 2, FigureFrameRectN.pos.y + FigureFrameRectN.height / 2},
        {FigureFrameRectN.pos.x + FigureFrameRectN.width / 2, FigureFrameRectN.pos.y - FigureFrameRectN.height / 2},
        {FigureFrameRectN.pos.x - FigureFrameRectN.width / 2, FigureFrameRectN.pos.y - FigureFrameRectN.height / 2}
    };
    
    point_t matrixPoints[4] = {
        {FigureFrameRectM.pos.x - FigureFrameRectM.width / 2, FigureFrameRectM.pos.y + FigureFrameRectM.height / 2},
        {FigureFrameRectM.pos.x + FigureFrameRectM.width / 2, FigureFrameRectM.pos.y + FigureFrameRectM.height / 2},
        {FigureFrameRectM.pos.x + FigureFrameRectM.width / 2, FigureFrameRectM.pos.y - FigureFrameRectM.height / 2},
        {FigureFrameRectM.pos.x - FigureFrameRectM.width / 2, FigureFrameRectM.pos.y - FigureFrameRectM.height / 2}
    };
    
    for (int i = 0; i < 4; ++i)
    {
        if (((newPoints[i].x >= matrixPoints[0].x) && (newPoints[i].x <= matrixPoints[2].x)
             && (newPoints[i].y >= matrixPoints[3].y) && (newPoints[i].y <= matrixPoints[1].y))
            || ((matrixPoints[i].x >= newPoints[0].x) && (matrixPoints[i].x <= newPoints[2].x)
                && (matrixPoints[i].y >= newPoints[3].y) && (matrixPoints[i].y <= newPoints[1].y)))
        {
            return true;
        }
    }
    return false;
}

std::unique_ptr< std::shared_ptr< Shape >[] > Matrix::operator[](const int index) const
{
    if ((index < 0) || (index >= layerNumber_))
    {
        throw std::out_of_range("invalid index");
    }
    std::unique_ptr<std::shared_ptr<Shape>[]> layer(
                                                           new std::shared_ptr<Shape>[layerSize_]);
    for (int i = 0; i < layerSize_; ++i)
    {
        layer[i] = figures_[index * layerSize_ + i];
    }
    return layer;
}

int Matrix::getSize() const
{
    return layerSize_;
}

int Matrix::getNumbers() const
{
    return layerNumber_;
}

bool Matrix::operator==(const Matrix & matrix) const
{
    if ((this->layerNumber_ != matrix.layerNumber_) || (this->layerSize_ != matrix.layerSize_))
    {
        return false;
    }
    for (int i = 0; i < layerNumber_ * layerSize_; ++i)
    {
        if (this->figures_[i] != matrix.figures_[i])
        {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix & matrix) const
{
    if ((this->layerNumber_ != matrix.layerNumber_) || (this->layerSize_ != matrix.layerSize_))
    {
        return true;
    }
    for (int i = 0; i < layerNumber_ * layerSize_; ++i)
    {
        if (this->figures_[i] != matrix.figures_[i])
        {
            return true;
        }
    }
    return false;
}
