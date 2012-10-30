#include "Number.h"



Number::Number(float n) : number(n)
{
}

Number::Number() : number(0)
{
}


Number::~Number(void)
{
}


std::ostream& operator<<(std::ostream& output, const Number& num)
{
    return output << num.number;
}

bool Number::operator<(const Number& o) 
{
    return number < o.number;
}