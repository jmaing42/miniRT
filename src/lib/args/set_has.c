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

#include "minirt/common/libc.h"

bool	minirt_args_set_has(
	t_minirt_args *self,
	const char *name,
	const char *value
)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < self->set_count)
	{
		if (minirt_str_eq(self->set[i].option->name, name))
		{
			j = -1;
			while (++j < self->set[i].value_count)
				if (minirt_str_eq(self->set[i].values[j], value))
					return (true);
			return (false);
		}
	}
	return (false);
}
