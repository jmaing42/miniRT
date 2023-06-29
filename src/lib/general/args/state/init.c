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

#include "minirt/args.h"
#include "minirt/common/array_builder.h"

static t_err	init_others(t_minirt_args_state *self)
{
	self->args = minirt_array_builder_new(sizeof(char *));
	if (!self->args)
		return (true);
	self->params_string = minirt_array_builder_new(
			sizeof(t_minirt_args_parameter_string));
	if (!self->params_string)
		return (true);
	self->params_map = minirt_array_builder_new(
			sizeof(t_minirt_args_parameter_map_builder));
	if (!self->params_map)
		return (true);
	self->params_set = minirt_array_builder_new(
			sizeof(t_minirt_args_parameter_set_builder));
	if (!self->params_set)
		return (true);
	self->params_boolean
		= minirt_array_builder_new(
			sizeof(t_minirt_args_parameter_boolean));
	if (!self->params_boolean)
		return (true);
	return (false);
}

t_err	minirt_args_state_init(t_minirt_args_state *self)
{
	self->state_type = MINIRT_ARGS_STATE_ANYTHING;
	self->args = NULL;
	self->params_string = NULL;
	self->params_map = NULL;
	self->params_set = NULL;
	self->params_boolean = NULL;
	self->error.type = MINIRT_ARGS_ERROR_MALLOC_FAILURE;
	return (init_others(self));
}
