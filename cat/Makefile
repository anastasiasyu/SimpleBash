SHELL := /bin/bash
FLAG =-Wall -Werror -Wextra
FILE=test_5_cat.txt

all: s21_cat test

s21_cat:
	gcc -std=c11 $(FLAG) s21_cat.c -o s21_cat

rebuild: clean clang s21_cat

test:
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -v $(FILE)) <(cat -v $(FILE))

clean:
	rm ./s21_cat

clang:
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -i *.c 

shtest:
	sh test_s21_cat.sh
