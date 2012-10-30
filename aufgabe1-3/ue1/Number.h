#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>

class Number
{
    friend std::ostream& operator<<(std::ostream& output, const Number& num);
public:
    Number(float n);
    Number();
    ~Number(void);

    bool operator<(const Number& o);



private:
    float number;
};

#endif