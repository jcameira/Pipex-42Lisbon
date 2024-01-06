/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:24:08 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/28 22:29:13 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	find_special_char(char const *str, char c, int *j, int *i)
{
	int	special_char;

	special_char = 0;
	while (str[(*i) + (*j)] && str[(*i) + (*j)] != c)
	{
		if (str[(*i) + (*j)] && str[(*i) + (*j)] == '\\')
		{
			special_char++;
			(*j)++;
		}
		(*j)++;
	}
	return (special_char);
}

static int	split_d_quotes(char **matrix, char const *str, int *word, int *i)
{
	int	j;
	int	special_char;

	j = 0;
	special_char = 0;
	(*i)++;
	while (str[(*i) + j] && str[(*i) + j] != '"')
	{
		if (str[(*i) + j] && str[(*i) + j] == '\\')
		{
			special_char++;
			j++;
		}
		j++;
	}
	matrix[(*word)++] = substr_pipex(str, *i, j, special_char);
	if (!matrix[(*word) - 1])
		free_matrix(matrix, (*word) - 1);
	return (j);
}

static void	split_s_quotes(char **matrix, char const *str, int *word, int *i)
{
	int	j;
	int	special_char;

	j = 0;
	special_char = 0;
	if (str[(*i)] && str[(*i)] == '\'')
	{
		(*i)++;
		while (str[(*i) + j] && str[(*i) + j] != '\'')
		{
			if (str[(*i) + j] && str[(*i) + j] == '\\')
			{
				special_char++;
				j++;
			}
			j++;
		}
		matrix[(*word)++] = substr_pipex(str, *i, j, special_char);
		if (!matrix[(*word) - 1])
			free_matrix(matrix, (*word) - 1);
	}
	else if (str[(*i)] && str[(*i)] == '"')
		j = split_d_quotes(matrix, str, word, i);
	(*i) += j + 1;
}

static void	*fill_matrix(char **matrix, char const *str, char c)
{
	int		i;
	int		j;
	int		word;
	int		special_char;

	i = 0;
	word = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] && str[i] == c)
			i++;
		else if (str[i] && (str[i] == '\'' || str[i] == '"'))
			split_s_quotes(matrix, str, &word, &i);
		else if (str[i] && str[i] != c)
		{
			special_char = find_special_char(str, c, &j, &i);
			matrix[word++] = substr_pipex(str, i, j, special_char);
			if (!matrix[word - 1])
				return (free_matrix(matrix, word - 1));
			i += j;
		}
	}
	matrix[word] = 0;
	return (matrix);
}

char	**split_pipex(char const *str, char c)
{
	char	**matrix;

	matrix = (char **)malloc(sizeof (char *) * (word_count_pipex(str, c) + 1));
	if (!matrix)
		return (NULL);
	matrix = fill_matrix(matrix, str, c);
	return (matrix);
}
