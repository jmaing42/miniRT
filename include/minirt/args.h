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

#ifndef ARGS_H
# define ARGS_H

# include <stddef.h>
# include <stdbool.h>

# include "minirt/base_types.h"

typedef enum e_minirt_args_options_duplicate_parameter_string
{
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_ERROR,
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_IGNORE_IF_SAME,
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_USE_FIRST,
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_USE_LAST,
}	t_minirt_args_options_duplicate_parameter_string;

typedef struct s_minirt_args_options_string
{
	const char											*name;
	char												short_name;
	t_minirt_args_options_duplicate_parameter_string	on_duplicate;
}	t_minirt_args_options_string;

typedef enum e_minirt_args_options_duplicate_key
{
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_ERROR,
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_IGNORE_IF_SAME,
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_USE_FIRST,
	MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_USE_LAST,
}	t_minirt_args_options_duplicate_key;

typedef struct s_minirt_args_options_map
{
	const char							*name;
	char								short_name;
	t_minirt_args_options_duplicate_key	on_duplicate;
	bool								allow_null;
}	t_minirt_args_options_map;

typedef enum e_minirt_args_options_duplicate_value
{
	MINIRT_ARGS_OPTIONS_DUPLICATE_VALUE_ERROR,
	MINIRT_ARGS_OPTIONS_DUPLICATE_VALUE_IGNORE,
}	t_minirt_args_options_duplicate_value;

typedef struct s_minirt_args_options_set
{
	const char								*name;
	char									short_name;
	t_minirt_args_options_duplicate_value	on_duplicate;
}	t_minirt_args_options_set;

typedef enum e_minirt_args_options_duplicate_parameter_boolean
{
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_ERROR,
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_IGNORE,
}	t_minirt_args_options_duplicate_parameter_boolean;

typedef struct s_minirt_args_options_boolean
{
	const char											*name;
	char												short_name;
	t_minirt_args_options_duplicate_parameter_boolean	on_duplicate;
	bool												accept_number;
	bool												accept_keyword;
}	t_minirt_args_options_boolean;

typedef enum e_minirt_args_options_unknown_parameter
{
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_ERROR,
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_IGNORE,
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_AS_ARGS,
}	t_minirt_args_options_unknown_parameter;

typedef enum e_minirt_args_options_malformed_parameter
{
	MINIRT_ARGS_OPTIONS_MALFORMED_PARAMETER_ERROR,
	MINIRT_ARGS_OPTIONS_MALFORMED_PARAMETER_IGNORE,
	MINIRT_ARGS_OPTIONS_MALFORMED_PARAMETER_AS_ARGS,
}	t_minirt_args_options_malformed_parameter;

typedef struct s_minirt_args_options
{
	const t_minirt_args_options_string			*string_parameters;
	size_t										string_parameter_count;
	const t_minirt_args_options_map				*map_parameters;
	size_t										map_parameter_count;
	const t_minirt_args_options_set				*set_parameters;
	size_t										set_parameter_count;
	const t_minirt_args_options_boolean			*boolean_parameters;
	size_t										boolean_parameter_count;
	t_minirt_args_options_unknown_parameter		unknown_parameter;
	t_minirt_args_options_malformed_parameter	malformed_parameter;
	bool										has_subcommand;
}	t_minirt_args_options;

typedef struct s_minirt_args_parameter_string {
	const t_minirt_args_options_string	*option;
	const char							*value;
}	t_minirt_args_parameter_string;

typedef struct s_minirt_args_map_entry
{
	char		*key;
	const char	*value;
}	t_minirt_args_map_entry;

typedef struct s_minirt_args_parameter_map {
	const t_minirt_args_options_map	*option;
	t_minirt_args_map_entry			*entries;
	size_t							entry_count;
}	t_minirt_args_parameter_map;

typedef struct s_minirt_args_parameter_set {
	const t_minirt_args_options_set	*option;
	const char						**values;
	size_t							value_count;
}	t_minirt_args_parameter_set;

typedef struct s_minirt_args_parameter_boolean {
	const t_minirt_args_options_boolean	*option;
	bool								value;
}	t_minirt_args_parameter_boolean;

typedef struct s_minirt_args
{
	char							**args;
	size_t							arg_count;
	t_minirt_args_parameter_string	*string;
	size_t							string_count;
	t_minirt_args_parameter_map		*map;
	size_t							map_count;
	t_minirt_args_parameter_set		*set;
	size_t							set_count;
	t_minirt_args_parameter_boolean	*boolean;
	size_t							boolean_count;
}	t_minirt_args;

typedef enum e_minirt_args_error_type
{
	MINIRT_ARGS_ERROR_MALLOC_FAILURE,
	MINIRT_ARGS_ERROR_UNKNOWN_PARAMETER,
	MINIRT_ARGS_ERROR_MALFORMED_PARAMETER,
	MINIRT_ARGS_ERROR_MISSING_ENTRY,
	MINIRT_ARGS_ERROR_MISSING_VALUE_MAP,
	MINIRT_ARGS_ERROR_MISSING_VALUE_SET,
	MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_STRING,
	MINIRT_ARGS_ERROR_DUPLICATE_KEY,
	MINIRT_ARGS_ERROR_DUPLICATE_VALUE,
	MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_BOOLEAN,
}	t_minirt_args_error_type;

