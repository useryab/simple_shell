#include "shell.h"

/**
 *
 **/

int main(int argc, char *argv[])
{
  char *arg[] = {NULL, NULL};
  char *envp[] = {NULL};
  char *buffer = NULL; 
  size_t size = 0;
  ssize_t read;
  int pid, status;

  while (1)
    {
      printf("#cisfun$ ");
      read = getline(&buffer, &size, stdin);
      if (read == -1)
	{
	  if (feof(stdin))
	    {
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
	  return (-1);
	}
      else if (pid == 0)
	{
	  
	  arg[0] = malloc((strlen(buffer) + 1) * sizeof(char));
	  if (arg[0] == NULL)
	    return (-1);

	  strcpy(arg[0], buffer);
	  
	  if (execve(buffer, arg, envp) == -1)
	    {
	      printf("%s: No such file or direcyory\n", argv[0]);
	      free(buffer);
	      free(arg[0]);
	      return (-1);
	    }
	}
      else
	{
	  wait(&status);
	}
    }

  return (0);
}
