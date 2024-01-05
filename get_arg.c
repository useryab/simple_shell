#include "shell.h"

/**
 *
 **/

char **get_arg(char *buffer)
{
  char *token;
  int i = 0;
  char **arg = malloc(MAX_LENGTH * sizeof(char *));

  
  if (arg == NULL)
    {
      perror("malloc fails!!!\n");
      return (NULL);
    }

  token = _strtok(buffer, " ");

  while (token != NULL)
    {
      arg[i] = strdup(token);
      token = _strtok(NULL, " ");
      i++;
    }
  arg[i] = NULL;

  free(buffer);
  return (arg);
}
