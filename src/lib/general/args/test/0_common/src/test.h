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

#ifndef TEST_H
# define TEST_H

# include "minirt/base_types.h"

# include "minirt/args.h"

t_err	print_result(t_minirt_args_result result);

t_err	print_error(
			t_minirt_args_error error);
t_err	print_error_unknown_parameter(
			t_minirt_args_error_unknown_parameter error);
t_err	print_error_malformed_parameter(
			t_minirt_args_error_malformed_parameter error);
t_err	print_error_missing_value_string(
			t_minirt_args_error_missing_value_string error);
t_err	print_error_missing_entry(
			t_minirt_args_error_missing_entry error);
t_err	print_error_missing_value_map(
			t_minirt_args_error_missing_value_map error);
t_err	print_error_missing_value_set(
			t_minirt_args_error_missing_value_set error);
t_err	print_error_duplicate_parameter_string(
			t_minirt_args_error_duplicate_parameter_string error);
t_err	print_error_duplicate_key(
			t_minirt_args_error_duplicate_key error);
t_err	print_error_duplicate_value(
			t_minirt_args_error_duplicate_value error);
t_err	print_error_duplicate_parameter_boolean(
			t_minirt_args_error_duplicate_parameter_boolean error);

t_err	print_args(
			t_minirt_args args);
t_err	print_args_parameter_string(
			t_minirt_args_parameter_string *param);
t_err	print_args_parameter_map(
			t_minirt_args_parameter_map *param);
t_err	print_args_parameter_set(
			t_minirt_args_parameter_set *param);
t_err	print_args_parameter_boolean(
			t_minirt_args_parameter_boolean *param);
t_err	print_args_parameters_string(
			t_minirt_args_parameter_string *param,
			size_t count);
t_err	print_args_parameters_map(
			t_minirt_args_parameter_map *param,
			size_t count);
t_err	print_args_parameters_set(
			t_minirt_args_parameter_set *param,
			size_t count);
t_err	print_args_parameters_boolean(
			t_minirt_args_parameter_boolean *param,
			size_t count);
t_err	print_args_operands(
			const char **operands,
			size_t count);

#endif
