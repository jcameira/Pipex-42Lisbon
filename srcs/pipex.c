/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:54:39 by jcameira          #+#    #+#             */
/*   Updated: 2023/12/27 15:38:28 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parent(t_pipe_info *info, char **argv, char **envp)
{
	char	*path;
	char	**cmd_args;

	if (info->outfile_fd < 0)
		write_file_error(argv);
	close(info->pipe_ends[1]);
	dup2(info->pipe_ends[0], 0);
	dup2(info->outfile_fd, 1);
	cmd_args = split_pipex((info->cmds)[1], ' ');
	if (!cmd_args)
		exit(EXIT_COMMAND_NOT_FOUND);
	if (!strncmp(cmd_args[0], "./", 2))
		path = cmd_args[0];
	else if (!(*envp))
		path = ft_strjoin(DEFAULT_CMD_PATH, cmd_args[0]);
	else
		path = find_cmd_path(envp, cmd_args[0]);
	execute_cmd(path, cmd_args, envp);
}

static void	child(t_pipe_info *info, char **argv, char **envp)
{
	char	*path;
	char	**cmd_args;

	if (info->infile_fd < 0)
		write_file_error(argv);
	close(info->pipe_ends[0]);
	dup2(info->pipe_ends[1], 1);
	dup2(info->infile_fd, 0);
	cmd_args = split_pipex((info->cmds)[0], ' ');
	if (!cmd_args)
		exit(EXIT_COMMAND_NOT_FOUND);
	if (!strncmp(cmd_args[0], "./", 2))
		path = cmd_args[0];
	else if (!(*envp))
		path = ft_strjoin(DEFAULT_CMD_PATH, cmd_args[0]);
	else
		path = find_cmd_path(envp, cmd_args[0]);
	execute_cmd(path, cmd_args, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_info	info;
	int			status;

	if (argc != 5)
		return (1);
	info.infile_fd = open(argv[1], O_RDONLY);
	info.outfile_fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (info.outfile_fd && access(argv[4], W_OK))
		exit(EXIT_INCORRECT_USAGE);
	(info.cmds)[0] = argv[2];
	(info.cmds)[1] = argv[3];
	if (pipe(info.pipe_ends) < 0)
		exit(EXIT_FAILURE);
	info.pid = fork();
	if (info.pid == 0)
		child(&info, argv, envp);
	info.pid2 = fork();
	if (info.pid2 == 0)
		parent(&info, argv, envp);
	close_everything(&info);
	waitpid(info.pid2, &status, 0);
	return (WEXITSTATUS(status));
}