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

t_err	minirt_args_set_foreach(
	t_minirt_args *self,
	const char *name,
	void *context,
	t_err (*func)(void *context, const char *value)
)
{
	size_t	i;
	size_t	j;

	i = (size_t)-1;
	while (++i < self->set_count)
	{
		if (minirt_str_eq(self->set[i].option->name, name))
		{
			j = (size_t)(-1);
			while (++j < self->set[i].value_count)
			{
				if (func(context, self->set[i].values[j]))
					return (true);
			}
			return (false);
		}
	}
	return (false);
}
