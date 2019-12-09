/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:09:28 by rofernan          #+#    #+#             */
/*   Updated: 2019/11/22 14:34:53 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_set(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = ft_strlen(s1);
	k = 0;
	if (!s1 || !set)
		return (NULL);
	while (check_set(s1[i], set))
		i++;
	while (check_set(s1[j - 1], set) && j > i)
		j--;
	if (!(str = malloc(sizeof(*str) * (j - i + 1))))
		return (NULL);
	while (i < j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}
