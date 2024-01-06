/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:32:40 by jcameira          #+#    #+#             */
/*   Updated: 2023/12/27 17:53:00 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line_bonus.h"

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define TRUE 1
# define DEFAULT_CMD_PATH "/usr/bin/"
# define DEFAULT_ERROR_MSG_PREFIX "pipex: line 1: "
# define DEFAULT_MIN_ARGS 5
# define HERE_DOC_ARGS 6
# define HERE_DOC ".here_doc"
# define HERE_DOC_INDICATOR "pipe heredoc> "
# define INPUT 0
# define EXIT_FAILURE 1
# define EXIT_INCORRECT_USAGE 2
# define EXIT_COMMAND_NOT_FOUND 127

typedef struct s_pipe_bonus_info
{
	pid_t	*pid;
	int		**pipe_ends;
	int		infile_fd;
	int		outfile_fd;
	int		here_doc;
	int		cmd_num;
	char	**cmds;
}	t_pipe_bonus_info;

void	execute_cmd(char *path, char **cmd_args, char **envp);
char	*write_command_path(char **cmd_paths, char *cmd);
char	*find_cmd_path(char **envp, char *cmd);
char	**split_pipex(char const *str, char c);
void	*memcpy_pipex(void *dest, const void *src, size_t n);
char	*substr_pipex(char const *str, unsigned int start,
			size_t len, int special_char);
int		word_count_pipex(char const *str, char c);
void	*free_matrix(char **matrix, int word);
void	free_cmds(char **cmd_args);
void	write_command_error(char **cmd_args);
void	write_file_error(char **argv);
void	get_pipes(t_pipe_bonus_info *info);
void	get_cmds(char **argv, t_pipe_bonus_info *info);
void	here_doc_init(char *limiter, t_pipe_bonus_info *info);
void	get_infile(char **argv, t_pipe_bonus_info *info);
void	get_outfile(int argc, char **argv, t_pipe_bonus_info *info);
void	close_unused_pipes(t_pipe_bonus_info *info, int child_num);
void	manage_dups(t_pipe_bonus_info *info, int child_num);
void	close_everything_bonus(t_pipe_bonus_info *info);
void	free_everything_bonus(t_pipe_bonus_info *info);

#endif