DEBUG=
#Uncomment the below line to dispaly the runner debug
#DEBUG+= -DDEBUG_RUNNER
#Template for other debug flags to be added later
#DEBUG+- -DDEBUG_OTHER

#If adding another include directory, be sure to add it here
CPPFLAGS=-g ${DEBUG} -Iinclude/common -Iinclude/runner -Iinclude/solutions

.DEFAULT_GOAL := all

# Runner library; contains a lot of common code for file parsing and handling test files
build/runner/aoc_test.o: src/runner/aoc_test.cpp  \
	include/runner/aoc_test.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/runner/aoc_test.o -c src/runner/aoc_test.cpp

build/runner/aoc_tests.o: src/runner/aoc_tests.cpp  \
	include/runner/aoc_tests.h \
	include/runner/aoc_test.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/runner/aoc_tests.o -c src/runner/aoc_tests.cpp

build/runner/file_utils.o: src/runner/file_utils.cpp  \
	include/runner/file_utils.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/runner/file_utils.o -c src/runner/file_utils.cpp

bin/lib/librunner.a: build/runner/aoc_test.o  \
	build/runner/aoc_tests.o  \
	build/runner/file_utils.o
	ar rcs bin/lib/librunner.a build/runner/aoc_test.o build/runner/aoc_tests.o build/runner/file_utils.o

# Solutions - These are the programs for the daily solutions
build/solutions/aoc_day.o: src/solutions/aoc_day.cpp  \
	include/solutions/aoc_day.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/solutions/aoc_day.o -c src/solutions/aoc_day.cpp

build/solutions/aoc_days.o: src/solutions/aoc_days.cpp  \
	include/solutions/aoc_days.h \
	include/solutions/aoc_day.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/solutions/aoc_days.o -c src/solutions/aoc_days.cpp

#Generic line to compile a daily solution.
#Be sure to add the .o file to the libsoluations.a target
build/solutions/aoc_day_0.o: src/solutions/aoc_day_0.cpp  \
	include/solutions/aoc_day_0.h \
	include/solutions/aoc_day.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/solutions/aoc_day_0.o -c src/solutions/aoc_day_0.cpp

bin/lib/libsolutions.a: build/solutions/aoc_day.o  \
	build/solutions/aoc_days.o \
	build/solutions/aoc_day_0.o
	ar rcs bin/lib/libsolutions.a build/solutions/aoc_day.o build/solutions/aoc_days.o build/solutions/aoc_day_0.o

# The aoc executable
build/aoc.o: src/aoc.cpp  \
	include/solutions/aoc_days.h  \
	include/runner/aoc_tests.h  \
	include/runner/file_utils.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/aoc.o -c src/aoc.cpp

#If adding a new library, be sure to add it in the correct order in the compile line
bin/aoc: build/aoc.o  \
	bin/lib/librunner.a \
	bin/lib/libsolutions.a
	g++ ${CPPFLAGS} -o bin/aoc build/aoc.o -Lbin/lib -lsolutions -lrunner

clean:
	rm -f build/runner/aoc_test.o  \
	build/runner/aoc_tests.o  \
	build/runner/file_utils.o  \
	build/solutions/aoc_day.o  \
	build/solutions/aoc_day_0.o  \
	build/solutions/aoc_days.o  \
	build/aoc.o  \
	bin/lib/librunner.a  \
	bin/lib/libsolutions.a  \
	bin/aoc

all: build/runner/aoc_test.o  \
	build/runner/aoc_tests.o  \
	build/runner/file_utils.o  \
	build/solutions/aoc_day.o  \
	build/solutions/aoc_day_0.o  \
	build/solutions/aoc_days.o  \
	build/aoc.o  \
	bin/lib/librunner.a  \
	bin/lib/libsolutions.a  \
	bin/aoc
