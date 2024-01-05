#include "shell.h"

/**
 *
 **/

char *get_path(char *command)
  {
    char *real_path = NULL;
    char *env = "";
    char *token;
    env = _strcat(env, getenv("PATH"));
    token = _strtok(env, ":");

    while (token != NULL)
      {
	real_path = _strcat(token, command);
	if (real_path == NULL)
	  {
	    perror("real_path: fail\n");
	    return (NULL);
	  }

	if (!(access(real_path, X_OK)))
	  {
	    free(env);
	    free(command);
	    return (real_path);
	  }
	else
	  {
	    if (real_path != NULL)
	      {
		free(real_path);
		real_path = NULL;
	      }
		token = _strtok(NULL, ":");
	  }
      }

    free(env);
    free(command);

    return (NULL);
  }
