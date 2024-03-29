/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:23:20 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 20:52:33 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_error(t_pipe_info *info, char **cmd_args)
{
	char	*error;

	error = ft_strjoin(DEFAULT_ERROR_MSG_PREFIX, cmd_args[0]);
	perror(error);
	close_everything(info);
	free_cmds(cmd_args);
	free(error);
}

void	write_command_error(char **cmd_args)
{
	ft_putstr_fd(DEFAULT_ERROR_MSG_PREFIX, 2);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(COMMAND_ERROR_MSG, 2);
	free_cmds(cmd_args);
	exit(EXIT_COMMAND_NOT_FOUND);
}

void	write_file_error(char **argv)
{
	char	*error;

	error = ft_strjoin(DEFAULT_ERROR_MSG_PREFIX, argv[1]);
	perror(error);
	free(error);
	exit(EXIT_FAILURE);
}
