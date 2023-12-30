#include "shell.h"

/**
 *
**/

int main(int argc, char *argv[])
{
  char *arg[MAX_LENGTH];
  char *envp[] = {NULL};
  char *buffer = NULL;
  char *token;
  size_t size = 0;
  ssize_t read;
  int pid, status, i;

  if (argc > 1)
    {
      printf("%s: 0: Can't open %s\n", argv[0], argv[1]);
      exit(-1);
    }
  while (1)
    {
      printf("#cisfun$ ");
      read = getline(&buffer, &size, stdin);
      if (read == -1)
	{
	  if (feof(stdin))
	    {
	      if (buffer != NULL)
		{
		  free(buffer);
		  buffer = NULL;
		}
	      printf("\n");
	      break;
	    }
	  else
	    {
	      perror("getline fail!!!\n");
	      return (-1);
	    }
	}
      buffer[strlen(buffer) - 1] = '\0';

      pid = fork();

      if (pid < 0)
	{
	  perror("fork gets error!!!\n");
	  free(buffer);
	  return (-1);
	}
      else if (pid == 0)
	{
	  token = strtok(buffer, " ");
	  i = 0;
	  while (token != NULL)
	    {
	      arg[i++] = token;
	      token = strtok(NULL, " ");
	    }
	  arg[i] = NULL;

	  if (execve(arg[0], arg, envp) == -1)
	    {
	      printf("%s: No such file or direcyory\n", argv[0]);
	      free(buffer);
	      return (-1);
	    }
	}
      else
	{
	  wait(&status);
	  if (buffer != NULL)
	    {
	      free(buffer);
	      buffer = NULL;
	    }
	}
    }

  return (0);
}
