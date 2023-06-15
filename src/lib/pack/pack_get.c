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

#include "minirt/pack.h"

#include "minirt/common/libc.h"

static bool	find(t_minirt_pack *self, const char *name, size_t *out_index)
{
	t_minirt_pack_node *const	node = (t_minirt_pack_node *)self->array;
	size_t						i;

	i = -1;
	while (++i < self->node_count)
	{
		if (minirt_str_eq(
				name,
				(const char *)&self->array[node[i].name_offset]))
		{
			*out_index = i;
			return (true);
		}
	}
	return (false);
}

bool	minirt_pack_get(
	t_minirt_pack *self,
	const char *name,
	void **out,
	size_t *out_length
)
{
	size_t		index;
	const bool	result = find(self, name, &index);

	if (result)
	{
		*out = &self->array[
			((t_minirt_pack_node *)&self->array[index])->content_offset];
		*out_length
			= ((t_minirt_pack_node *)&self->array[index])->content_length;
	}
	return (result);
}
