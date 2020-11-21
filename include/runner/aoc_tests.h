#ifndef __AOC_TESTS_H__
#define __AOC_TESTS_H__

#include <string>
#include <vector>

#include "aoc_test.h"

using namespace std;

class AocTests
{
    private:
        vector<AocTest> m_tests;
        string base_directory(string filename);
    public:
        AocTests();
        ~AocTests();
        bool load_tests(string filename);
        vector<AocTest> get_all_tests();
        vector<AocTest> filter_tests(int day, int part);
};

#endif
