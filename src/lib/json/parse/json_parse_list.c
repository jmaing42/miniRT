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

static t_err	append_item(
	t_minirt_json_token_list_node **head,
	t_minirt_json_value_list *out
)
{
	t_minirt_json_list_node *const		node
		= malloc(sizeof(t_minirt_json_list_node));
	t_minirt_json_value_internal *const	value
		= malloc(sizeof(t_minirt_json_value_internal));

	if (!node || !value || minirt_json_parse_value(head, value))
	{
		free(node);
		free(value);
		return (true);
	}
	node->next = NULL;
	node->value = value;
	if (out->value.tail)
		out->value.tail->next = node;
	else
		out->value.head = node;
	out->value.tail = node;
	return (false);
}

static t_err	fill_items(
	t_minirt_json_token_list_node **head,
	t_minirt_json_value_list *out
)
{
	if (*(*head)->value.type == MINIRT_JSON_TOKEN_TYPE_BRACKET_CLOSE)
		return (false);
	if (append_item(head, out))
		return (true);
	while (out->value.tail->value->type != MINIRT_JSON_VALUE_TYPE_ERROR
		&& *(*head)->value.type == MINIRT_JSON_TOKEN_TYPE_COMMA
		&& minirt_json_parse_next_is_value(*(*head)->next->value.type))
	{
		*head = (*head)->next;
		if (append_item(head, out))
		{
			minirt_json_value_list_free(out);
			return (true);
		}
	}
	return (false);
}

static t_err	syntax_error(t_minirt_json_value_list *out)
{
	out->type = MINIRT_JSON_VALUE_TYPE_ERROR;
	return (false);
}

t_err	minirt_json_parse_list(
	t_minirt_json_token_list_node **head,
	t_minirt_json_value_list *out
)
{
	t_minirt_json_token_list_node	*curr;

	curr = *head;
	if (!minirt_json_parse_next_is_list(*(*head)->value.type)
		|| (!minirt_json_parse_next_is_value(*(*head)->next->value.type)
			&& *(*head)->next->value.type
			!= MINIRT_JSON_TOKEN_TYPE_BRACKET_CLOSE))
		return (syntax_error(out));
	curr = curr->next;
	out->type = MINIRT_JSON_VALUE_TYPE_LIST;
	out->value.head = NULL;
	out->value.tail = NULL;
	if (fill_items(&curr, out))
		return (true);
	if (*curr->value.type != MINIRT_JSON_TOKEN_TYPE_BRACKET_CLOSE
		|| (out->value.tail
			&& out->value.tail->value->type == MINIRT_JSON_VALUE_TYPE_ERROR))
	{
		minirt_json_value_list_free(out);
		return (syntax_error(out));
	}
	*head = curr->next;
	return (false);
}
