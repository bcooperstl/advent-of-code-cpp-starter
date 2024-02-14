DEBUG=
#Uncomment the below line to dispaly the runner debug
#DEBUG+= -DDEBUG_RUNNER
#Template for other debug flags to be added later
#DEBUG+- -DDEBUG_OTHER

#If adding another include directory, be sure to add it here
CPPFLAGS=-std=c++17 -g ${DEBUG} -I./include/common -I./include/runner -I./include/solutions

.DEFAULT_GOAL := all

# Runner library; contains a lot of common code for file parsing and handling test files
build/runner/aoc_test.o: src/runner/aoc_test.cpp  \
	include/runner/aoc_test.h \
	include/common/constants.h
	clang++ ${CPPFLAGS} -o build/runner/aoc_test.o -c src/runner/aoc_test.cpp

build/runner/aoc_tests.o: src/runner/aoc_tests.cpp  \
	include/runner/aoc_tests.h \
	include/runner/aoc_test.h \
	include/common/constants.h
	clang++ ${CPPFLAGS} -o build/runner/aoc_tests.o -c src/runner/aoc_tests.cpp

build/runner/file_utils.o: src/runner/file_utils.cpp  \
	include/runner/file_utils.h \
	include/common/constants.h
	clang++ ${CPPFLAGS} -o build/runner/file_utils.o -c src/runner/file_utils.cpp

bin/lib/librunner.a: build/runner/aoc_test.o  \
	build/runner/aoc_tests.o  \
	build/runner/file_utils.o
	ar rcs bin/lib/librunner.a build/runner/aoc_test.o build/runner/aoc_tests.o build/runner/file_utils.o

# Solutions - These are the programs for the daily solutions
build/solutions/%.o: src/solutions/%.cpp  \
	include/solutions/%.h \
	include/common/constants.h
	clang++ ${CPPFLAGS} -c -o $@ $<

objects := $(patsubst src/solutions/%.cpp,build/solutions/%.o,$(wildcard src/solutions/*.cpp))

bin/lib/libsolutions.a: $(objects)
	ar rcs bin/lib/libsolutions.a $(objects)

# The aoc executable
build/aoc.o: src/aoc.cpp  \
	include/solutions/aoc_days.h  \
	include/runner/aoc_tests.h  \
	include/runner/file_utils.h \
	include/common/constants.h
	clang++ ${CPPFLAGS} -o build/aoc.o -c src/aoc.cpp

#If adding a new library, be sure to add it in the correct order in the compile line
bin/aoc: build/aoc.o  \
	bin/lib/librunner.a \
	bin/lib/libsolutions.a
	clang++ ${CPPFLAGS} -o bin/aoc build/aoc.o -Lbin/lib -lsolutions -lrunner

clean:
	rm -f build/runner/*.o  \
	build/solutions/*.o  \
	build/aoc.o  \
	bin/lib/*.a  \
	bin/aoc

all: $(wildcard build/runner/*.o)  \
	$(wildcard build/solutions/*.o)  \
	build/aoc.o  \
	$(wildcard bin/lib/*.a)  \
	bin/aoc
