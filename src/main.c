/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:00:12 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/07/22 16:52:01 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_matrix(char ***matrix)
{
	int i;

	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
}

char	*ft_getenv(char *env[], char *var)
{
	int i;

	i = 0;
	while (env[i])
	{
		if(ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return(env[i]);
		i++;
	}

	perror("Env search error");
	exit(1);
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

	perror("Program not found");
	exit(1);
}

int main(int argc, char *argv[], char *env[])
{
	if(argc == 5)
	{
		pid_t fork1;
		int fd[2];

		fork1 = 0;
		pipe(fd);
		fork1 = fork();
		if (fork1 < 0)
		{
			perror("Fork() failed.\n");
			exit(1);
		}
		else if (fork1 == 0)
		{
			int infile = open(argv[1], O_RDWR);
			dup2(infile, 0);
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			if(argv[2])
			{
				char **argus = ft_split(argv[2], ' ');
				char *program_path = ft_find_program(env, argus[0]);
				if(program_path)
				{
					execve(program_path, argus, env);
					free(program_path);
				}
			}	
		}
		else
		{
			wait(NULL);
			pid_t fork2 = fork();
			if(fork2 == 0)
			{
				int outfile = open(argv[4], O_RDWR);
				close(fd[1]);
				dup2(fd[0], 0);
				close(fd[0]);
				if(argv[2])
				{
				char **argus = ft_split(argv[3], ' ');
					char *program_path = ft_find_program(env, argus[0]);
				if(program_path)
				{
					dup2(outfile, 1);
					execve(program_path, argus, env);
					free(program_path);
				}
					return(0);
				}
			}
			

			ft_printf("tornato al processo padre!\n");
			return(0);
			}
			return (0);
		}
	
	perror("Error use './pipex infile cmd1'");
	exit(-1);
}