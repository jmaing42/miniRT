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
	t_minirt_args_options_map	*option;
	t_minirt_array_builder		*builder;
}	t_minirt_args_parameter_map_builder;

typedef struct s_minirt_args_parameter_set_builder {
	t_minirt_args_options_set	*option;
	t_minirt_array_builder		*builder;
}	t_minirt_args_parameter_set_builder;

typedef union u_minirt_args_state_value
{
	t_minirt_args_options_string	*string;
	t_minirt_args_options_map		*map;
	t_minirt_args_options_set		*set;
	t_minirt_args_options_boolean	*boolean;
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

t_err	minirt_args_state_init(
			t_minirt_args_state *self);
void	minirt_args_state_deinit(
			t_minirt_args_state *self);

t_err	minirt_args_malloc_error(
			t_minirt_args_state *state,
			t_minirt_args_result *out);

t_err	minirt_args_next(
			t_minirt_args_state *mut_state,
			t_minirt_args_options *options,
			const char *arg);
t_err	minirt_args_next_anything(
			t_minirt_args_state *mut_state,
			t_minirt_args_options *options,
			const char *arg);
t_err	minirt_args_next_string(
			t_minirt_args_state *mut_state,
			t_minirt_args_options *options,
			const char *arg);
t_err	minirt_args_next_entry(
			t_minirt_args_state *mut_state,
			t_minirt_args_options *options,
			const char *arg);
t_err	minirt_args_next_value(
			t_minirt_args_state *mut_state,
			t_minirt_args_options *options,
			const char *arg);
t_err	minirt_args_next_args(
			t_minirt_args_state *mut_state,
			t_minirt_args_options *options,
			const char *arg);

t_err	minirt_args_finalize(
			t_minirt_args_state *mut_state,
			t_minirt_args_result *out);

t_err	minirt_args_error(
			t_minirt_args_state *mut_state,
			t_minirt_args_result *out);

t_err	minirt_args_add_map(
			t_minirt_args_state *mut_state,
			char *key,
			char *value);
t_err	minirt_args_add_map_error_duplicate_key(
			t_minirt_args_state *mut_state,
			char *key,
			char *value);
t_err	minirt_args_add_arg(
			t_minirt_args_state *mut_state,
			const char *arg);

#endif
