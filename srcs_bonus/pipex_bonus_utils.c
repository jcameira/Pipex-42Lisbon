/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:24:44 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 21:03:38 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd_bonus(t_pipe_bonus_info *info, char *path, char **cmd_args,
			char **envp)
{
	if (!path || access(path, 0) || (!access(path, 0)
			&& !ft_strchr(path, '/')
			&& !ft_strncmp(path + ft_strlen(path) - 3, ".sh", 3)
			&& ft_strncmp(path, "./", 2)))
	{
		close_everything_bonus(info);
		write_command_error_bonus(info, cmd_args);
	}
	if (access(path, X_OK) == -1)
	{
		execute_error_bonus(info, cmd_args);
		exit(EXIT_PERMISSION_DENIED);
	}
	if (execve(path, cmd_args, envp) < 0)
	{
		execute_error_bonus(info, cmd_args);
		exit(errno);
	}
}

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
