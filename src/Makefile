APP_NAME 	= SmartCalculator
TESTS_NAME  = tests

all: install tests lcov

install:
	bash install.sh

uninstall: clean
	rm -rf $(APP_NAME)
	rm -rf $(APP_NAME).tar.gz

clean:
	rm -rf smart_calculator
	rm -rf coverage*
	rm $(TESTS_NAME)

dvi:
	open ../README.md

dist: install
	tar -czf $(APP_NAME).tar.gz --directory=smart_calculator/ .

launch:
	./$(APP_NAME)

tests: install
	make -C smart_calculator tests
	cp smart_calculator/tests tests
	leaks --atExit -q -- ./tests

lcov: tests
	lcov -t "tests" -o gcov.info --no-external -c -d .
	lcov --remove gcov.info '*/smart_calculator/tests_autogen/*' --output-file gcov.info
	genhtml -o coverage_report gcov.info
	open coverage_report/index.html
	rm gcov.info

clang:
	clang-format --style=google -n controller/*
	clang-format --style=google -n model/*
	clang-format --style=google -n view/*.cc view/*.h
	clang-format --style=google -n structures.h main.cc
	clang-format --style=google -n test/*

.PHONY: all install uninstall clean dvi dist launch tests lcov clang
