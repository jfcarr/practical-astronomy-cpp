COMPILER = clang++
CPP_STD = c++17

default:
	@echo 'Targets:'
	@echo '  run-test-verbose  -- Run unit tests, with verbose output'
	@echo '  run-test          -- Run unit tests'
	@echo '  build-test        -- Build test project'
	@echo '  document          -- Generate documentation'
	@echo '  format            -- Format source code'
	@echo '  clean             -- Remove object and bin files'

run-test-verbose: build-test
	./test -s

run-test: build-test
	./test

build-test: test

test: test.o pa_macros.o pa_util.o pa_datetime.o
	$(COMPILER) -o test test.o pa_datetime.o pa_util.o pa_macros.o

test.o: test.cpp
	$(COMPILER) -std=$(CPP_STD) -c test.cpp

pa_datetime.o: lib/pa_datetime.cpp lib/pa_datetime.h
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_datetime.cpp

pa_util.o: lib/pa_util.cpp lib/pa_util.h
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_util.cpp

pa_macros.o: lib/pa_macros.cpp lib/pa_macros.h
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_macros.cpp

document:
	doxygen

format:
	clang-format -i test.cpp
	clang-format -i lib/pa_datetime.cpp lib/pa_datetime.h
	clang-format -i lib/pa_util.cpp lib/pa_util.h

clean:
	-rm -f test *.o
