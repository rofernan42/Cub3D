/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:38:20 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/16 12:04:42 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int param)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1 || !s2
	|| !(dest = malloc(sizeof(*dest) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[j])
		dest[i++] = s1[j++];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	if (param == 0)
		ft_strdel(&s2);
	if (param == 1)
		ft_strdel(&s1);
	if (param == 2)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (dest);
}
