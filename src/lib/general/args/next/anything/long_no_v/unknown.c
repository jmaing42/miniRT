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

t_err	minirt_args_next_anything_long_no_v_unknown(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	if (options->unknown_parameter
		== MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_AS_ARGS)
		return (minirt_args_add_arg(mut_state, arg));
	if (options->unknown_parameter
		== MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_IGNORE)
		return (false);
	mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
	mut_state->error.type = MINIRT_ARGS_ERROR_UNKNOWN_PARAMETER;
	mut_state->error.value.unknown_parameter.arg = arg;
	return (false);
}
