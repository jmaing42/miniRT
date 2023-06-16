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

#include <stdlib.h>

t_err	minirt_strndup(const char *src, size_t length, char **out)
{
	char	*result;
	size_t	i;

	result = malloc(length + 1);
	if (!result)
		return (true);
	i = -1;
	while (++i < length)
		result[i] = src[i];
	result[length] = '\0';
	*out = result;
	return (false);
}
