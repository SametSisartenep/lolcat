/* Copyright (C) 2014 jaseg <github@jaseg.net>
 *
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 * Version 2, December 2004
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 * 0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#define _GNU_SOURCE //for fmemopen

#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <sys/time.h>


#define ARRAY_SIZE(foo) (sizeof(foo)/sizeof(foo[0]))
const char codes[] = {39,38,44,43,49,48,84,83,119,118,154,148,184,178,214,208,209,203,204,198,199,163,164,128,129,93,99,63,69,33};

int
main (int argc, char **argv) {
  char **inputs = argv + 1;
  char **inputs_end = argv + argc;
  if (inputs == inputs_end) {
    char *foo[] = {"-"};
    inputs = foo;
    inputs_end = inputs + 1;
  }

  setlocale(LC_ALL, "");

  for (char **filename = inputs; filename < inputs_end; filename++) {
    FILE *f = stdin;

    if (strcmp(*filename, "-"))
      f = fopen(*filename, "r");

    if (!f) {
      fprintf(stderr, "Cannot open input file \"%s\": %s\n", *filename, strerror(errno));
      return 2;
    }

        int c;
    while ((c = fgetwc(f)) > 0) {
            if (strchr("acegmnopqrsuvwxyz", c))
                printf("▄");
            else if (strchr(".,:; \t\r\n", c))
                printf("%lc", c);
            else
                printf("█");
    }

    fclose(f);

    if (c != WEOF && c != 0) {
      fprintf(stderr, "Error reading input file \"%s\": %s\n", *filename, strerror(errno));
      return 2;
    }
  }
}
