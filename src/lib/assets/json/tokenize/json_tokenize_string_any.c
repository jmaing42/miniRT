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

typedef t_minirt_json_tokenizer_state			t_s;
typedef t_minirt_json_tokenizer_state_string	t_x;

static const unsigned char						g_map[256] = {
	1, 1, 1, 1, 1, 1, 1, 1, // 0000 ~ 0007
	1, 1, 1, 1, 1, 1, 1, 1, // 0010 ~ 0017
	1, 1, 1, 1, 1, 1, 1, 1, // 0020 ~ 0027
	1, 1, 1, 1, 1, 1, 1, 1, // 0030 ~ 0037
	0, 0, 0, 0, 0, 0, 0, 0, // 0040 ~ 0047
	0, 0, 0, 0, 0, 0, 0, 0, // 0050 ~ 0057
	0, 0, 0, 0, 0, 0, 0, 0, // 0060 ~ 0067
	0, 0, 0, 0, 0, 0, 0, 0, // 0070 ~ 0077
	0, 0, 0, 0, 0, 0, 0, 0, // 0100 ~ 0107
	0, 0, 0, 0, 0, 0, 0, 0, // 0110 ~ 0117
	0, 0, 0, 0, 0, 0, 0, 0, // 0120 ~ 0127
	0, 0, 0, 0, 0, 0, 0, 0, // 0130 ~ 0137
	0, 0, 0, 0, 0, 0, 0, 0, // 0140 ~ 0147
	0, 0, 0, 0, 0, 0, 0, 0, // 0150 ~ 0157
	0, 0, 0, 0, 0, 0, 0, 0, // 0160 ~ 0167
	0, 0, 0, 0, 0, 0, 0, 1, // 0170 ~ 0177
	0, 0, 0, 0, 0, 0, 0, 0, // 0200 ~ 0207
	0, 0, 0, 0, 0, 0, 0, 0, // 0210 ~ 0217
	0, 0, 0, 0, 0, 0, 0, 0, // 0220 ~ 0227
	0, 0, 0, 0, 0, 0, 0, 0, // 0230 ~ 0237
	0, 0, 0, 0, 0, 0, 0, 0, // 0240 ~ 0247
	0, 0, 0, 0, 0, 0, 0, 0, // 0250 ~ 0257
	0, 0, 0, 0, 0, 0, 0, 0, // 0260 ~ 0267
	0, 0, 0, 0, 0, 0, 0, 0, // 0270 ~ 0277
	0, 0, 0, 0, 0, 0, 0, 0, // 0300 ~ 0307
	0, 0, 0, 0, 0, 0, 0, 0, // 0310 ~ 0317
	0, 0, 0, 0, 0, 0, 0, 0, // 0320 ~ 0327
	0, 0, 0, 0, 0, 0, 0, 0, // 0330 ~ 0337
	0, 0, 0, 0, 0, 0, 0, 0, // 0340 ~ 0347
	0, 0, 0, 0, 0, 0, 0, 0, // 0350 ~ 0357
	0, 0, 0, 0, 0, 0, 0, 0, // 0360 ~ 0367
	0, 0, 0, 0, 0, 0, 0, 0, // 0370 ~ 0377
};

static bool	is_control(char c)
{
	return (g_map[(unsigned char)c]);
}

t_err	minirt_json_tokenize_string_any(
	char c,
	t_minirt_json_token_list *list,
	void *data,
	t_minirt_json_tokenizer_state *out_next_state
)
{
	if (c == '"')
	{
		*out_next_state = (t_s){MINIRT_JSON_TOKENIZER_STATE_DEFAULT, NULL};
		return (minirt_json_tokenize_add_string_token(list, (t_x *)data));
	}
	else if (c == '\\')
	{
		*out_next_state
			= (t_s){MINIRT_JSON_TOKENIZER_STATE_STRING_BACKSLASH, data};
		return (false);
	}
	else if (is_control(c))
	{
		*out_next_state = (t_s){MINIRT_JSON_TOKENIZER_STATE_ERROR, NULL};
		return (false);
	}
	*out_next_state = (t_s){MINIRT_JSON_TOKENIZER_STATE_STRING_ANY, data};
	if (minirt_json_stringbuilder_append_char(((t_x *)data)->stringbuilder, c))
	{
		minirt_json_stringbuilder_free(((t_x *)data)->stringbuilder);
		free(data);
		return (true);
	}
	return (false);
}
