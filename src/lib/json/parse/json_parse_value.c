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

#include "minirt/common/libc.h"

static t_err	special(
	t_minirt_json_token_list_node **head,
	t_minirt_json_value_internal *out
)
{
	t_err	result;

	result = false;
	if (*(*head)->value.type == MINIRT_JSON_TOKEN_TYPE_NULL)
		out->type = MINIRT_JSON_VALUE_TYPE_NULL;
	else if (*(*head)->value.type == MINIRT_JSON_TOKEN_TYPE_TRUE
		|| *(*head)->value.type == MINIRT_JSON_TOKEN_TYPE_FALSE)
	{
		out->type = MINIRT_JSON_VALUE_TYPE_BOOLEAN;
		out->boolean.value
			= *(*head)->value.type == MINIRT_JSON_TOKEN_TYPE_TRUE;
	}
	else if (*(*head)->value.type == MINIRT_JSON_TOKEN_TYPE_NUMBER)
	{
		out->type = MINIRT_JSON_VALUE_TYPE_NUMBER;
		out->number.value = (*head)->value.number->value;
	}
	else if (*(*head)->value.type == MINIRT_JSON_TOKEN_TYPE_STRING)
	{
		out->type = MINIRT_JSON_VALUE_TYPE_STRING;
		result
			= minirt_strdup((*head)->value.string->value, &out->string.value);
	}
	else
		return (true);
	*head = (*head)->next;
	return (result);
}

t_err	minirt_json_parse_value(
	t_minirt_json_token_list_node **head,
	t_minirt_json_value_internal *out
)
{
	if (!minirt_json_parse_next_is_value(*(*head)->value.type))
	{
		out->type = MINIRT_JSON_VALUE_TYPE_ERROR;
		return (false);
	}
	if (minirt_json_parse_next_is_list(*(*head)->value.type))
		return (minirt_json_parse_list(head, &out->list));
	if (minirt_json_parse_next_is_dict(*(*head)->value.type))
		return (minirt_json_parse_dict(head, &out->dict));
	return (special(head, out));
}
