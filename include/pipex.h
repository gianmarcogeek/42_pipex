/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:22:10 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/07/26 12:34:28 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

void	ft_error(char *error_msg);
void	free_matrix(char ***matrix);
char	*ft_getenv(char *env[], char *var);
char	*ft_find_program(char *env[], char *program);
void	subprocess(char *cmd, char *env[]);

#endif
