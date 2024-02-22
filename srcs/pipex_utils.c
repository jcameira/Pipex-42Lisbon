/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:02:05 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 02:12:36 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(t_pipe_info *info, char *path, char **cmd_args, char **envp)
{
	if (!path || access(path, 0) || (!access(path, 0)
			&& !ft_strchr(path, '/')
			&& !ft_strncmp(path + ft_strlen(path) - 3, ".sh", 3)
			&& ft_strncmp(path, "./", 2)))
		write_command_error(cmd_args);
	if (access(path, X_OK) == -1)
	{
		free_cmds(cmd_args);
		exit(126);
	}
	if (execve(path, cmd_args, envp) < 0)
	{
		close_everything(info);
		exit(1);
	}
}

char	*write_command_path(char **cmd_paths, char *cmd)
{
	int		i;
	char	*path;
	char	*complete_path;

	i = -1;
	while (cmd_paths[++i])
	{
		path = ft_strjoin(cmd_paths[i], "/");
		complete_path = ft_strjoin(path, cmd);
		if (!access(complete_path, 0))
		{
			free_cmds(cmd_paths);
			return (complete_path);
		}
		free(path);
		free(complete_path);
	}
	free_cmds(cmd_paths);
	if (!access(cmd, 0))
		return (cmd);
	return (NULL);
}

char	*find_cmd_path(char **envp, char *cmd)
{
	int		i;
	char	*path;
	char	**cmd_paths;

	path = NULL;
	i = -1;
	while (envp[++i])
		if (!ft_strncmp("PATH", envp[i], 4))
			path = ft_strchr(envp[i], '/');
	if (!path || !path[0])
		return (NULL);
	cmd_paths = ft_split(path, ':');
	if (!cmd_paths)
		exit(EXIT_FAILURE);
	return (write_command_path(cmd_paths, cmd));
}
