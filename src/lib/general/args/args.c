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

#include "minirt/args.h"

#include "args_internal.h"

t_err	minirt_args(
	unsigned int argc,
	char **argv,
	t_minirt_args_options options,
	t_minirt_args_result *out
)
{
	t_minirt_args_state	state;
	unsigned int		i;

	if (minirt_args_state_init(&state))
		return (minirt_args_malloc_error(&state, out));
	i = -1;
	while (++i < argc && state.state_type != MINIRT_ARGS_STATE_ERROR)
		if (minirt_args_next(&state, &options, argv[i]))
			return (minirt_args_malloc_error(&state, out));
	return (minirt_args_finalize(&state, out));
}
