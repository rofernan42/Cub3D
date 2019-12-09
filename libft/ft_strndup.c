/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 13:37:38 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/09 14:36:34 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!(dest = malloc(sizeof(*dest) * (n + 1))))
		return (NULL);
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	if (n > ft_strlen(src))
	{
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}
