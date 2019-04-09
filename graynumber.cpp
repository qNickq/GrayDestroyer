#include "graynumber.h"


unsigned short convert2Gray(unsigned short num)
{
    return num ^ (num >> 1);
}

unsigned short convert2Bin(unsigned short num)
{
    unsigned int bin;
    for (bin = 0; num; num >>= 1) {
        bin ^= num;
    }
    return static_cast<unsigned short>(bin);
}

unsigned short nextGray(unsigned short num)
{
    if (isGrayEven(num))
    {
        return num ^ 1;
    }
    else
    {
        return static_cast<unsigned short>(num ^ (getLesserOne(num) << 1));
    }
}

bool isGrayEven(unsigned short num)
{
    int count = 0;
    while (num)
    {
        if (num & 1) ++count;
        num >>= 1;
    }
    return (count % 2 == 0);
}

unsigned short getLesserOne(unsigned short num)
{
    return num & ~(num-1) ;
}
