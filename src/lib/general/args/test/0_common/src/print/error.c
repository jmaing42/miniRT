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

#include "../test.h"

#include <stdio.h>

static t_err	print_error_type(t_minirt_args_error_type type)
{
	if (type == MINIRT_ARGS_ERROR_MALLOC_FAILURE)
		return (puts("[ERROR] MALLOC_FAILURE") == EOF);
	if (type == MINIRT_ARGS_ERROR_UNKNOWN_PARAMETER)
		return (puts("[ERROR] UNKNOWN_PARAMETER") == EOF);
	if (type == MINIRT_ARGS_ERROR_MALFORMED_PARAMETER)
		return (puts("[ERROR] MALFORMED_PARAMETER") == EOF);
	if (type == MINIRT_ARGS_ERROR_MISSING_VALUE_STRING)
		return (puts("[ERROR] MISSING_VALUE") == EOF);
	if (type == MINIRT_ARGS_ERROR_MISSING_ENTRY)
		return (puts("[ERROR] MISSING_ENTRY") == EOF);
	if (type == MINIRT_ARGS_ERROR_MISSING_VALUE_MAP)
		return (puts("[ERROR] MISSING_VALUE") == EOF);
	if (type == MINIRT_ARGS_ERROR_MISSING_VALUE_SET)
		return (puts("[ERROR] MISSING_VALUE") == EOF);
	if (type == MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_STRING)
		return (puts("[ERROR] DUPLICATE_PARAMETER") == EOF);
	if (type == MINIRT_ARGS_ERROR_DUPLICATE_KEY)
		return (puts("[ERROR] DUPLICATE_KEY") == EOF);
	if (type == MINIRT_ARGS_ERROR_DUPLICATE_VALUE)
		return (puts("[ERROR] DUPLICATE_VALUE") == EOF);
	if (type == MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_BOOLEAN)
		return (puts("[ERROR] DUPLICATE_PARAMETER") == EOF);
	return (true);
}

static t_err	print_error_value(t_minirt_args_error e)
{
	if (e.type == MINIRT_ARGS_ERROR_UNKNOWN_PARAMETER)
		return (print_error_unknown_parameter(e.value.unknown_parameter));
	if (e.type == MINIRT_ARGS_ERROR_MALFORMED_PARAMETER)
		return (print_error_malformed_parameter(e.value.malformed_parameter));
	if (e.type == MINIRT_ARGS_ERROR_MISSING_VALUE_STRING)
		return (print_error_missing_value_string(e.value.missing_value_string));
	if (e.type == MINIRT_ARGS_ERROR_MISSING_ENTRY)
		return (print_error_missing_entry(e.value.missing_entry));
	if (e.type == MINIRT_ARGS_ERROR_MISSING_VALUE_MAP)
		return (print_error_missing_value_map(e.value.missing_value_map));
	if (e.type == MINIRT_ARGS_ERROR_MISSING_VALUE_SET)
		return (print_error_missing_value_set(e.value.missing_value_set));
	if (e.type == MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_STRING)
		return (print_error_duplicate_parameter_string(
				e.value.duplicate_parameter_string));
	if (e.type == MINIRT_ARGS_ERROR_DUPLICATE_KEY)
		return (print_error_duplicate_key(e.value.duplicate_key));
	if (e.type == MINIRT_ARGS_ERROR_DUPLICATE_VALUE)
		return (print_error_duplicate_value(e.value.duplicate_value));
	if (e.type == MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_BOOLEAN)
		return (print_error_duplicate_parameter_boolean(
				e.value.duplicate_parameter_boolean));
	return (true);
}

t_err	print_error(t_minirt_args_error error)
{
	return (
		print_error_type(error.type)
		|| print_error_value(error)
	);
}
