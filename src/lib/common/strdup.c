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

#include "minirt/common.h"

#include <stdlib.h>

t_err	minirt_strdup(const char *src, char **out)
{
	size_t		length;
	char		*result;
	const char	*tmp;
	char		*temp;

	length = 0;
	tmp = src;
	while (*tmp)
	{
		tmp++;
		length++;
	}
	result = malloc(length + 1);
	if (!result)
		return (true);
	tmp = src;
	temp = result;
	while (*tmp)
		*temp++ = *tmp++;
	*temp = '\0';
	*out = result;
	return (false);
}
