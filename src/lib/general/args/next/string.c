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

t_err	minirt_args_next_string(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	(void)options;
	mut_state->state_type = MINIRT_ARGS_STATE_ANYTHING;
	return (minirt_args_add_string(mut_state, arg));
}
