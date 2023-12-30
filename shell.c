#include "shell.h"

/**
 *
 **/

int main(int argc __attribute__((unused)), char *argv[])
  {
    char *buffer = NULL;
    char *token[MAX_LENGTH] = {NULL};
    char *envp[] = {NULL};
    size_t num = 0;
    int i;
    int max = 0;
    int status;
    pid_t pid;
    ssize_t read;
    
    while (1)
      {
	if (buffer != NULL)
	  {
	  free(buffer);
	  buffer = NULL;
	  }
	
	printf("#cisfun$ ");
	fflush(stdout);

	read = getline(&buffer, &num, stdin);
	if (read == -1)
	  {
	    if (feof(stdin))
	      {
		printf("\n");
		break;
	      }
	    else
	      {
		perror("getline() fails!!!\n");
		return (-1);
	      }
	  }
	
	while (buffer[max] != '\n')
	  max++;
	buffer[max] = '\0';
	
	pid = fork();

	if (pid < 0)
	  {
	    perror("fork error!!!\n");
	    return (-1);
	  }
	else if (pid == 0)
	  {
	    i = 0;
	token[i] = strtok(buffer, " ");
	while (token[i])
	  {
	    i++;
	    token[i] = strtok(NULL, " ");
	  }
	
	    if (i > 1)
	      {
		printf("%s: No such file or directory\n", argv[0]);
		return (-1);
	      }

	    printf("##%s##%s##", token[0], token[1]);
	    fflush(stdout);
	    
	    if (execve(token[0], token, envp) == -1)
	      {
		printf("%s: error No such file or directory\n", argv[0]);
		free(buffer);
		buffer = NULL;
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
