/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:24:44 by jcameira          #+#    #+#             */
/*   Updated: 2023/12/27 15:41:30 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	manage_dups(t_pipe_bonus_info *info, int child_num)
{
	if (child_num == 0)
	{
		dup2(info->pipe_ends[child_num][1], 1);
		dup2(info->infile_fd, 0);
	}
	else if (child_num > 0 && child_num < info->cmd_num - 1)
	{
		dup2(info->pipe_ends[child_num][1], 1);
		dup2(info->pipe_ends[child_num - 1][0], 0);
	}
	else
	{
		dup2(info->outfile_fd, 1);
		dup2(info->pipe_ends[child_num - 1][0], 0);
	}
}

void	get_pipes(t_pipe_bonus_info *info)
{
	int	i;

	info->pipe_ends = malloc(sizeof (int *) * (info->cmd_num - 1));
	if (!(info->pipe_ends))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < info->cmd_num - 1)
	{
		info->pipe_ends[i] = malloc(sizeof (int) * 2);
		pipe(info->pipe_ends[i]);
	}
}

void	get_cmds(char **argv, t_pipe_bonus_info *info)
{
	int	i;
	int	j;

	info->cmds = malloc(sizeof (char *) * info->cmd_num);
	if (!(info->cmds))
		exit(EXIT_FAILURE);
	i = 0;
	j = 2 + info->here_doc;
	while (i < info->cmd_num)
		(info->cmds)[i++] = argv[j++];
}
