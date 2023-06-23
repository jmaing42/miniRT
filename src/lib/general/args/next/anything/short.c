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

static bool	is_string(
	t_minirt_args_options *options,
	const char *arg,
	const t_minirt_args_options_string **out
)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < options->string_parameter_count)
	{
		if (arg[1] == options->string_parameters[i].short_name)
		{
			*out = &options->string_parameters[i];
			return (true);
		}
	}
	return (false);
}

static bool	is_map(
	t_minirt_args_options *options,
	const char *arg,
	const t_minirt_args_options_map **out
)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < options->map_parameter_count)
	{
		if (arg[1] == options->map_parameters[i].short_name)
		{
			*out = &options->map_parameters[i];
			return (true);
		}
	}
	return (false);
}

static bool	is_set(
	t_minirt_args_options *options,
	const char *arg,
	const t_minirt_args_options_set **out
)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < options->set_parameter_count)
	{
		if (arg[1] == options->set_parameters[i].short_name)
		{
			*out = &options->set_parameters[i];
			return (true);
		}
	}
	return (false);
}

static bool	is_boolean(
	t_minirt_args_options *options,
	const char *arg,
	const t_minirt_args_options_boolean **out
)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < options->boolean_parameter_count)
	{
		if (arg[1] == options->boolean_parameters[i].short_name)
		{
			*out = &options->boolean_parameters[i];
			return (true);
		}
	}
	return (false);
}

t_err	minirt_args_next_anything_short(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	const bool	str = is_string(options, arg, &mut_state->state_value.string);
	const bool	map = is_map(options, arg, &mut_state->state_value.map);
	const bool	set = is_set(options, arg, &mut_state->state_value.set);
	const bool	b = is_boolean(options, arg, &mut_state->state_value.boolean);

	if (str && !arg[2])
		return (minirt_args_next_anything_no_v_string(mut_state));
	if (map && !arg[2])
		return (minirt_args_next_anything_no_v_map(mut_state));
	if (set && !arg[2])
		return (minirt_args_next_anything_no_v_set(mut_state));
	if (b && !arg[2])
		return (minirt_args_next_anything_no_v_boolean(mut_state));
	if (str)
		return (minirt_args_next_anything_short_string(mut_state, arg));
	if (map)
		return (minirt_args_next_anything_short_map(mut_state, arg));
	if (set)
		return (minirt_args_next_anything_short_set(mut_state, arg));
	if (b)
		return (
			minirt_args_next_anything_short_boolean(mut_state, options, arg));
	return (minirt_args_next_anything_unknown(mut_state, options, arg));
}
