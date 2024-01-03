#include "shell.h"

/**
 *
 **/

void print_arg(char **arg)
  {
    int i = 0;
    if (arg)
      {
    while (arg[i])
      {
	printf("arg[%d]: %s\n", i, arg[i]);
	i++;
      }

    }
  }
