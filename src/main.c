/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:00:12 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/07/21 19:40:21 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//use with ./pipex "ls -l ./lib"

void	free_matrix(char ***matrix)
{
	int i;

	i = 0;
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

char *ft_find_program(char *env[], char *program)
{
	char *full_path; 
	char **paths;
	char *program_path;
	char *program_name;
	int i;
	
	full_path= ft_getenv(env, "PATH");
	paths = ft_split(ft_strchr(full_path, '=') + 1, ':');
	i = 0;
	program_name = ft_strjoin("/", program);
	program_path = ft_strjoin(paths[i], program_name);
	while(access(program_path, F_OK) != 0 && paths[i])
	{
		free(program_path);
		i++;
		program_path = ft_strjoin(paths[i], program_name);
	}
	if(paths[i])
	{
		free_matrix(&paths);
		free(program_name);
		return(program_path);
		
	}
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
			// int infile = open(argv[1], O_RDWR);
			// dup2(infile, 0);
			char **argus = ft_split(argv[1], ' ');
			char *program_path = ft_find_program(env, argus[0]);
			if(program_path)
			{
				execve(program_path, argus, env);
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