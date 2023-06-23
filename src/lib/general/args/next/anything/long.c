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

#include "minirt/common/libc.h"

static bool	is_string(
	t_minirt_args_options *options,
	const char *arg,
	const t_minirt_args_options_string **out_option,
	size_t *out_option_length
)
{
	size_t	i;
	size_t	option_length;

	i = (size_t)-1;
	while (++i < options->string_parameter_count)
	{
		if (minirt_starts_with(
				&arg[2], options->string_parameters[i].name, &option_length)
			&& (!arg[2 + option_length] || arg[2 + option_length] == '='))
		{
			*out_option = &options->string_parameters[i];
			*out_option_length = option_length;
			return (true);
		}
	}
	return (false);
}

static bool	is_set(
	t_minirt_args_options *options,
	const char *arg,
	const t_minirt_args_options_set **out_option,
	size_t *out_option_length
)
{
	size_t	i;
	size_t	option_length;

	i = (size_t)-1;
	while (++i < options->set_parameter_count)
	{
		if (minirt_starts_with(
				&arg[2], options->set_parameters[i].name, &option_length)
			&& (!arg[2 + option_length] || arg[2 + option_length] == '='))
		{
			*out_option = &options->set_parameters[i];
			*out_option_length = option_length;
			return (true);
		}
	}
	return (false);
}

t_err	minirt_args_next_anything_long(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	size_t		option_length;
	const bool	str = is_string(
			options, arg, &mut_state->state_value.string, &option_length);
	const bool	set = is_set(
			options, arg, &mut_state->state_value.set, &option_length);

	if (str)
		return (minirt_args_next_anything_long_string(
				mut_state, option_length, arg));
	if (set)
		return (minirt_args_next_anything_long_set(
				mut_state, option_length, arg));
	return (minirt_args_next_anything_unknown(mut_state, options, arg));
}
