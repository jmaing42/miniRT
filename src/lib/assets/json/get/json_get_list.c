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

#include "minirt/json.h"

#include "json_internal.h"

t_minirt_json	minirt_json_get_list(t_minirt_json value, size_t index)
{
	t_minirt_json_value_internal *const	self = value;
	t_minirt_json_list_node				*current;

	current = self->list.value.head;
	while (index--)
		current = current->next;
	return (current->value);
}
