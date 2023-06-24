/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_branch_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/25 02:06:54 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock_branch.h"

#include <stdio.h>
#include <stdlib.h>

#include "branch.h"
#include "mock_branch_internal.h"

static void	already_started(void)
{
	fputs("mock is already started.\n", stderr);
	exit(BRANCH_ERROR);
}

void	mock_branch_start(bool may_partial)
{
	if (mock_branch_internal()->started)
		already_started();
	mock_branch_internal()->started = true;
	mock_branch_internal()->may_partial = may_partial;
	mock_branch_internal()->malloc_count = 0;
	mock_branch_internal()->opened_fd_count = 0;
	mock_branch_internal()->paused = false;
}
