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

#include "../../test.h"

#include <stdio.h>

t_err	print_error_missing_value_map(
	t_minirt_args_error_missing_value_map error
)
{
	return (
		printf("Missing value for map parameter --%s", error.option->name) < 0
		|| (error.option->short_name
			&& printf(" (-%c)", error.option->short_name) < 0)
		|| printf(" with key %s\n", error.key) < 0
	);
}
