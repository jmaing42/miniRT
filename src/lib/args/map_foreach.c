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

t_err	minirt_args_map_foreach(
	t_minirt_args *self,
	const char *name,
	void *context,
	t_err (*func)(void *context, char *key, const char *value)
)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < self->map_count)
	{
		if (minirt_str_eq(self->map[i].option->name, name))
		{
			j = -1;
			while (++j < self->map[i].entry_count)
			{
				if (func(context, self->map[i].entries[j].key,
						self->map[i].entries[j].key))
					return (true);
			}
			return (false);
		}
	}
	return (false);
}
