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

#ifdef MOCK_BRANCH_NO_WRAP
# include "prelude_gnu_source.h"
#endif

#include <stdlib.h>

#include <stdio.h>

#ifdef MOCK_BRANCH_NO_WRAP
# include <dlfcn.h>
#endif

#include "branch.h"
#include "mock_branch_internal.h"

#ifdef MOCK_BRANCH_NO_WRAP

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
	if (!ptr)
		return ;
	mock_branch_internal()->malloc_count--;
	original(ptr);
}

#else

extern void	__real_free(void *ptr);

void	__wrap_free(void *ptr)
{
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
	{
		__real_free(ptr);
		return ;
	}
	if (!ptr)
		return ;
	mock_branch_internal()->malloc_count--;
	__real_free(ptr);
}

#endif
