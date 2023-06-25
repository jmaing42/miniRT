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

#include "prelude_gnu_source.h"

#include <stdlib.h>

#include <stdio.h>

#include <dlfcn.h>

#include "branch.h"
#include "mock_branch_internal.h"

typedef void	(*t_original)(void *ptr);

static void	failed_to_find_original(void)
{
	fputs("Failed to find original malloc() function.\n", stderr);
	exit(BRANCH_ERROR);
}

void	free(void *ptr)
{
	const t_original	original = (t_original)dlsym(RTLD_NEXT, "free");

	if (!original)
	{
		branch_unexpected_error();
		failed_to_find_original();
	}
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
	{
		original(ptr);
		return ;
	}
	mock_branch_internal()->malloc_count--;
	original(ptr);
}
