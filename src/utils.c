/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:34:19 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/07/29 12:58:25 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(char *error_msg)
{
	if (errno)
		perror(error_msg);
	else
		ft_putendl_fd(error_msg, 2);
	exit (1);
}

void	free_matrix(char ***matrix)
{
	int	i;

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
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*ft_find_program(char *env[], char *program)
{
	char	*full_path;
	char	**paths;
	char	*program_path;
	char	*program_name;
	int		i;

	full_path = ft_getenv(env, "PATH");
	if (!full_path)
		ft_error("Error while searching env 'PATH' variable!");
	paths = ft_split(ft_strchr(full_path, '=') + 1, ':');
	program_name = ft_strjoin("/", program);
	i = 0;
	while (paths[i])
	{
		program_path = ft_strjoin(paths[i], program_name);
		if (access(program_path, F_OK) == 0)
			return (program_path);
		free(program_path);
		i++;
	}
	free_matrix(&paths);
	return (free(program_name), NULL);
}

void	subprocess(char *cmd, char *env[])
{
	char	**program_args;
	char	*program_path;

	if (!cmd || !*cmd || ft_iswhitespace(*cmd))
		ft_error("Error invalid program!");
	program_args = ft_split(cmd, ' ');
	program_path = ft_find_program(env, program_args[0]);
	if (program_path)
		execve(program_path, program_args, env);
	free_matrix(&program_args);
	free(program_path);
	ft_error("Error while executing program!");
}
