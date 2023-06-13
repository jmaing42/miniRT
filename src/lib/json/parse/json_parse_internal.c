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

t_err	minirt_json_parse_internal(
	const char *str,
	t_minirt_json_value_internal *out
)
{
	t_minirt_json_token_list		token_list;
	t_minirt_json_token_list_node	*head;

	if (minirt_json_tokenize(str, &token_list))
		return (true);
	if (!token_list.head)
	{
		out->type = MINIRT_JSON_VALUE_TYPE_ERROR;
		return (false);
	}
	head = token_list.head;
	if (minirt_json_parse_value(&head, out))
	{
		minirt_json_tokenize_free(token_list);
		return (true);
	}
	if (*head->value.type != MINIRT_JSON_TOKEN_TYPE_EOF)
	{
		minirt_json_tokenize_free(token_list);
		minirt_json_value_internal_free(out);
		out->type = MINIRT_JSON_VALUE_TYPE_ERROR;
		return (false);
	}
	minirt_json_tokenize_free(token_list);
	return (false);
}
