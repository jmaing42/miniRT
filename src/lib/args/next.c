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

t_err	minirt_args_next(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	char *arg
)
{
	if (mut_state->state_type == MINIRT_ARGS_STATE_ANYTHING)
		return (minirt_args_next_anything(mut_state, options, arg));
	else if (mut_state->state_type == MINIRT_ARGS_STATE_STRING)
		return (minirt_args_next_string(mut_state, options, arg));
	else if (mut_state->state_type == MINIRT_ARGS_STATE_ENTRY)
		return (minirt_args_next_entry(mut_state, options, arg));
	else if (mut_state->state_type == MINIRT_ARGS_STATE_VALUE)
		return (minirt_args_next_value(mut_state, options, arg));
	else
		return (minirt_args_next_args(mut_state, options, arg));
}
