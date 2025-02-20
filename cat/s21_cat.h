#ifndef S21_CAT_H
#define S21_CAT_H

#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int b;
  int n;
  int s;
  int E;
  int T;
  int v;
} arguments;

arguments arg_parser(int argc, char **argv);
void outline(arguments *arg, char *line, int n);
char v_output(char ch);
void output(arguments *arg, char **argv);

#endif