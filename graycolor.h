#pragma once

#include <QColor>
#include "graynumber.h"

class GrayColor
{
public:
    GrayColor(QColor color);
    GrayColor(unsigned short red, unsigned short green, unsigned short blue);

    unsigned short red() const;
    void setRed(unsigned short value);

    unsigned short green() const;
    void setGreen(unsigned short value);

    unsigned short blue() const;
    void setBlue(unsigned short value);

private:
    unsigned short _red;
    unsigned short _green;
    unsigned short _blue;
};
