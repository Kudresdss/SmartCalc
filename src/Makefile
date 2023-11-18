APP_NAME = SmartCalculator

all: install tests lcov

install:
	bash install.sh

uninstall: clean
	rm -rf $(APP_NAME)
	rm -rf $(APP_NAME).tar.gz

clean:
	rm -rf smart_calculator
	#rm -rf coverage*

dvi:
	open ../README.md

dist: install
	tar -czf $(APP_NAME).tar.gz --directory=smart_calculator/ .

launch:
	./$(APP_NAME)

tests: install
	make -C smart_calculator run_test
	./smart_calculator/run_test

lcov: tests
	make -C build coverage
	cp build/coverage.info .
	genhtml coverage.info --output-directory coverage_report
	open coverage_report/index.html

#clang:
#	clang-format --style=google -n controller/*
#	clang-format --style=google -n model/*
#	clang-format --style=google -n mvc_model/*
#	clang-format --style=google -n view/*.cc view/*.h
#	clang-format --style=google -n structures.h main.cc
#	clang-format --style=google -n test/*

.PHONY: all install uninstall clean dvi dist launch tests lcov clang