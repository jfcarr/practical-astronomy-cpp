LIB_OBJS1 = pa_datetime.o pa_coordinates.o pa_sun.o pa_planet.o pa_comet.o
LIB_OBJS2 = pa_data.o pa_macros.o pa_util.o 
TEST_OBJS = test.o test_datetime.o test_coordinates.o test_sun.o test_planet.o test_comet.o
SUPPORT_HEADERS = lib/pa_models.h lib/pa_types.h
COMPILER = g++
CPP_STD = c++17
FORMATTER = clang-format

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

test: $(TEST_OBJS) $(LIB_OBJS1) $(LIB_OBJS2)
	$(COMPILER) -o test $(TEST_OBJS) $(LIB_OBJS1) $(LIB_OBJS2)

test.o: test.cpp
	$(COMPILER) -std=$(CPP_STD) -c test.cpp

test_datetime.o: test_datetime.cpp
	$(COMPILER) -std=$(CPP_STD) -c test_datetime.cpp

test_coordinates.o: test_coordinates.cpp $(SUPPORT_HEADERS)
	$(COMPILER) -std=$(CPP_STD) -c test_coordinates.cpp

pa_datetime.o: lib/pa_datetime.cpp lib/pa_datetime.h $(SUPPORT_HEADERS)
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_datetime.cpp

pa_coordinates.o: lib/pa_coordinates.cpp lib/pa_coordinates.h $(SUPPORT_HEADERS)
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_coordinates.cpp

pa_sun.o: lib/pa_sun.cpp lib/pa_sun.h $(SUPPORT_HEADERS)
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_sun.cpp

pa_planet.o: lib/pa_planet.cpp lib/pa_planet.h $(SUPPORT_HEADERS)
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_planet.cpp

pa_comet.o: lib/pa_comet.cpp lib/pa_comet.h $(SUPPORT_HEADERS)
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_comet.cpp

pa_data.o: lib/pa_data.cpp lib/pa_data.h
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_data.cpp

pa_macros.o: lib/pa_macros.cpp lib/pa_macros.h $(SUPPORT_HEADERS)
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_macros.cpp

pa_util.o: lib/pa_util.cpp lib/pa_util.h
	$(COMPILER) -std=$(CPP_STD) -c lib/pa_util.cpp

document:
	doxygen

format:
	$(FORMATTER) -i test.cpp test_datetime.cpp test_coordinates.cpp test_sun.cpp test_planet.cpp
	$(FORMATTER) -i lib/pa_datetime.cpp lib/pa_datetime.h
	$(FORMATTER) -i lib/pa_coordinates.cpp lib/pa_coordinates.h
	$(FORMATTER) -i lib/pa_sun.cpp lib/pa_sun.h
	$(FORMATTER) -i lib/pa_planet.cpp lib/pa_planet.h
	$(FORMATTER) -i lib/pa_comet.cpp lib/pa_comet.h
	$(FORMATTER) -i lib/pa_data.cpp lib/pa_data.h
	$(FORMATTER) -i lib/pa_macros.cpp lib/pa_macros.h
	$(FORMATTER) -i lib/pa_util.cpp lib/pa_util.h
	$(FORMATTER) -i $(SUPPORT_HEADERS)

clean:
	-rm -f test *.o
