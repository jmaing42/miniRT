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

static t_err	print_entry(
	t_minirt_args_map_entry *entry
)
{
	return (
		printf("\t%s", entry->key) < 0
		|| (entry->value && printf("=%s", entry->value) < 0)
		|| printf("\n") < 0
	);
}

t_err	print_args_parameter_map(
	t_minirt_args_parameter_map *param
)
{
	size_t	i;

	if (
		printf("--%s", param->option->name) < 0
		|| (param->option->short_name
			&& printf(" (-%c)", param->option->short_name) < 0)
		|| printf(": (map)\n") < 0)
		return (true);
	i = (size_t)-1;
	while (++i < param->entry_count)
		if (print_entry(&param->entries[i]))
			return (true);
	return (false);
}
