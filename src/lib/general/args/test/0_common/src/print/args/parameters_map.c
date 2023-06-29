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

t_err	print_args_parameters_map(
	t_minirt_args_parameter_map *param,
	size_t count
)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < count)
		if (print_args_parameter_map(&param[i]))
			return (true);
	return (false);
}
