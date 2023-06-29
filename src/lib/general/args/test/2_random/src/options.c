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

#include "minirt/args.h"

#include <stdbool.h>

const t_minirt_args_options_string	g_string_options[] = {
{
	"string",
	's',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_ERROR,
},
{
	"string-2",
	'S',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_IGNORE_IF_SAME,
},
{
	"test-use-first",
	'f',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_USE_FIRST,
},
{
	"test-use-last",
	'l',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_USE_LAST,
},
{
	"no-short-name",
	'\0',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_ERROR,
},
};

const t_minirt_args_options_map		g_map_options[] = {
{
	"map",
	'm',
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_USE_FIRST,
	true,
},
{
	"map-test",
	'M',
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_IGNORE_IF_SAME,
	true,
},
{
	"error",
	'\0',
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_ERROR,
	true,
},
{
	"env",
	'e',
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_USE_LAST,
	false,
},
{
	"define",
	'D',
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_USE_LAST,
	true,
},
{
	"publish",
	'p',
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_IGNORE_IF_SAME,
	false,
},
};

const t_minirt_args_options_set		g_set_options[] = {
{
	"include-directory",
	'I',
	MINIRT_ARGS_OPTIONS_DUPLICATE_VALUE_IGNORE,
},
{
	"library-directory",
	'L',
	MINIRT_ARGS_OPTIONS_DUPLICATE_VALUE_IGNORE,
},
{
	"set-test",
	'T',
	MINIRT_ARGS_OPTIONS_DUPLICATE_VALUE_ERROR,
},
};

const t_minirt_args_options_boolean	g_boolean_options[] = {
{
	"detach",
	'd',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_ERROR,
},
{
	"interactive",
	'i',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_ERROR,
},
{
	"tty",
	't',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_ERROR,
},
{
	"no-newline",
	'n',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_IGNORE,
},
{
	"rm",
	'\n',
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_IGNORE,
},
};

const t_minirt_args_options			g_options = {
	g_string_options,
	sizeof(g_string_options) / sizeof(g_string_options[0]),
	g_map_options,
	sizeof(g_map_options) / sizeof(g_map_options[0]),
	g_set_options,
	sizeof(g_set_options) / sizeof(g_set_options[0]),
	g_boolean_options,
	sizeof(g_boolean_options) / sizeof(g_boolean_options[0]),
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_IGNORE,
	MINIRT_ARGS_OPTIONS_MALFORMED_PARAMETER_AS_ARGS,
	false,
};
