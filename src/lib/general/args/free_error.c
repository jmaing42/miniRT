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

#include <stdlib.h>

void	minirt_args_free_error(t_minirt_args_error *error)
{
	if (error->type == MINIRT_ARGS_ERROR_MISSING_VALUE_MAP)
		free(error->value.missing_value_map.key);
	if (error->type == MINIRT_ARGS_ERROR_DUPLICATE_KEY)
		free(error->value.missing_value_map.key);
}
