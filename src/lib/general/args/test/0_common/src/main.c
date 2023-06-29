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

#include "test.h"

#include <stdio.h>
#include <stdlib.h>

#include "branch.h"
#include "mock_branch.h"

extern const t_minirt_args_options	g_options;

static void	test(int argc, char **argv)
{
	t_minirt_args_result	args;

	if (minirt_args(argc, argv, g_options, &args))
	{
		if (args.value.error.type == MINIRT_ARGS_ERROR_MALLOC_FAILURE)
		{
			if (branch_all_ok())
				exit(EXIT_FAILURE);
			exit(BRANCH_OK);
		}
		print_result(args);
		minirt_args_free_result(&args);
	}
}

int	main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IOLBF, 0);
	mock_branch_start(true);
	test(argc, argv);
	mock_branch_stop(false);
	if (branch_all_ok())
		return (EXIT_SUCCESS);
	return (BRANCH_OK);
}
