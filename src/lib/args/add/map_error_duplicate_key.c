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

#include <stdlib.h>

t_err	minirt_args_add_map_error_duplicate_key(
	t_minirt_args_state *mut_state,
	char *key,
	char *value
)
{
	free(value);
	mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
	mut_state->error.type = MINIRT_ARGS_ERROR_DUPLICATE_KEY;
	mut_state->error.value.duplicate_key.option = mut_state->state_value.map;
	mut_state->error.value.duplicate_key.key = key;
	return (false);
}
