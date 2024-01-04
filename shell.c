#include "shell.h"
extern char **environ;

/**
 * main - function
 * argc: number of argument
 * argv: argv
 * Return: int
**/

int main(int argc, char *argv[])
{
  char **env;
  char **arg;
  char *envp[] = {NULL};
  char *buffer = NULL;
  size_t size = 0;
  int pid, status, read;
  bool is_interactive;

  if (argc > 1)
    {
      printf("%s: 0: Can't open %s\n", argv[0], argv[1]);
      exit(-1);
    }
  is_interactive = isatty(fileno(stdin));
  while (1)
    {
      if (is_interactive)
      printf("#cisfun$ ");
      read = my_getline(&buffer, &size, stdin);
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
      else if (read == -2)
	continue;

      arg = get_arg(buffer);
      buffer = NULL;

      if (!(strcmp(arg[0], "exit")) && arg[1] == NULL)
	{
	  _free(&arg);
	  break;
	}
      else if (!(strcmp(arg[0], "exit")) && arg[1] != NULL)
	{
	  _free(&arg);
	  printf("%s: not accept argument.\n", argv[0]);
	  continue;
	}

      if (!(strcmp(arg[0], "env")) && arg[1] == NULL)
	{
	  for (env = environ; *env != NULL; env++)
	    printf("%s\n", *env);
	  continue;
	}
      else if (!(strcmp(arg[0], "env")) && arg[1] != NULL)
	{
	  _free(&arg);
	  continue;
	}
      
      if ((access(arg[0], X_OK)))
	{
	  arg[0] = get_path(_strcat("/", arg[0]));
	  if (arg[0] == NULL)
	    {
	      printf("%s: No such file or direcyory\n", argv[0]);
	      continue;
	    }
	}
       pid = fork();

      if (pid < 0)
	{
	  perror("fork gets error!!!\n");
	  _free(&arg);
	  return (-1);
	}
      else if (pid == 0)
	{
	  if (execve(arg[0], arg, envp) == -1)
	    {
	      printf("%s: No such file or direcyory\n", argv[0]);
	      _free(&arg);
	      return (-1);
	    }
	}
      else
	{
	  wait(&status);
	  _free(&arg);
	}
    }
  return (0);
}