typedef struct s_minirt_args_error_unknown_parameter
{
	const char	*arg;
}	t_minirt_args_error_unknown_parameter;

typedef struct s_minirt_args_error_malformed_parameter
{
	const char	*arg;
}	t_minirt_args_error_malformed_parameter;

typedef struct s_minirt_args_error_missing_entry
{
	const t_minirt_args_options_map	*option;
}	t_minirt_args_error_missing_entry;

typedef struct s_minirt_args_error_missing_value_map
{
	const t_minirt_args_options_map	*option;
	char							*key;
}	t_minirt_args_error_missing_value_map;

typedef struct s_minirt_args_error_missing_value_set
{
	t_minirt_args_options_set	*option;
}	t_minirt_args_error_missing_value_set;

typedef struct s_minirt_args_error_duplicate_parameter_string
{
	const t_minirt_args_options_string	*option;
}	t_minirt_args_error_duplicate_parameter_string;

typedef struct s_minirt_args_error_duplicate_key
{
	const t_minirt_args_options_map	*option;
	char							*key;
}	t_minirt_args_error_duplicate_key;

typedef struct s_minirt_args_error_duplicate_value
{
	const t_minirt_args_options_set	*option;
	const char						*value;
}	t_minirt_args_error_duplicate_value;

typedef struct s_minirt_args_error_duplicate_parameter_boolean
{
	const t_minirt_args_options_boolean	*option;
}	t_minirt_args_error_duplicate_parameter_boolean;

typedef union u_minirt_args_error_value
{
	t_minirt_args_error_unknown_parameter			unknown_parameter;
	t_minirt_args_error_malformed_parameter			malformed_parameter;
	t_minirt_args_error_missing_entry				missing_entry;
	t_minirt_args_error_missing_value_map			missing_value_map;
	t_minirt_args_error_missing_value_set			missing_value_set;
	t_minirt_args_error_duplicate_parameter_string	duplicate_parameter_string;
	t_minirt_args_error_duplicate_key				duplicate_key;
	t_minirt_args_error_duplicate_value				duplicate_value;
	t_minirt_args_error_duplicate_parameter_boolean	duplicate_parameter_boolean;
}	t_minirt_args_error_value;

typedef struct s_minirt_args_error
{
	t_minirt_args_error_type	type;
	t_minirt_args_error_value	value;
}	t_minirt_args_error;

typedef enum e_minirt_args_result_type
{
	MINIRT_ARGS_RESULT_OK,
	MINIRT_ARGS_RESULT_ERROR,
}	t_minirt_args_result_type;

typedef union u_minirt_args_result_value
{
	t_minirt_args		ok;
	t_minirt_args_error	error;
}	t_minirt_args_result_value;

typedef struct s_minirt_args_result
{
	t_minirt_args_result_type	type;
	t_minirt_args_result_value	value;
}	t_minirt_args_result;

/**
 * @brief parse args
 *
 *  parameter has 4 types: string, map, set, boolean
 *  string: "--name" "VALUE" or "--name=VALUE" or "-n" "VALUE" or "-nVALUE"
 *  map: "--name" "KEY=VALUE" or "-n" "KEY=VALUE" or "-nKEY=VALUE"
 *  set: "--name" "VALUE" or "-n" "VALUE" or "-nVALUE"
 *  boolean: "--name" or "-n" or "--name=0"(1/0/true/false) or "-nm"("-n" "-m")
 *
 * @param argc first parameter from main
 * @param argv second parameter from main
 * @param options
 * @param out union ok or error, depends on return value
 * @return t_err true on error, false on success
 */
t_err		minirt_args(
				unsigned int argc,
				char **argv,
				t_minirt_args_options options,
				t_minirt_args_result *out);

void		minirt_args_free(
				t_minirt_args *self);
void		minirt_args_free_error(
				t_minirt_args_error *error);
void		minirt_args_free_result(
				t_minirt_args_result *value);
const char	*minirt_args_get_string(
				t_minirt_args *self,
				const char *name);
bool		minirt_args_set_has(
				t_minirt_args *self,
				const char *name,
				const char *value);
const char	*minirt_args_map_get(
				t_minirt_args *self,
				const char *name,
				const char *key);
bool		minirt_args_get_boolean(
				t_minirt_args *self,
				const char *name,
				bool *out);
t_err		minirt_args_set_foreach(
				t_minirt_args *self,
				const char *name,
				void *context,
				t_err (*func)(void *context, const char *value));
t_err		minirt_args_map_foreach(
				t_minirt_args *self,
				const char *name,
				void *context,
				t_err (*func)(void *context, char *key, const char *value));

#endif
