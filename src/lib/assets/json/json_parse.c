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

#include "minirt/json.h"

#include <stdlib.h>

#include "json_internal.h"

t_err	minirt_json_parse(const char *str, t_minirt_json *out)
{
	t_minirt_json_value_internal *const	result
		= malloc(sizeof(t_minirt_json_value_internal));

	if (!result)
		return (true);
	if (minirt_json_parse_internal(str, result))
	{
		free(result);
		return (true);
	}
	*out = result;
	return (false);
}
