/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_file_name (file name is useless too)          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42header-remover <whatever@example.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by file history     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt/common/libc.h"

bool	minirt_strchr(const char *str, char c, size_t *out)
{
	size_t	i;

	i = (size_t)-1;
	while (str[++i])
	{
		if (str[i] == c)
		{
			*out = i;
			return (true);
		}
	}
	*out = i;
	return (false);
}
