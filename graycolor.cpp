#include "graycolor.h"
#include <QDebug>

GrayColor::GrayColor(QColor color)
{
    _red = convert2Gray(static_cast<unsigned short>(color.red()));
    _green = convert2Gray(static_cast<unsigned short>(color.green()));
    _blue = convert2Gray(static_cast<unsigned short>(color.blue()));
}

GrayColor::GrayColor(unsigned short _r, unsigned short _g, unsigned short _b)
{
    _red = convert2Gray(_r);
    _green = convert2Gray(_g);
    _blue = convert2Gray(_b);
}

unsigned short GrayColor::blue() const
{
    return _blue;
}

void GrayColor::setBlue(unsigned short value)
{
    _blue = value;
}

unsigned short GrayColor::green() const
{
    return _green;
}

void GrayColor::setGreen(unsigned short value)
{
    _green = value;
}

unsigned short GrayColor::red() const
{
    return _red;
}

void GrayColor::setRed(unsigned short value)
{
    _red = value;
}

