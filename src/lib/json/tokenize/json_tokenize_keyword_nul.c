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

t_err	minirt_json_tokenize_keyword_nul(
	char c,
	t_minirt_json_token_list *list,
	void *data,
	t_minirt_json_tokenizer_state *out_next_state
)
{
	(void)list;
	(void)data;
	if (c == 'l')
	{
		if (minirt_json_tokenize_add_simple_token(
				list, MINIRT_JSON_TOKEN_TYPE_NULL))
			return (true);
		out_next_state->state = MINIRT_JSON_TOKENIZER_STATE_DEFAULT;
	}
	else
		out_next_state->state = MINIRT_JSON_TOKENIZER_STATE_ERROR;
	return (false);
}
