# Testing Utility

There is testing functionality built into this starter to allow tests to be easily run repeatedly. It will check for expected results, and alert the developer whether tests pass or fail.

Test can either be run for a single day and part, or for all the days as a whole (i.e. regression testing). A common test index file will identify all the tests to be run. The developer can split the test index file into multiple files, if so desired.

## Test File Format
The sample test file is given in `data/sample/test_index_0.txt` and only contains tests against the day 0 solution provided with the starter.

The format for a line in the file is:

`day,part,filename,expected result[,any extra arguments (comma-separated)]`

### Simple Test Case 
Looking at a simple test case:  
`0,1,test_cases/day0_test1.txt,3`

The day is day 0.  
The part is part 1.  
The input file is `test_cases/day0_test1.txt`. This is the file containing the test data (i.e. what you would run through as a single file in non-testing mode). 
It is given relative from the location of the index file. So, the index file is in `data/sample/test_index_0.txt`, 
and the test case file is in `data/sample/test_cases/day0_test1.txt`, so just the relative part of `test_cases/day0_test1.txt` is given.  
The expected result is 3

### Adding extra arguments
If you need to pass in extra arguments for the test, such as the number of iterations to run, those can be given after the expected result, in a comma-separeted list.
This is the same as if you were adding extra arguments to the end of run-one-file invocation.

So for:  
`0,2,test_cases/day0_test4.txt,6,a,b,c`  
It's day 0, part 2, input file is `test_cases/day0_test4.txt`, the expected result is 6. There are then three extra arguments `a`,`b`, and `c` which are passed through to the `AocDay0::part2(string filename, vector<string> extra_args)` function in the `extra_args` list.

### Quoting a delimiter
Let's say an answer required a comma. (i.e. 2018, Day 13). Rather than have to rewrite this to use a different delimiter, you can just put the element in single quotes.

So for :  
`13,1,test_cases/day13_test1.txt,'6,4'`
It's day 13, part 1, input file is `test_cases/day13_test1.txt`, the expected result is `6,4`. The comma is preserved in the expected answer

These is no way to escape a single quote. I'm hoping that it isn't necessary, so it probably will be around day 16 :-)

### Comments
You can put comments in the test file. Any line that starts with a `#` is treated as a comment.

### Sample test file
Here's the test of the `data/sample/test_index_0.txt` file, showing how the file could be put together.

    #format is day,part,filename,expected result,any extra arguments (comma-separated)
    0,1,test_cases/day0_test2.txt,3
    #This is a comment
    0,1,test_cases/day0_test3.txt,0
    0,1,test_cases/day0_test4.txt,-6
    0,1,day0_input.txt,569
    0,2,test_cases/day0_test1.txt,-3
    #The below test case shows that the answer can be quoted, if a comma is in the answer (happened in 2018)
    0,2,test_cases/day0_test2.txt,'-3'
    0,2,test_cases/day0_test3.txt,0
    #a,b,c are extra parms. Not worrying about them in this program, but showing how to do that
    #The extra parameters are useful when the sample will show a program runnign for 10 times,
    # but we really run it 1000000 times. This allows that value to be specified without recompiling
    0,2,test_cases/day0_test4.txt,6,a,b,c
    0,2,day0_input.txt,-569

## Running Tests
There are two modes to run tests: one day/part combination or full regression test of all the test cases in the index file.

### One day/part Mode
The command line is:

    bin/aoc -d day -p part -t test_index_filename

Everything should be straight forward - give it the day, part (1 or 2), and the tess index file. It'll run all the matching test cases and output the results at the end of the program. 
There is a pass/fail count given at the end as well.  
For example:  

    [brian@dev1 advent-of-code-cpp-starter]$ bin/aoc -d 0 -p 1 -t data/sample/test_index_0.txt
    Running tests for day 0 part 1
    ++Day 0 Part 1-data/sample/test_cases/day0_test1.txt passed with result 3
    ++Day 0 Part 1-data/sample/test_cases/day0_test2.txt passed with result 3
    --Day 0 Part 1-data/sample/test_cases/day0_test3.txt FAILED expected=0 actual=9
    ++Day 0 Part 1-data/sample/test_cases/day0_test4.txt passed with result -6
    ++Day 0 Part 1-data/sample/day0_input.txt passed with result 569


### Regression Mode
The command line is:

    bin/aoc -r test_index_filename

The only input is the filename, and it will run the tests and show the results at the end. There is a pass/fail count given at the end as well.  
For example:  

    [brian@dev1 advent-of-code-cpp-starter]$ bin/aoc -r data/sample/test_index_0.txt
    Running full regression test for all days and parts!
    ++Day 0 Part 1-data/sample/test_cases/day0_test1.txt passed with result 3
    ++Day 0 Part 1-data/sample/test_cases/day0_test2.txt passed with result 3
    --Day 0 Part 1-data/sample/test_cases/day0_test3.txt FAILED expected=0 actual=9
    ++Day 0 Part 1-data/sample/test_cases/day0_test4.txt passed with result -6
    ++Day 0 Part 1-data/sample/day0_input.txt passed with result 569
    ++Day 0 Part 2-data/sample/test_cases/day0_test1.txt passed with result -3
    ++Day 0 Part 2-data/sample/test_cases/day0_test2.txt passed with result -3
    ++Day 0 Part 2-data/sample/test_cases/day0_test3.txt passed with result 0
    ++Day 0 Part 2-data/sample/test_cases/day0_test4.txt passed with result 6
    ++Day 0 Part 2-data/sample/day0_input.txt passed with result -569
    ++++++9 of 10 tests passed++++++
    ------1 of 10 TESTS FAILED------

#### One suggestion
If you're going to be using the regression mode, after you have a correct solution for a day/part, it would be a good idea to put that in the test_index file so it could be picked up by future regressions.

At least once in 2019, I thought I had done some successful code surgery on my intCode portions and simple tests passed, but I had a bug that I didn't realize until I manually re-ran a prior day's actual full input file.


