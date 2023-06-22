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

static const t_minirt_json_tokenizer_state_function	g_state_functions[] = {
	minirt_json_tokenize_default,
	minirt_json_tokenize_keyword_t,
	minirt_json_tokenize_keyword_tr,
	minirt_json_tokenize_keyword_tru,
	minirt_json_tokenize_keyword_f,
	minirt_json_tokenize_keyword_fa,
	minirt_json_tokenize_keyword_fal,
	minirt_json_tokenize_keyword_fals,
	minirt_json_tokenize_keyword_n,
	minirt_json_tokenize_keyword_nu,
	minirt_json_tokenize_keyword_nul,
	minirt_json_tokenize_string_any,
	minirt_json_tokenize_string_backslash,
	minirt_json_tokenize_string_x0,
	minirt_json_tokenize_string_x1,
	minirt_json_tokenize_number_sign,
	minirt_json_tokenize_number_zero,
	minirt_json_tokenize_number_integer,
	minirt_json_tokenize_number_dot,
	minirt_json_tokenize_number_fraction,
	minirt_json_tokenize_number_e,
	minirt_json_tokenize_number_e_sign,
	minirt_json_tokenize_number_e_digit,
};

typedef t_minirt_json_tokenizer_state				t_s;

t_err	minirt_json_tokenize(
	const char *str,
	t_minirt_json_token_list *out
)
{
	t_s		current_state;
	size_t	i;

	current_state.state = MINIRT_JSON_TOKENIZER_STATE_DEFAULT;
	current_state.data = NULL;
	*out = (t_minirt_json_token_list){NULL, NULL};
	i = (size_t)-1;
	while (current_state.state != MINIRT_JSON_TOKENIZER_STATE_ERROR
		&& (i++ == (size_t)-1 || str[i - 1]))
	{
		if (g_state_functions[current_state.state](
			str[i], out, current_state.data, &current_state))
		{
			minirt_json_tokenize_free(*out);
			return (true);
		}
	}
	if (current_state.state == MINIRT_JSON_TOKENIZER_STATE_ERROR)
	{
		minirt_json_tokenize_free(*out);
		*out = (t_minirt_json_token_list){NULL, NULL};
	}
	return (false);
}
