#include "s21_grep.h"

int main(int argc, char **argv) {
  arguments arg = arg_parser(argc, argv);
  output(arg, argc, argv);
  return 0;
}

// f
void pattern_add(arguments *arg, char *pattern) {
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(arguments *arg, char *filepath) {
  FILE *f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s) perror(filepath);
    exit(1);
  }
  char *line = NULL;
  size_t memlen = 0;
  ssize_t read = getline(&line, &memlen, f);
  while (read != -1) {
    // f
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    pattern_add(arg, line);
    read = getline(&line, &memlen, f);
  }
  free(line);
  fclose(f);
}

arguments arg_parser(int argc, char **argv) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        pattern_add(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
      case '?':
        perror("n/a");
        exit(1);
        break;
    }
  }
  if (arg.len_pattern == 0) {
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

// o
// void print_match(regex_t *re, char *line) {
//   regmatch_t math;
//   int offset = 0;
//   while(1) {
//     int result = regexec(re, line +  offset, 1, &math, 0);
//     if (result !=0) {
//       break;
//     }
//     for (int i = math.rm_so; i < math.rm_eo; i++) {
//       putchar(line[i]);
//     }
//     putchar('\n');
//     offset += math.rm_eo;

//   }
// }

void print_match(arguments arg, regex_t *re, char *line, int line_count,
                 char *path) {
  regmatch_t match;
  int offset = 0;

  while (regexec(re, line + offset, 1, &match, 0) != 1) {
    if (!arg.h) printf("%s:", path);
    if (arg.n) printf("%d:", line_count);
    for (int i = match.rm_so; i < match.rm_eo;
         i++) {  // start offset end offset
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void processFile(arguments arg, char *path, regex_t *reg) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    // s
    if (!arg.s) perror(path);
    exit(1);
  }
  char *line = NULL;
  size_t memlen = 0;
  int line_count = 1;
  int count = 0;
  int read = getline(&line, &memlen, f);

  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h && !arg.o) printf("%s:", path);
        if (arg.n && !arg.o) printf("%d:", line_count);
        if (arg.o) {
          if (result != 0 && !arg.h) printf("%s:", path);
          if (result == 0) print_match(arg, reg, line, line_count, path);
          if (result != 0 && arg.n) printf("%d:", line_count);
          if (result != 0) output_line(line, read);

        } else
          output_line(line, read);
      }
      count++;
    }
    read = getline(&line, &memlen, f);
    line_count++;
  }

  // while (read != -1) {
  //   int result = regexec(reg, line, 0, NULL, 0);
  //   //v
  //   if ((result == 0 && !arg.v) || (arg.v && result !=0))
  //   {

  //     if (!arg.l && !arg.c) {
  //        if (!arg.h) printf("%s:", path);
  //     //n
  //       if (arg.n) printf("%d:", line_count);
  //       if (arg.o) {
  //         if (result != 0 && !arg.h) printf("%s:", path);
  //         //if (result == 0) print_match(arg, reg, line, line_count, path);
  //         if (result != 0 && arg.n) printf("%d:", line_count);
  //         if (result != 0) output_line(line, read);
  //         output_line(line, read);
  //       }
  //       //else{

  //       //}

  //     }
  //     count++;
  //   }
  //   read = getline(&line, &memlen, f);
  //   line_count++;

  // }

  free(line);
  // c
  if (!arg.l && arg.c) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", count);
  }
  // l
  if (arg.l && count > 0) printf("%s\n", path);
  fclose(f);
}

void output(arguments arg, int argc, char **argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) perror("n/a1");
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &re);
  }
  regfree(&re);
}
