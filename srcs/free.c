/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:09:36 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 16:11:19 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmds(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		free(cmd_args[i++]);
	free(cmd_args);
}

void	close_everything(t_pipe_info *info)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (info->pipe_ends[0] >= 0)
		close(info->pipe_ends[0]);
	if (info->pipe_ends[1] >= 0)
		close(info->pipe_ends[1]);
	if (info->infile_fd >= 0)
		close(info->infile_fd);
	if (info->infile_fd >= 0)
		close(info->outfile_fd);
}
