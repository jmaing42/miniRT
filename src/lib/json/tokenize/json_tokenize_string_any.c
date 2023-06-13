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

static const bool								g_t = true;
static const bool								g_f = false;

static const bool								g_map[256] = {
	g_t, g_t, g_t, g_t, g_t, g_t, g_t, g_t, // 0000 ~ 0007
	g_t, g_t, g_t, g_t, g_t, g_t, g_t, g_t, // 0010 ~ 0017
	g_t, g_t, g_t, g_t, g_t, g_t, g_t, g_t, // 0020 ~ 0027
	g_t, g_t, g_t, g_t, g_t, g_t, g_t, g_t, // 0030 ~ 0037
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0040 ~ 0047
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0050 ~ 0057
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0060 ~ 0067
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0070 ~ 0077
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0100 ~ 0107
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0110 ~ 0117
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0120 ~ 0127
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0130 ~ 0137
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0140 ~ 0147
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0150 ~ 0157
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0160 ~ 0167
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_t, // 0170 ~ 0177
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0200 ~ 0207
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0210 ~ 0217
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0220 ~ 0227
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0230 ~ 0237
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0240 ~ 0247
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0250 ~ 0257
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0260 ~ 0267
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0270 ~ 0277
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0300 ~ 0307
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0310 ~ 0317
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0320 ~ 0327
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0330 ~ 0337
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0340 ~ 0347
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0350 ~ 0357
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0360 ~ 0367
	g_f, g_f, g_f, g_f, g_f, g_f, g_f, g_f, // 0370 ~ 0377
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
