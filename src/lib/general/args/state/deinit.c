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

#include "args_internal.h"

#include <stdlib.h>

#include "minirt/common/array_builder.h"

void	minirt_args_state_deinit(t_minirt_args_state *self)
{
	size_t	i;

	if (self->params_string)
		minirt_array_builder_free(self->params_string);
	if (self->params_map)
	{
		i = (size_t)(-1);
		while (++i < self->params_map->length)
			free(((t_minirt_args_map_entry *)self->params_map->array)[i].key);
		minirt_array_builder_free(self->params_map);
	}
	if (self->params_set)
		minirt_array_builder_free(self->params_set);
	if (self->params_boolean)
		minirt_array_builder_free(self->params_boolean);
	if (self->args)
		minirt_array_builder_free(self->args);
	minirt_args_free_error(&self->error);
}
