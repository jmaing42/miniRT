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

t_err	print_args(t_minirt_args args)
{
	return (
		print_args_parameters_string(args.string, args.string_count)
		|| print_args_parameters_map(args.map, args.map_count)
		|| print_args_parameters_set(args.set, args.set_count)
		|| print_args_parameters_boolean(args.boolean, args.boolean_count)
		|| print_args_operands(args.args, args.arg_count)
	);
}
