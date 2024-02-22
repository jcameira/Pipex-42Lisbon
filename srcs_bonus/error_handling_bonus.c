/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:50:32 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/22 13:39:50 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_command_error_bonus(t_pipe_bonus_info *info, char **cmd_args)
{
	ft_putstr_fd(DEFAULT_ERROR_MSG_PREFIX, 2);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(COMMAND_ERROR_MSG, 2);
	free_cmds(cmd_args);
	free_everything_bonus(info);
	exit(EXIT_COMMAND_NOT_FOUND);
}
