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

bool	minirt_args_get_boolean(
	t_minirt_args *self,
	const char *name,
	bool *out
)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < self->string_count)
	{
		if (minirt_str_eq(self->string[i].option->name, name))
		{
			*out = self->string[i].value;
			return (true);
		}
	}
	return (false);
}
