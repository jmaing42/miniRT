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

t_err	minirt_json_tokenize_add_simple_token(
	t_minirt_json_token_list *list,
	t_minirt_json_token_type type
)
{
	t_minirt_json_token_type *const			token
		= malloc(sizeof(t_minirt_json_token_type));
	t_minirt_json_token_list_node *const	node
		= malloc(sizeof(t_minirt_json_token_list_node));

	if (!token || !node)
	{
		free(token);
		free(node);
		return (true);
	}
	*token = type;
	node->next = NULL;
	node->free_value = *((void (**)(t_minirt_json_token))(&free));
	node->value.type = token;
	if (list->head)
		list->tail->next = node;
	else
		list->head = node;
	list->tail = node;
	return (false);
}
