/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:40:41 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/28 22:29:23 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*memcpy_pipex(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	j;

	if (!dest && !src)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (((unsigned char *)src)[i] == '\\'
			&& ((unsigned char *)src)[i + 1] == '\'')
			i++;
		else if (((unsigned char *)src)[i] == '\\'
			&& ((unsigned char *)src)[i + 1] == '"')
			i++;
		((unsigned char *)dest)[j] = ((unsigned char *)src)[i];
		i++;
		j++;
	}
	return (dest);
}

char	*substr_pipex(char const *str, unsigned int start,
	size_t len, int special_char)
{
	char	*substr;

	if (!str)
		return (NULL);
	if (len >= ft_strlen(str) - start)
		len = ft_strlen(str) - start;
	if (start > ft_strlen(str))
		len = 0;
	substr = malloc(sizeof (char) * (len - special_char + 1));
	if (!substr)
		return (NULL);
	substr = memcpy_pipex(substr, (const void *)(str + start),
			len);
	substr[len - special_char] = '\0';
	return (substr);
}

static void	go_through_word(char const *str, char c, int *i, int *words)
{
	(*words)++;
	while (str[(*i)] && str[(*i)] != c)
	{
		if (str[(*i)] && str[(*i)] == '\\' && str[(*i) + 1] == c)
			(*i)++;
		(*i)++;
	}
}

int	word_count_pipex(char const *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] == '\'')
		{
			i++;
			go_through_word(str, '\'', &i, &words);
		}
		else if (str[i] && str[i] == '"')
		{
			i++;
			go_through_word(str, '"', &i, &words);
		}
		else if (str[i] && str[i] != c)
			go_through_word(str, c, &i, &words);
	}
	return (words);
}

void	*free_matrix(char **matrix, int word)
{
	while (word >= 0)
	{
		free(matrix[word]);
		matrix[word] = NULL;
		word--;
	}
	free(matrix);
	return (NULL);
}
