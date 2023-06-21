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

t_err	minirt_args_next_anything_long_no_v_set(
	t_minirt_args_state *mut_state,
	const char *arg
)
{
	const t_minirt_args_options_set *const	option
		= mut_state->state_value.set;
	const size_t							option_length
		= minirt_strlen(option->name);

	if (!arg[2 + option_length])
	{
		mut_state->state_type = MINIRT_ARGS_STATE_VALUE;
		return (false);
	}
	return (minirt_args_add_set(mut_state, &arg[3 + option_length]));
}
