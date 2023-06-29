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

const t_minirt_args_options	g_options = {
	NULL,
	0,
	NULL,
	0,
	NULL,
	0,
	NULL,
	0,
	MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_ERROR,
	MINIRT_ARGS_OPTIONS_MALFORMED_PARAMETER_ERROR,
	false,
};
