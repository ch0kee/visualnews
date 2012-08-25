#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class _Log
{
public:
    template<typename _T>
    _Log& operator<< (const _T& in)
    {
        std::cout << ">> " << in << std::endl;
        return *this;
    }

};
extern _Log logger;
#define LOG( x ) std::cout << x << std::endl

#endif // LOGGER_H
