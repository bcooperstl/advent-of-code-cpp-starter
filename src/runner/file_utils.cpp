#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "file_utils.h"

using namespace std;

// Really basic way to parse a line based on delimiters. 
// parameters:
//  input = the input string to split. assume newline is removed, or else it will be addded to the last item
//  delimiter = the value to split on
//  quote = an optional parameter - a quote character to indicate a that quoted sections will be used and ignore delimiters
//  comment_char = an optional parameter - if this is the first character in a line, that line is treated as a comment and skipped.
vector<string> FileUtils::split_line_to_strings(string input, char delimiter, char quote_char, char comment_char)
{
#ifdef DEBUG_RUNNER
    cout << "original input is [" << input << "]" << endl;
#endif

    vector<string> splits;
    
    char * pos = (char *)input.c_str();
    
    if (comment_char && *pos == comment_char)
    {
#ifdef DEBUG_RUNNER
        cout << "Comment line found" << endl;
#endif
        return splits;
    }
    
    bool in_quote = false;
    ostringstream current;
    while (*pos != '\0')
    {
        if (quote_char && in_quote)
        {
            if (*pos == quote_char)
            {
                in_quote = false;
#ifdef DEBUG_RUNNER
                cout << "Leaving quotes" << endl;
#endif
            }
            else
            {
                current << (*pos);
            }
        }
        else
        {
            if (quote_char && *pos == quote_char)
            {
                in_quote = true;
#ifdef DEBUG_RUNNER
                cout << "In quotes" << endl;
#endif
            }
            else if (*pos == delimiter)
            {
                // ABCDE,ABCDE,ABCDE
                // first string goes from 0 to 4...construct as string(0,5). pos will be 5 for the comma. so 5-0=5
                // second string goes from 6 to 10...construct as string(6,5)...pos wil be 11 for the comma. so 11-6=5
                // third string goes from 12 to 16...construct as string(12,5) but need to do this out of loop as its the last string
#ifdef DEBUG_RUNNER
                cout << "appending [" << current.str() << "] as a string" << endl;
#endif
                splits.push_back(current.str());
                current = ostringstream();
            }
            else
            {
                current << (*pos);
            }
        }
        pos++;
    }
    // append the last string. pos will be pointed to the null terminator at 17, so string(12,5) would be pos(17)-start(12)
#ifdef DEBUG_RUNNER
    cout << "appending [" << current.str() << "] as the last string" << endl;
#endif
    splits.push_back(current.str());
    return splits;
}

bool FileUtils::read_as_list_of_strings(string filename, vector<string> & lines)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "*****Error opening file " << filename << endl;
        return false;
    }
    string line;
    while (getline(infile, line))
    {
#ifdef DEBUG_RUNNER
        cout << "Read line [" << line << "] from file" << endl;
#endif
        lines.push_back(line);
    }
    infile.close();
    return true;
}

bool FileUtils::read_as_list_of_split_strings(string filename, vector<vector<string>> & split_strings, char delimiter, char quote_char, char comment_char)
{
    vector<string> lines;
    if (!read_as_list_of_strings(filename, lines))
    {
        return false;
    }
    for (vector<string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
    {
        vector<string> results = split_line_to_strings(*iter, delimiter, quote_char, comment_char);
        if (results.size() > 0)
            split_strings.push_back(results);
    }
    return true;
}

bool FileUtils::read_as_list_of_split_longs(string filename, vector<vector<long>> & split_longs, char delimiter, char quote_char, char comment_char)
{
    vector<string> lines;
    if (!read_as_list_of_strings(filename, lines))
    {
        return false;
    }
    for (vector<string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
    {
        vector<string> long_strings = split_line_to_strings(*iter, delimiter, quote_char, comment_char);
        vector<long> longs;
        for (vector<string>::iterator str_long_iter = long_strings.begin(); str_long_iter != long_strings.end(); ++str_long_iter)
        {
            string str_long = *str_long_iter;
            longs.push_back(strtol(str_long.c_str(), NULL, 10));
        }
        split_longs.push_back(longs);
    }
    return true;
}

