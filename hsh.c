#include "main.h"

int is_exe(char *filename)
{
	extern char **environ;
	char **envcp = environ;
	int i;
	char *pathcp, *pathtok, *cat_path;

	if (filename == NULL)
	{
		return (-1);
	}
	if (access(filename, F_OK | X_OK) == 0)
	{
		return (1);
	}
	else
	{
		for (i = 0; *envcp != NULL; i++)
		{
			if (_strncmp(*envcp, "PATH=", 5) == 0)
			{
				pathcp = _strdup(*envcp + 5);
                if (!pathcp)
                {
                    perror("PATH not found");
                    return (0);
                }
				break;
			}
			envcp++;
		}
	}
	pathtok = strtok(pathcp, ":");

	while (pathtok != NULL)
	{
		cat_path = _cat3(pathcp, "/", pathtok);
		if (access(cat_path, F_OK | X_OK) == 0)
		{
			free(cat_path);
			free(pathcp);
			return (1);
		}
		free(cat_path);
		pathtok = strtok(NULL, ":");
	}

	free(pathcp);
	perror("./hsh");
	return (0);
}


int main(void)
{
    size_t n = 0;
    char *buffer = NULL, *del = " ";
    ssize_t read_line;
    int count, i, status;
    char **argv;
	pid_t child_pid; 

    while (1)
    {

        read_line = getline(&buffer, &n, stdin);

        if (read_line == -1)
        {
            free(buffer);
            exit(EXIT_SUCCESS);
        }

        if (read_line > 0 && buffer[read_line - 1] == '\n')
        {
            buffer[read_line - 1] = '\0';

			if (buffer[0] == '\0')
			{
            	free(buffer);
            	continue;
        	}
        }

	if (_strncmp(buffer, "exit", _strlen("exit")) == 0)
	{
		free(buffer);
    	break;
	}

	argv = split(buffer, del, &count);
        if (is_exe(argv[0]))
        {

        
		
        	child_pid = fork();

        	if (child_pid == -1)
        	{
            	perror("fork");
            	free(buffer);
            	free(argv);
            	exit(EXIT_FAILURE);
    		}

        	if (child_pid == 0)
        	{
            	if (execvp(argv[0], argv) == -1)
            	{
                	perror("execvp");
                	free(buffer);
                	free(argv);
                	exit(EXIT_FAILURE);
            	}
				exit(EXIT_SUCCESS);
        	}
        	else
        	{
        	    waitpid(child_pid, &status, 0);
        	}
		
        for (i = 0; i < count; i++)
        {
            free(argv[i]);
        }
        free(argv);
		}
		else
		{
				for (i = 0; i < count; i++)
        	{
            	free(argv[i]);
        	}
        	free(argv);
			continue;
		}
    }
	

    free(buffer);
    return (0);
}