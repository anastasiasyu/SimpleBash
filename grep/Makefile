SHELL := /bin/bash
Fi=1.txt
P=pattern.txt

all: s21_grep 

clang:
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -i *.c 
	clang-format -n *.h
	clang-format -i *.h

s21_grep:
	gcc -std=c11 -Wall -Werror -Wextra -o s21_grep s21_grep.c

test:
	-diff <(./s21_grep -v Hello $(Fi)) <(grep -v Hello $(Fi))
	-diff <(./s21_grep -i Da $(Fi)) <(grep -i Da $(Fi))
	-diff <(./s21_grep -e :da $(Fi)) <(grep -e :da $(Fi))
	-diff <(./s21_grep -s Green $(Fi)) <(grep -s Green $(Fi))

shtest:
	sh grep_test.sh

clean:
	rm -rf ./s21_grep 

rebuild: clean clang s21_grep

