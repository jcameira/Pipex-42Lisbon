/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:09:36 by jcameira          #+#    #+#             */
/*   Updated: 2023/12/22 20:34:57 by jcameira         ###   ########.fr       */
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
	close(info->pipe_ends[0]);
	close(info->pipe_ends[1]);
	close(info->infile_fd);
	close(info->outfile_fd);
}
