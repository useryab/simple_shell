#include "shell.h"

/**
 * my_getline - ...........
 * @lineptr: .....
 * @n: ......
 * @stream: .....
 * Return: ...
 **/

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
  size_t i = 0;
  int fp;
  char *new_lineptr;
  
  if (*lineptr == NULL || *n == 0)
    {
      *n = 128;
      *lineptr = (char *)malloc(*n);
      if (*lineptr == NULL)
	{
	  perror("malloc");
	  return (-1);
	}
    }

  i = 0;
  fp = fgetc(stream);
  while (fp != EOF && fp != '\n')
    {
      if (i >= *n - 1)
	{
	  *n *= 2;
	  new_lineptr = (char *)realloc(*lineptr, *n);
	  if (new_lineptr == NULL)
	    {
	      perror("fail realloc!!!");
	      free(*lineptr);
	      *lineptr = NULL;
	      return (-1);
	    }
	  *lineptr = new_lineptr;
	}

      (*lineptr)[i++] = (char)fp;
      fp = fgetc(stream);
    }
  (*lineptr)[i] = '\0';

  if (fp == EOF && i == 0)
    {
      free(*lineptr);
      *lineptr = NULL;
      return (-1);
    }
  
 if (fp == '\n' && i == 0)
    {
      free(*lineptr);
      *lineptr = NULL;
      return (-2);
    }

  return (i);
}
