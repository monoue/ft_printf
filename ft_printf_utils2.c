/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:58:29 by monoue            #+#    #+#             */
/*   Updated: 2020/08/20 15:00:40 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_strdup(const char *original_s)
{
	char	*duplicated_s;
	size_t	index;

	if (!original_s)
		return (NULL);
	duplicated_s = malloc(ft_strlen(original_s) + 1);
	if (duplicated_s == NULL)
		return (NULL);
	index = 0;
	while (original_s[index] != '\0')
	{
		duplicated_s[index] = original_s[index];
		index++;
	}
	duplicated_s[index] = '\0';
	return (duplicated_s);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_index;
	size_t	s2_index;
	char	*joined_str;

	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	joined_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined_str)
		return (NULL);
	s1_index = 0;
	while (s1 && s1[s1_index])
	{
		joined_str[s1_index] = s1[s1_index];
		s1_index++;
	}
	s2_index = 0;
	while (s2 && s2[s2_index])
	{
		joined_str[s1_index + s2_index] = s2[s2_index];
		s2_index++;
	}
	joined_str[s1_index + s2_index] = '\0';
	return (joined_str);
}

char		*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	SAFE_FREE(s1);
	SAFE_FREE(s2);
	return (joined_str);
}

char		*ft_substr(char *original_s, int start, int len)
{
	char	*sub_s;
	int		srclen;
	int		minlen;
	size_t	original_index;
	size_t	sub_index;

	if (original_s == NULL)
		return (NULL);
	srclen = ft_strlen(original_s);
	if (start > srclen)
		return (ft_strdup(""));
	minlen = MIN(srclen - start, len);
	sub_s = malloc(sizeof(*sub_s) * (minlen + 1));
	if (sub_s == NULL)
		return (NULL);
	sub_index = 0;
	original_index = start;
	while (minlen > 0)
	{
		sub_s[sub_index++] = original_s[original_index++];
		minlen--;
	}
	sub_s[sub_index] = '\0';
	return (sub_s);
}
