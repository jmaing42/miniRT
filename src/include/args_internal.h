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

#ifndef ARGS_INTERNAL_H
# define ARGS_INTERNAL_H

# include "minirt/args.h"

# include "minirt/common/array_builder_types.h"

typedef enum e_minirt_args_state_type
{
	MINIRT_ARGS_STATE_ERROR,
	MINIRT_ARGS_STATE_ANYTHING,
	MINIRT_ARGS_STATE_ENTRY,
	MINIRT_ARGS_STATE_VALUE,
	MINIRT_ARGS_STATE_STRING,
	MINIRT_ARGS_STATE_ARGS,
}	t_minirt_args_state_type;

typedef struct s_minirt_args_parameter_map_builder {
	const t_minirt_args_options_map	*option;
	t_minirt_array_builder			*builder;
}	t_minirt_args_parameter_map_builder;

typedef struct s_minirt_args_parameter_set_builder {
	const t_minirt_args_options_set	*option;
	t_minirt_array_builder			*builder;
}	t_minirt_args_parameter_set_builder;

typedef union u_minirt_args_state_value
{
	const t_minirt_args_options_string	*string;
	const t_minirt_args_options_map		*map;
	const t_minirt_args_options_set		*set;
	const t_minirt_args_options_boolean	*boolean;
}	t_minirt_args_state_value;

typedef struct s_minirt_args_state
{
	t_minirt_args_state_type	state_type;
	t_minirt_args_state_value	state_value;
	t_minirt_array_builder		*args;
	t_minirt_array_builder		*params_string;
	t_minirt_array_builder		*params_map;
	t_minirt_array_builder		*params_set;
	t_minirt_array_builder		*params_boolean;
	t_minirt_args_error			error;
}	t_minirt_args_state;

typedef enum e_minirt_args_type
{
	MINIRT_ARGS_TYPE_ARG,
	MINIRT_ARGS_TYPE_MALFORMED_PARAMETER,
	MINIRT_ARGS_TYPE_LONG_WITHOUT_VALUE,
	MINIRT_ARGS_TYPE_LONG_STRING_WITH_VALUE_OR_LONG_BOOLEAN_WITH_VALUE,
	MINIRT_ARGS_TYPE_SHORT,
}	t_minirt_args_type;

t_err				minirt_args_state_init(
						t_minirt_args_state *self);
void				minirt_args_state_deinit(
						t_minirt_args_state *self);

t_err				minirt_args_malloc_error(
						t_minirt_args_state *state,
						t_minirt_args_result *out);

t_err				minirt_args_next(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_anything(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_string(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_entry(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_value(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_args(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);

t_err				minirt_args_finalize(
						t_minirt_args_state *mut_state,
						t_minirt_args_result *out);

t_err				minirt_args_error(
						t_minirt_args_state *mut_state,
						t_minirt_args_result *out);

t_err				minirt_args_add_string(
						t_minirt_args_state *mut_state,
						const char *value);
t_err				minirt_args_add_map(
						t_minirt_args_state *mut_state,
						char *key,
						const char *value);
t_err				minirt_args_add_map_error_duplicate_key(
						t_minirt_args_state *mut_state,
						char *key);
t_err				minirt_args_add_set(
						t_minirt_args_state *mut_state,
						const char *value);
t_err				minirt_args_add_boolean(
						t_minirt_args_state *mut_state);
t_err				minirt_args_add_arg(
						t_minirt_args_state *mut_state,
						const char *arg);

t_minirt_args_type	minirt_args_identify(
						const char *arg);

t_err				minirt_args_next_anything_arg(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_anything_malformed(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_anything_long_no_v(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_anything_long(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_anything_short_no_v(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_anything_short(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);

t_err				minirt_args_next_anything_unknown(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);
t_err				minirt_args_next_anything_no_v_string(
						t_minirt_args_state *mut_state);
t_err				minirt_args_next_anything_no_v_map(
						t_minirt_args_state *mut_state);
t_err				minirt_args_next_anything_no_v_set(
						t_minirt_args_state *mut_state);
t_err				minirt_args_next_anything_no_v_boolean(
						t_minirt_args_state *mut_state);
t_err				minirt_args_next_anything_long_string(
						t_minirt_args_state *mut_state,
						size_t option_length,
						const char *arg);
t_err				minirt_args_next_anything_long_set(
						t_minirt_args_state *mut_state,
						size_t option_length,
						const char *arg);
t_err				minirt_args_next_anything_short_string(
						t_minirt_args_state *mut_state,
						const char *arg);
t_err				minirt_args_next_anything_short_map(
						t_minirt_args_state *mut_state,
						const char *arg);
t_err				minirt_args_next_anything_short_set(
						t_minirt_args_state *mut_state,
						const char *arg);
t_err				minirt_args_next_anything_short_boolean(
						t_minirt_args_state *mut_state,
						t_minirt_args_options *options,
						const char *arg);

void				minirt_args_free_state_ok(
						t_minirt_args_state *state);

#endif
