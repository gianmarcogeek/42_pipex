/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:06:08 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/07/25 17:54:03 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void child_main(int fd[], char *argv[], char *env[])
{
	int infile;
	
	close(fd[0]);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		ft_error("Error while opening input file");
	dup2(infile, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	close(infile);
	subprocess(argv[2], env);
}
int main(int argc, char *argv[], char *env[])
{
	pid_t fork_id;
	int fd[2];
	int outfile;
	
	if (argc != 5)
		ft_error("Error! use './pipex infile cmd1 cmd2 outfile'");
	if (pipe(fd) == -1)
		ft_error("Error while creating pipe");
	fork_id = fork();
	if (fork_id < 0)
		ft_error("Error while forking main process");
	else if (fork_id == 0)
		child_main(fd, argv, env);
	wait(NULL);
	close(fd[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (outfile == -1)
		ft_error("Error while opening output file");
	dup2(fd[0], 0);
	dup2(outfile, 1);
	close(fd[0]);
	close(outfile);
	subprocess(argv[3], env);
}
