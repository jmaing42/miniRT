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

typedef struct s_minirt_args_map_entry
{
	char	*key;
	char	*value;
}	t_minirt_args_map_entry;

typedef union u_minirt_args_value {
	char					*string;
	t_minirt_args_map_entry	*map;
	char					**set;
	bool					boolean;
}	t_minirt_args_value;

typedef struct s_minirt_args_parameter {
	char				*key;
	t_minirt_args_value	*value;
}	t_minirt_args_parameter;

typedef struct s_minirt_args
{
	char					**args;
	t_minirt_args_parameter	*parameters;
}	t_minirt_args;

typedef enum e_minirt_args_error_type
{
	MINIRT_ARGS_ERROR_MALLOC_FAILURE,
	MINIRT_ARGS_ERROR_UNKNOWN_PARAMETER,
	MINIRT_ARGS_ERROR_MISSING_ENTRY,
	MINIRT_ARGS_ERROR_MISSING_VALUE,
	MINIRT_ARGS_ERROR_DUPLICATE_KEY,
	MINIRT_ARGS_ERROR_DUPLICATE_VALUE,
	MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER,
}	t_minirt_args_error_type;

typedef struct s_minirt_args_error_unknown_parameter
{
	char	*parameter_name;
}	t_minirt_args_error_unknown_parameter;

typedef struct s_minirt_args_error_missing_entry
{
	char	*parameter_name;
}	t_minirt_args_error_missing_entry;

typedef struct s_minirt_args_error_missing_value
{
	char	*parameter_name;
}	t_minirt_args_error_missing_value;

typedef struct s_minirt_args_error_duplicate_key
{
	char	*parameter_name;
	char	*key;
	char	**values;
}	t_minirt_args_error_duplicate_key;

typedef struct s_minirt_args_error_duplicate_value
{
	char	*parameter_name;
	char	*value;
}	t_minirt_args_error_duplicate_value;

typedef struct s_minirt_args_error_duplicate_parameter
{
	char	*parameter_name;
	char	**values;
}	t_minirt_args_error_duplicate_parameter;

typedef union u_minirt_args_error_value
{
	t_minirt_args_error_unknown_parameter	unknown_parameter;
	t_minirt_args_error_missing_entry		missing_entry;
	t_minirt_args_error_missing_value		missing_value;
	t_minirt_args_error_duplicate_key		duplicate_key;
	t_minirt_args_error_duplicate_value		duplicate_value;
	t_minirt_args_error_duplicate_parameter	duplicate_parameter;
}	t_minirt_args_error_value;

typedef struct s_minirt_args_error
{
	t_minirt_args_error_type	type;
	t_minirt_args_error_value	value;
}	t_minirt_args_error;

typedef union s_minirt_args_result
{
	t_minirt_args		ok;
	t_minirt_args_error	error;
}	t_minirt_args_result;

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
	bool								allow_empty;
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

typedef enum e_minirt_args_options_duplicate_parameter
{
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_ERROR,
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_IGNORE_IF_SAME,
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_USE_FIRST,
	MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_USE_LAST,
}	t_minirt_args_options_duplicate_parameter;

typedef struct s_minirt_args_options_scalar
{
	const char									*name;
	char										short_name;
	t_minirt_args_options_duplicate_parameter	on_duplicate;
	bool										accept_number;
	bool										accept_keyword;
}	t_minirt_args_options_scalar;

typedef enum e_minirt_args_options_unknown_parameter
{
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_ERROR,
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_IGNORE,
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_AS_ARGS,
}	t_minirt_args_options_unknown_parameter;

typedef struct s_minirt_args_options
{
	const t_minirt_args_options_scalar		**string_parameters;
	const t_minirt_args_options_map			**map_parameters;
	const t_minirt_args_options_set			**set_parameters;
	const t_minirt_args_options_scalar		**boolean_parameters;
	t_minirt_args_options_unknown_parameter	unknown_parameter;
}	t_minirt_args_options;

t_err	minirt_args(
			unsigned int argc,
			char **argv,
			t_minirt_args_options options,
			t_minirt_args_result *out);

void	minirt_args_free(
			t_minirt_args *self);
void	minirt_args_free_error(
			t_minirt_args_error *error);
char	*minirt_args_get_string(
			t_minirt_args *self);
bool	minirt_args_set_has(
			t_minirt_args *self,
			const char *name,
			const char *value);
char	*minirt_args_map_get(
			t_minirt_args *self,
			const char *name,
			const char *key);
bool	minirt_args_get_boolean(
			t_minirt_args *self,
			const char *name);
t_err	minirt_args_set_foreach(
			t_minirt_args *self,
			const char *name,
			void *context,
			t_err (*func)(void *context, char *value));
t_err	minirt_args_map_foreach(
			t_minirt_args *self,
			const char *name,
			void *context,
			t_err (*func)(void *context, char *key, char *value));

#endif
