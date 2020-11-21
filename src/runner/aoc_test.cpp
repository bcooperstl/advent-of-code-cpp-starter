#include <string>
#include <vector>

#include "aoc_test.h"

using namespace std;

AocTest::AocTest(int day, int part, string filename, string expected_result, vector<string> extra_args):m_day(day),m_part(part),m_filename(filename),m_expected_result(expected_result),m_extra_args(extra_args)
{
}

AocTest::~AocTest()
{
}

bool AocTest::matches(int day, int part)
{
    return (m_day == day) && (m_part == part);
}

bool AocTest::compare_result(string actual_result)
{
    return m_expected_result == actual_result;
}

int AocTest::get_day()
{
    return m_day;
}

int AocTest::get_part()
{
    return m_part;
}

string AocTest::get_filename()
{
    return m_filename;
}

string AocTest::get_expected_result()
{
    return m_expected_result;
}

vector<string> AocTest::get_extra_args()
{
    return m_extra_args;
}
