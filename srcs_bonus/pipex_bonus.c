/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:32:43 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 11:40:32 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child(t_pipe_bonus_info *info, char **argv,
					char **envp, int child_num)
{
	char	*path;
	char	**cmd_args;

	if (child_num == 0)
		if (info->infile_fd < 0)
			write_file_error(argv);
	close_unused_pipes(info, child_num);
	manage_dups(info, child_num);
	cmd_args = split_pipex((info->cmds)[child_num], ' ');
	if (!cmd_args)
		exit(EXIT_COMMAND_NOT_FOUND);
	if (!strncmp(cmd_args[0], "./", 2))
		path = cmd_args[0];
	else if (!(*envp))
		path = ft_strjoin(DEFAULT_CMD_PATH, cmd_args[0]);
	else
		path = find_cmd_path(envp, cmd_args[0]);
	execute_cmd_bonus(info, path, cmd_args, envp);
}

void	start_childs(char **argv, char **envp, t_pipe_bonus_info *info)
{
	int	i;

	info->pid = malloc(sizeof (pid_t) * info->cmd_num);
	if (!(info->pid))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < info->cmd_num)
	{
		(info->pid)[i] = fork();
		if ((info->pid)[i] == 0)
			child(info, argv, envp, i);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_bonus_info	info;
	int					status;

	if (argc < 5)
		return (1);
	else
	{
		if (!ft_strcmp(argv[1], "here_doc"))
			info.here_doc = 1;
		else
			info.here_doc = 0;
	}
	get_infile(argv, &info);
	get_outfile(argc, argv, &info);
	info.cmd_num = argc - 3 - info.here_doc;
	get_cmds(argv, &info);
	get_pipes(&info);
	start_childs(argv, envp, &info);
	close_everything_bonus(&info);
	waitpid((info.pid)[info.cmd_num - 1], &status, 0);
	free_everything_bonus(&info);
	return (WEXITSTATUS(status));
}
