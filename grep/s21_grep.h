#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[2000];
  int len_pattern;
  int mem_pattern;

} arguments;

void pattern_add(arguments *arg, char *pattern);
void add_reg_from_file(arguments *arg, char *filepath);
arguments arg_parser(int argc, char **argv);
void output_line(char *line, int n);
void print_match(arguments arg, regex_t *re, char *line, int line_count,
                 char *path);
void processFile(arguments arg, char *path, regex_t *reg);
void output(arguments arg, int argc, char **argv);

#endif