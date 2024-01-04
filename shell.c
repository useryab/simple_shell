#include "shell.h"
extern char **environ;

/**
 *
 **/

void display_prompt()
  {
    if (isatty(fileno(stdin)))
      printf("#cisfun$ ");
  }

void execute_command(char **arg, char **envp, char *arg0)
  {
    int pid, status;

    pid = fork();

    if (pid < 0)
      {
	perror("fork gets error!!!\n");
	_free(&arg);
	exit(-1);
      }
    else if (pid == 0)
      {
	if (execve(arg[0], arg, envp) == -1)
	  {
	    printf("%s: No such file or directory\n", arg0);
	    _free(&arg);
	    exit(-1);
	  }
      }
    else
      {
	wait(&status);
	_free(&arg);
      }
  }

void handle_exit(char **arg, char *argv[])
  {
    if (!(strcmp(arg[0], "exit")) && arg[1] == NULL)
      {
	_free(&arg);
	exit(0);
      }
    else if (!(strcmp(arg[0], "exit")) && arg[1] != NULL)
      {
	_free(&arg);
	printf("%s: not accept argument.\n", argv[0]);
      }
  }

void handle_env(char **arg)
  {
    char **env;

    if (!(strcmp(arg[0], "env")) && arg[1] == NULL)
      {
	for (env = environ; *env != NULL; env++)
	  printf("%s\n", *env);
      }
    else if (!(strcmp(arg[0], "env")) && arg[1] != NULL)
      {
	_free(&arg);
      }
  }

int main(int argc, char *argv[])
  {
    char *env[] = {NULL};
    char **arg;
    char *buffer = NULL;
    size_t size = 0;
    int read;

    if (argc > 1)
      {
	printf("%s: 0: Can't open %s\n", argv[0], argv[1]);
	exit(-1);
      }

    while (1)
      {
	display_prompt();
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
	  {
	    continue;
	  }

	arg = get_arg(buffer);
	buffer = NULL;

	handle_exit(arg, argv);
	handle_env(arg);

	if (access(arg[0], X_OK))
	  {
	    arg[0] = get_path(_strcat("/", arg[0]));
	    if (arg[0] == NULL)
	      {
		printf("%s: NO such file or directory\n", argv[0]);
		continue;
	      }
	  }

	execute_command(arg, env, argv[0]);
      }

    return (0);
  }
