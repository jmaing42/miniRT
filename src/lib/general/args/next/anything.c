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

t_err	minirt_args_next_anything(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	t_minirt_args_type	type;

	if (minirt_str_eq(arg, "=="))
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ARGS;
		return (false);
	}
	type = minirt_args_identify(arg);
	if (type == MINIRT_ARGS_TYPE_ARG)
		return (minirt_args_next_anything_arg(mut_state, options, arg));
	else if (type == MINIRT_ARGS_TYPE_MALFORMED_PARAMETER)
		return (minirt_args_next_anything_malformed(mut_state, options, arg));
	else if (type == MINIRT_ARGS_TYPE_LONG_WITHOUT_VALUE)
		return (minirt_args_next_anything_long_no_v(mut_state, options, arg));
	else if (type
		== MINIRT_ARGS_TYPE_LONG_STRING_WITH_VALUE_OR_LONG_BOOLEAN_WITH_VALUE)
		return (minirt_args_next_anything_long(mut_state, options, arg));
	else
		return (minirt_args_next_anything_short(mut_state, options, arg));
}
