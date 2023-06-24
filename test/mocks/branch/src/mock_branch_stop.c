/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_branch_stop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/25 02:07:08 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock_branch.h"

#include <stdio.h>
#include <stdlib.h>

#include "branch.h"
#include "mock_branch_internal.h"

static void	not_started(void)
{
	fputs("mock is not started.\n", stderr);
	exit(BRANCH_ERROR);
}

static void	paused(void)
{
	fputs("mock is paused.\n", stderr);
	exit(BRANCH_ERROR);
}

static void	opened_fd_count(void)
{
	fputs("some fds are not closed properly.\n", stderr);
	exit(BRANCH_ERROR);
}

static void	malloc_count(void)
{
	fputs("some memory is not freed properly.\n", stderr);
	exit(BRANCH_ERROR);
}

void	mock_branch_stop(bool ignore_error)
{
	if (!mock_branch_internal()->started)
		not_started();
	if (mock_branch_internal()->paused)
		paused();
	if (!ignore_error)
	{
		if (mock_branch_internal()->opened_fd_count != 0)
			opened_fd_count();
		if (mock_branch_internal()->malloc_count != 0)
			malloc_count();
	}
	mock_branch_internal()->started = false;
}
