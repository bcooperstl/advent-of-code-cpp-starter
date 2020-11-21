#include <iostream>
#include <vector>

#include "aoc_tests.h"
#include "aoc_test.h"
#include "constants.h"
#include "file_utils.h"

using namespace std;

AocTests::AocTests()
{
}

AocTests::~AocTests()
{
}

string AocTests::base_directory(string filename)
{
    size_t found;
    found=filename.find_last_of("/\\");
    if (found != string::npos) // found a directory character. return everything from the start through that character
    {
        return filename.substr(0,found+1);
    }
    else // no directory character found. just return an empty string to indicate the current directory
    {
        return "";
    }
}

bool AocTests::load_tests(string filename)
{
    vector<vector<string>> test_index_contents;
    string basedir = base_directory(filename);
#ifdef DEBUG_RUNNER
    cout << "The base dicectory for test files is " << basedir << endl;
#endif
    FileUtils fileutils;
    if (!fileutils.read_as_list_of_split_strings(filename, test_index_contents, TEST_INDEX_DELIM, TEST_INDEX_QUOTE, TEST_INDEX_COMMENT))
    {
        cerr << "Error reading test index file " << filename << endl;
        return false;
    }
    
    for (vector<vector<string>>::iterator test_iter = test_index_contents.begin(); test_iter != test_index_contents.end(); ++test_iter)
    {
        vector<string> test_parameters = *test_iter;
        // Skip a blank line
        if (test_parameters.size() == 1 && test_parameters[0].size() == 0)
        {
            continue;
        }
        
        vector<string>::iterator parm_iter=test_parameters.begin();
        // format is day,part,filename,expected[,...extra args]
        long day, part;
        string filename, full_filename, expected;
        vector<string> extra_args;

        day = strtol((*parm_iter).c_str(), NULL, 10);
        ++parm_iter;

        part = strtol((*parm_iter).c_str(), NULL, 10);
        ++parm_iter;

        filename = *parm_iter;
        full_filename = basedir + filename;
#ifdef DEBUG_RUNNER
        cout << "The full path to " << filename << " is " << full_filename << endl;
#endif
        ++parm_iter;

        expected = *parm_iter;
        ++parm_iter;
        while (parm_iter != test_parameters.end())
        {
#ifdef DEBUG_RUNNER
            cout << "Adding extra parm " << *parm_iter << endl;
#endif
            extra_args.push_back(*parm_iter);
            ++parm_iter;
        }
        m_tests.push_back(AocTest(day, part, full_filename, expected, extra_args));
    }
    return true;
}

vector<AocTest> AocTests::get_all_tests()
{
    return m_tests;
}

vector<AocTest> AocTests::filter_tests(int day, int part)
{
    vector<AocTest> matching_tests;
    
    for (vector<AocTest>::iterator test_iter = m_tests.begin(); test_iter !=m_tests.end(); ++test_iter)
    {
        if ((*test_iter).matches(day, part))
        {
            matching_tests.push_back(*test_iter);
        }
    }
    
    return matching_tests;
}
