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
#include "minirt/common/array_builder.h"

t_err	minirt_args_next_args(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	char	*value;

	(void)options;
	return (
		minirt_strdup(arg, &value)
		|| minirt_array_builder_append(mut_state->args, 1, &value)
	);
}
