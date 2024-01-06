/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:03:05 by jcameira          #+#    #+#             */
/*   Updated: 2023/12/27 18:07:39 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_init(char *limiter, t_pipe_bonus_info *info)
{
	int		fd;
	char	*line;

	fd = open(HERE_DOC, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (TRUE)
	{
		ft_putstr_fd(HERE_DOC_INDICATOR, 1);
		line = get_next_line(INPUT);
		line = ft_strtrim(line, "\n");
		if (!ft_strcmp(line, limiter))
			break ;
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	free(line);
	close(fd);
	info->infile_fd = open(HERE_DOC, O_RDONLY);
	if (info->infile_fd < 0)
		unlink(HERE_DOC);
}

void	get_infile(char **argv, t_pipe_bonus_info *info)
{
	if (info->here_doc)
		here_doc_init(argv[2], info);
	else
		info->infile_fd = open(argv[1], O_RDONLY);
}

void	get_outfile(int argc, char **argv, t_pipe_bonus_info *info)
{
	if (info->here_doc)
		info->outfile_fd = open(argv[argc - 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		info->outfile_fd = open(argv[argc - 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (info->outfile_fd && access(argv[argc - 1], W_OK))
		exit(EXIT_INCORRECT_USAGE);
}
