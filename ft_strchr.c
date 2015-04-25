/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <mbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 23:08:08 by mbooth            #+#    #+#             */
/*   Updated: 2014/11/11 19:37:46 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		to_find;
	char	*s2;

	to_find = (char)c;
	s2 = (char *)s;
	i = 0;
	while (s2[i] != '\0')
	{
		if (s2[i] == to_find)
			return (s2 + i);
		i++;
	}
	if (s2[i] == '\0' && to_find == '\0')
		return (s2 + i);
	return (NULL);
}
