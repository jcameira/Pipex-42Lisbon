/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:32:40 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 21:03:05 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../srcs/pipex.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line_bonus.h"

# define TRUE 1
# define DEFAULT_MIN_ARGS 5
# define HERE_DOC ".here_doc"
# define HERE_DOC_INDICATOR "pipe heredoc> "
# define INPUT 0

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

void	execute_cmd_bonus(t_pipe_bonus_info *info, char *path, char **cmd_args,
			char **envp);
void	get_pipes(t_pipe_bonus_info *info);
void	get_cmds(char **argv, t_pipe_bonus_info *info);
void	here_doc_init(char *limiter, t_pipe_bonus_info *info);
void	get_infile(char **argv, t_pipe_bonus_info *info);
void	get_outfile(int argc, char **argv, t_pipe_bonus_info *info);
void	close_unused_pipes(t_pipe_bonus_info *info, int child_num);
void	manage_dups(t_pipe_bonus_info *info, int child_num);
void	close_everything_bonus(t_pipe_bonus_info *info);
void	free_everything_bonus(t_pipe_bonus_info *info);
void	write_command_error_bonus(t_pipe_bonus_info *info, char **cmd_args);
void	execute_error_bonus(t_pipe_bonus_info *info, char **cmd_args);

#endif