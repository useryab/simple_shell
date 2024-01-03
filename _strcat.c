#include "shell.h"

/**
 *
**/
char *new_cat;

char *_strcat(char *dest, char *src)
{
  size_t total_length = strlen(dest) + strlen(src);
  new_cat = NULL;

  new_cat = malloc(total_length + 1);

  if (new_cat == NULL)
    {
      perror("new_cat: malloc fail!!!\n");
      return (NULL);
    }

  strcat(new_cat, dest);
  strcat(new_cat, src);

  return (new_cat);
}
