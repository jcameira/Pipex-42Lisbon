/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 20:36:15 by jcameira          #+#    #+#             */
/*   Updated: 2023/12/27 18:51:15 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_unused_pipes(t_pipe_bonus_info *info, int child_num)
{
	int	i;

	i = -1;
	while (++i < info->cmd_num - 1)
	{
		if (i == child_num)
		{
			if (child_num != info->cmd_num - 1)
			{
				close(info->pipe_ends[i][0]);
			}
			else
			{
				close(info->pipe_ends[i][1]);
			}
		}
		else if (i == child_num - 1)
			close(info->pipe_ends[i][1]);
		else
		{
			close(info->pipe_ends[i][0]);
			close(info->pipe_ends[i][1]);
		}
	}
}

void	close_everything_bonus(t_pipe_bonus_info *info)
{
	int	i;

	close(info->infile_fd);
	close(info->outfile_fd);
	i = -1;
	while (++i < info->cmd_num - 1)
	{
		close(info->pipe_ends[i][0]);
		close(info->pipe_ends[i][1]);
	}
	if (info->here_doc)
		unlink(HERE_DOC);
}

void	free_everything_bonus(t_pipe_bonus_info *info)
{
	int	i;

	free(info->pid);
	i = -1;
	while (++i < info->cmd_num - 1)
		free((info->pipe_ends)[i]);
	free(info->pipe_ends);
	free(info->cmds);
}
