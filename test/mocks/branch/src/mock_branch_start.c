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

#include "mock_branch.h"

#include <stdio.h>
#include <stdlib.h>

#include "branch.h"
#include "mock_branch_internal.h"

static void	already_started(void)
{
	fputs("mock is already started.", stderr);
	exit(BRANCH_ERROR);
}

void	mock_branch_start(bool may_partial)
{
	if (mock_branch_internal()->started)
		already_started();
	mock_branch_internal()->may_partial = may_partial;
	mock_branch_internal()->malloc_count = 0;
	mock_branch_internal()->opened_fd_count = 0;
	mock_branch_internal()->paused = false;
}
