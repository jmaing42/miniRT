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

const char	*minirt_args_get_string(
	t_minirt_args *self,
	const char *name
)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < self->string_count)
		if (minirt_str_eq(self->string[i].option->name, name))
			return (self->string[i].value);
	return (NULL);
}
