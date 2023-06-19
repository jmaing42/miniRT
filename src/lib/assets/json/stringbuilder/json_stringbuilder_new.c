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

#define MINIMUM_BUFFER_SIZE 16

t_minirt_json_stringbuilder	*minirt_json_stringbuilder_new(size_t buffer_size)
{
	t_minirt_json_stringbuilder *const	result
		= malloc(sizeof(t_minirt_json_stringbuilder));

	if (!result)
		return (NULL);
	result->length = 0;
	result->head = NULL;
	result->tail = NULL;
	result->buffer_size = buffer_size;
	if (MINIMUM_BUFFER_SIZE > buffer_size)
		result->buffer_size = MINIMUM_BUFFER_SIZE;
	return (result);
}
