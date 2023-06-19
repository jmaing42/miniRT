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

t_err	minirt_args_malloc_error(
	t_minirt_args_state *state,
	t_minirt_args_result *out
)
{
	minirt_args_state_deinit(state);
	out->type = MINIRT_ARGS_RESULT_ERROR;
	out->value.error.type = MINIRT_ARGS_ERROR_MALLOC_FAILURE;
	return (true);
}
