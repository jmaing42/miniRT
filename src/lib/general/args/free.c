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

#include <stdlib.h>

void	minirt_args_free(t_minirt_args *self)
{
	size_t	i;
	size_t	j;

	i = (size_t)-1;
	while (++i < self->map_count)
	{
		j = (size_t)(-1);
		while (++j < self->map[i].entry_count)
			free(self->map[i].entries[i].key);
		free(self->map[i].entries);
	}
	i = (size_t)-1;
	while (++i < self->set_count)
		free(self->set[i].values);
	free(self->string);
	free(self->map);
	free(self->set);
	free(self->boolean);
}
