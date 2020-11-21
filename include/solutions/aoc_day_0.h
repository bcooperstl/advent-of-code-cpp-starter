#ifndef __AOC_DAY_0__
#define __AOC_DAY_0__

#include "aoc_day.h"

class AocDay0 : public AocDay
{
    private:
        vector<long> read_input(string filename);
    public:
        AocDay0();
        ~AocDay0();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
