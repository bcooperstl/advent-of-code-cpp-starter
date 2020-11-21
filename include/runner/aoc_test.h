#ifndef __AOC_TEST_H__
#define __AOC_TEST_H__

#include <string>
#include <vector>

using namespace std;

class AocTest
{
    private:
        int m_day;
        int m_part;
        string m_filename;
        string m_expected_result;
        vector<string> m_extra_args;
    public:
        AocTest(int day, int part, string filename, string expected_result, vector<string> extra_args);
        ~AocTest();
        bool matches(int day, int part);
        bool compare_result(string actual_result);
        int get_day();
        int get_part();
        string get_filename();
        string get_expected_result();
        vector<string> get_extra_args();
};

#endif
