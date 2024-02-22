/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:03:05 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 16:17:17 by jcameira         ###   ########.fr       */
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
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!ft_strcmp(line, limiter))
			break ;
		ft_putendl_fd(line, fd);
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
