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

#include "json_internal.h"

#include <stdlib.h>

void	minirt_json_stringbuilder_free(t_minirt_json_stringbuilder *self)
{
	t_minirt_json_stringbuilder_node	*current;
	t_minirt_json_stringbuilder_node	*next;

	current = self->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(self);
}
