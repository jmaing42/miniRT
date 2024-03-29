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

void	minirt_json_value_dict_free(
	t_minirt_json_value_dict *value
)
{
	t_minirt_json_dict_node	*node;

	while (value->value.head)
	{
		node = value->value.head;
		value->value.head = node->next;
		free(node->key);
		minirt_json_value_internal_free(node->value);
		free(node->value);
		free(node);
	}
}
