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

#include "minirt/common/libc.h"

void	*minirt_array_builder_build(t_minirt_array_builder *self)
{
	void *const	result = malloc(self->item_size * self->length);

	if (!result)
		return (NULL);
	minirt_memcpy(result, self->array, self->item_size * self->length);
	return (result);
}
