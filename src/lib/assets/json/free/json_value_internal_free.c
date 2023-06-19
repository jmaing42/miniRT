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

void	minirt_json_value_internal_free(
	t_minirt_json_value_internal *value
)
{
	if (value->type == MINIRT_JSON_VALUE_TYPE_STRING)
		minirt_json_value_string_free(&value->string);
	else if (value->type == MINIRT_JSON_VALUE_TYPE_LIST)
		minirt_json_value_list_free(&value->list);
	else if (value->type == MINIRT_JSON_VALUE_TYPE_DICT)
		minirt_json_value_dict_free(&value->dict);
}
