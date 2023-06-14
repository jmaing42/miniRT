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

#include "json_internal.h"

#include <stdlib.h>

#include "minirt/common/libc.h"

char	*minirt_json_stringbuilder_to_string(
	t_minirt_json_stringbuilder *self,
	size_t offset
)
{
	char *const							result
		= malloc(self->length - offset + 1);
	t_minirt_json_stringbuilder_node	*node;
	size_t								position;

	if (!result)
		return (NULL);
	result[self->length - offset] = '\0';
	if (!self->length)
		return (result);
	node = self->head;
	position = 0;
	minirt_memcpy(
		(void *)&result[position],
		&node->str[offset],
		node->length - offset);
	position += node->length - offset;
	node = node->next;
	while (node)
	{
		minirt_memcpy((void *)&result[position], node->str, node->length);
		position += node->length;
		node = node->next;
	}
	return (result);
}
