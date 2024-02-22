/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:55:26 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 20:36:42 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define DEFAULT_CMD_PATH "/usr/bin/"
# define DEFAULT_ERROR_MSG_PREFIX "pipex: line 1: "
# define COMMAND_ERROR_MSG ": command not found\n"
# define EXIT_FAILURE 1
# define EXIT_INCORRECT_USAGE 2
# define EXIT_PERMISSION_DENIED 126
# define EXIT_COMMAND_NOT_FOUND 127

typedef struct s_pipe_info
{
	pid_t	pid;
	pid_t	pid2;
	int		pipe_ends[2];
	int		infile_fd;
	int		outfile_fd;
	char	*cmds[2];
}	t_pipe_info;

void	execute_cmd(t_pipe_info *info, char *path, char **cmd_args,
			char **envp);
char	*write_command_path(char **cmd_paths, char *cmd);
char	*find_cmd_path(char **envp, char *cmd);
char	**split_pipex(char const *str, char c);
void	*memcpy_pipex(void *dest, const void *src, size_t n);
char	*substr_pipex(char const *str, unsigned int start,
			size_t len, int special_char);
int		word_count_pipex(char const *str, char c);
void	*free_matrix(char **matrix, int word);
void	free_cmds(char **cmd_args);
void	close_everything(t_pipe_info *info);
void	write_command_error(char **cmd_args);
void	write_file_error(char **argv);
void	execute_error(t_pipe_info *info, char **cmd_args);

#endif