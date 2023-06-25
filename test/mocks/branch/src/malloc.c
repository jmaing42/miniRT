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

static void	failed_to_allocate_memory(void)
{
	branch_unexpected_error();
	fputs("Failed to allocate memory.\n", stderr);
	exit(BRANCH_ERROR);
}

static void	exit_unexpected_error(void)
{
	branch_unexpected_error();
	fputs("Unexpected error occurred.\n", stderr);
	exit(BRANCH_ERROR);
}

#ifdef MOCK_BRANCH_NO_WRAP

typedef void	*(*t_original)(size_t size);

static void	failed_to_find_original(void)
{
	branch_unexpected_error();
	fputs("Failed to find original malloc() function.\n", stderr);
	exit(BRANCH_ERROR);
}

void	*malloc(size_t size)
{
	const t_original	original = (t_original)dlsym(RTLD_NEXT, "malloc");
	int					current;
	void				*result;

	if (!original)
		failed_to_find_original();
	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
		return (original(size));
	current = branch(2);
	if (current == -1)
		exit_unexpected_error();
	if (current == 1)
		return (NULL);
	mock_branch_internal()->malloc_count++;
	result = original(size);
	if (!result)
		failed_to_allocate_memory();
	return (result);
}

#else

extern void	*__real_malloc(size_t size);

void	*__wrap_malloc(size_t size)
{
	int		current;
	void	*result;

	if (!mock_branch_internal()->started || mock_branch_internal()->paused)
		return (__real_malloc(size));
	current = branch(2);
	if (current == -1)
		exit_unexpected_error();
	if (current == 1)
		return (NULL);
	mock_branch_internal()->malloc_count++;
	result = __real_malloc(size);
	if (!result)
		failed_to_allocate_memory();
	return (result);
}

#endif
