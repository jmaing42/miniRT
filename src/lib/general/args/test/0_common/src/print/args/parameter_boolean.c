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

t_err	print_args_parameter_boolean(
	t_minirt_args_parameter_boolean *param
)
{
	return (
		printf("--%s", param->option->name) < 0
		|| (param->option->short_name
			&& printf(" (-%c)", param->option->short_name) < 0)
		|| printf(" (boolean)\n") < 0
	);
}
