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

bool	minirt_starts_with(const char *self, const char *starts, size_t *out)
{
	size_t	i;

	i = 0;
	while (self[i] && starts[i] && self[i] == starts[i])
		i++;
	if (starts[i])
	{
		if (out)
			*out = i;
		return (true);
	}
	return (false);
}
