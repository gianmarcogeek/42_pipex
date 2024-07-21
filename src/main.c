/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:00:12 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/07/21 17:58:37 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_matrix(char ***matrix)
{
	int i = 0;
	
	while((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
}

char *ft_getenv(char *env[], char *var)
{
	int i;

	i = 0;
	while (env[i])
	{
		if(ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return(env[i]);
		i++;
	}
	//error
	return (NULL);
}

char *ft_find_program(char *env[], char *program_name)
{
	char *full_path = ft_getenv(env, "PATH");
	char **paths = ft_split(ft_strchr(full_path, '=') + 1, ':');
	int i = 0;
	char *program_path = ft_strjoin(paths[i], program_name);

	while(access(program_path, F_OK) != 0 && paths[i])
	{
		free(program_path);
		i++;
		program_path = ft_strjoin(paths[i], program_name);
	}
	if(paths[i])
		return(free_matrix(&paths), program_path);
	//error
	return(NULL);
}

int main(int argc, char *argv[], char *env[])
{
	if(argc && argv)
	{
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork() failed.\n");
			exit(1);
		}
		else if (pid == 0)
		{
			//child
			//look inside argv[1] for program name
			//program_path = ft_find_path(env, argv[1]);
			char *program_path = ft_find_program(env, argv[1]);
			if(program_path)
			{
				ft_printf(" %s \n", program_path);
				free(program_path);
			}
			return (0);
		}
		else
		{
			//parent
			wait(NULL);
			ft_printf("tornato al processo padre!\n");
			return(0);
		}
	}
}