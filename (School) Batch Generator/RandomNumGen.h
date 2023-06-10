#ifndef RANDOMNUMGEN_H
#define RANDOMNUMGEN_H

#include <chrono>
#include <random>

namespace Random
{
    inline std::mt19937 init()
    {
        std::random_device rd;
        
        std::seed_seq ss{static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        
        return std::mt19937{ss};
    }

    inline std::mt19937 mt{init()};
    
    inline int get(int min, int max)
    {
        std::uniform_int_distribution uid{min, max};
        return uid(mt);
    }
};

#endif
