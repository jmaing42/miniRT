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

#include <stdbool.h>

#include "minirt/common/libc.h"
#include "json_internal.h"

bool	minirt_json_dict_has_key(t_minirt_json value, const char *key)
{
	t_minirt_json_value_internal *const	self = value;
	t_minirt_json_dict_node				*current;

	current = self->dict.value.head;
	while (current)
	{
		if (minirt_str_eq(current->key, key))
			return (true);
		current = current->next;
	}
	return (false);
}
