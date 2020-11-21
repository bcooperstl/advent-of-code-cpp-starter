#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_0.h"
#include "file_utils.h"

using namespace std;

AocDay0::AocDay0():AocDay(0)
{
}

AocDay0::~AocDay0()
{
}

vector<long> AocDay0::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<long> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        long l;
        string to_convert = *iter;
        l = strtol(to_convert.c_str(), NULL, 10);
        data.push_back(l);
    }
    return data;
}

string AocDay0::part1(string filename, vector<string> extra_args)
{
    vector<long> data = read_input(filename);
    long sum = 0;
    for (vector<long>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        sum+=*iter;
    }
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay0::part2(string filename, vector<string> extra_args)
{
    if (extra_args.size() > 0)
    {
        cout << "There are " << extra_args.size() << " extra arguments given:" << endl;
        for (vector<string>::iterator iter = extra_args.begin(); iter != extra_args.end(); ++iter)
        {
            cout << "[" << *iter << "]" << endl;
        }
    }
    
    vector<long> data = read_input(filename);
    long sum = 0;
    for (vector<long>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        sum-=*iter;
    }
    ostringstream out;
    out << sum;
    return out.str();
}
