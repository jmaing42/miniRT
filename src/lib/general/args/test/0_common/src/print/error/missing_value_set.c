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

t_err	print_error_missing_value_set(
	t_minirt_args_error_missing_value_set error
)
{
	return (
		printf("Missing value for set parameter --%s", error.option->name) < 0
		|| (error.option->short_name
			&& printf(" (-%c)", error.option->short_name) < 0)
		|| printf("\n") < 0
	);
}
