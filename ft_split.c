/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmichel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:38:28 by lmichel           #+#    #+#             */
/*   Updated: 2021/10/11 18:39:20 by lmichel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_freearr(char **ret)
{
	unsigned int	i;

	i = 0;
	while (ret[i])
		free(ret[i++]);
	free(ret);
	return (NULL);
}

static size_t	ft_hmstr(char const *str, char c)
{
	size_t			i;
	size_t			ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if ((str[i] != c && str[i + 1] && str[i + 1] == c)
			|| (str[i] != c && !str[i + 1]))
			ret++;
		i++;
	}
	return (ret);
}

static size_t	ft_hmchr(const char *str, char c)
{
	size_t			i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	size_t			i;
	size_t			j;
	char			**ret;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	ret = malloc((ft_hmstr(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (s[i++] == c)
		j++;
	i = 0;
	while (i < ft_hmstr(s, c))
	{
		ret[i] = ft_substr(s, j, ft_hmchr(&s[j], c));
		if (!(ret[i++]))
			return (ft_freearr(ret));
		j += ft_hmchr(&s[j], c);
		while (s[j] == c)
			j++;
	}
	ret[i] = NULL;
	return (ret);
}
