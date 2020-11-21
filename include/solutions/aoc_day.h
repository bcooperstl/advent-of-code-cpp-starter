#ifndef __AOC_DAY_H__
#define __AOC_DAY_H__

#include <string>
#include <vector>

using namespace std;

/* This is the superclass for all of the daily programs.
 * It will have two functions to override - one for part 1, and one for part 2
 * each of those functions takes two arguments
 *  1) the filename for the input file.
    2) a vector of strings for extra arguments. This vector can be empty.
 */

class AocDay
{
    protected:
        int m_day;
    public:
        AocDay(int day);
        ~AocDay();
        virtual string part1(string filename, vector<string> extra_args);
        virtual string part2(string filename, vector<string> extra_args);
};

#endif
