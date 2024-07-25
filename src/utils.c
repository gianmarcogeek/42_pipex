/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:34:19 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/07/25 17:56:26 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(char *error_msg)
{
	if(errno)
		perror(error_msg);
	else
		ft_putendl_fd(error_msg, 2);
	exit (1);
}

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
	return (NULL);
}

char	*ft_find_program(char *env[], char *program)
{
	char *full_path; 
	char **paths;
	char *program_path;
	char *program_name;
	int i;
	
	full_path = ft_getenv(env, "PATH");
	if (!full_path)
		ft_error("Error while searching env path");
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
		return(free(program_name), program_path);
	}
	return(NULL);
}

void	subprocess(char *cmd, char *env[])
{
	char **program_args;
	char *program_path;

	program_args = ft_split(cmd, ' ');
	program_path = ft_find_program(env, program_args[0]);
	if (!program_path)
		ft_error("Error program not found");
	execve(program_path, program_args, env);
	ft_error("Program does not exist");
	//free(program_path)
}
