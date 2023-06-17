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

#include <stdlib.h>

#include "minirt/common/libc.h"

static size_t	size(
	t_minirt_pack_in *files,
	size_t file_count
)
{
	size_t	result;
	size_t	i;

	result = 0;
	i = -1;
	while (++i < file_count)
		result += minirt_strlen(files[i].name) + 1 + files[i].content_length;
	return (result);
}

static void	fill(
	t_minirt_pack_in *files,
	size_t file_count,
	unsigned char *out
)
{
	size_t			current_offset;
	size_t			tmp;
	size_t			i;

	current_offset = sizeof(t_minirt_pack_node) * file_count;
	i = -1;
	while (++i < file_count)
	{
		tmp = minirt_strlen(files[i].name) + 1;
		minirt_memcpy(
			&out[current_offset],
			files[i].name,
			tmp);
		((t_minirt_pack_node *)out)[i].name_offset = current_offset;
		current_offset += tmp;
		minirt_memcpy(
			&out[current_offset],
			files[i].content,
			files[i].content_length);
		((t_minirt_pack_node *)out)[i].content_offset = current_offset;
		((t_minirt_pack_node *)out)[i].content_length = files[i].content_length;
		current_offset += files[i].content_length;
	}
}

t_err	minirt_pack(
	t_minirt_pack_in *files,
	size_t file_count,
	t_minirt_pack **out
)
{
	const size_t			malloc_size
		= sizeof(t_minirt_pack) + size(files, file_count);
	t_minirt_pack *const	result = malloc(malloc_size);

	if (!result)
		return (true);
	result->size = malloc_size;
	fill(files, file_count, result->array);
	*out = result;
	return (false);
}
