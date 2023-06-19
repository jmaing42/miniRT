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

typedef t_minirt_json_tokenizer_state	t_s;

t_err	minirt_json_tokenize_number_zero(
	char c,
	t_minirt_json_token_list *list,
	void *data,
	t_minirt_json_tokenizer_state *out_next_state
)
{
	t_minirt_json_tokenizer_state_number *const	d = data;

	if (c == '.' || c == 'e' || c == 'E')
	{
		*out_next_state = (t_s){MINIRT_JSON_TOKENIZER_STATE_NUMBER_E, data};
		if (c == '.')
			*out_next_state
				= (t_s){MINIRT_JSON_TOKENIZER_STATE_NUMBER_DOT, data};
		return (false);
	}
	if ('0' <= c && c <= '9')
	{
		free(data);
		*out_next_state = (t_s){MINIRT_JSON_TOKENIZER_STATE_ERROR, NULL};
		return (false);
	}
	if (minirt_json_tokenize_add_number_token(list, d))
		return (true);
	*out_next_state = (t_s){MINIRT_JSON_TOKENIZER_STATE_DEFAULT, NULL};
	return (minirt_json_tokenize_default(c, list, data, out_next_state));
}
