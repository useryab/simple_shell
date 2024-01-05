#include "shell.h"

/**
 *
 **/

char *_strtok(char *str, const char *delim)
{
  static char *temp_str = NULL;
  char *token;
  char *end_point;

  if (str != NULL)
    {
      temp_str = str;
    }
  else if (temp_str == NULL)
    {
      return (NULL);
    }

  token = temp_str + strspn(temp_str, delim);
  if (*token == '\0')
    {
      temp_str = NULL;
      return (NULL);
    }

  end_point = token + strcspn(token, delim);

  if (*end_point != '\0')
    {
      *end_point = '\0';
      temp_str = end_point + 1;
    }
  else
    {
      temp_str = NULL;
    }

  return (token);
}
