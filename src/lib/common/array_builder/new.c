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

#include "minirt/common/array_builder.h"

#include <stdlib.h>

t_minirt_array_builder	*minirt_array_builder_new(size_t item_size)
{
	t_minirt_array_builder *const	result
		= malloc(sizeof(t_minirt_array_builder));

	if (!result)
		return (NULL);
	result->item_size = item_size;
	result->capacity = 0;
	result->length = 0;
	result->array = NULL;
	return (result);
}
