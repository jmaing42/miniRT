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

static void	not_paused(void)
{
	fputs("mock is not paused.", stderr);
	exit(BRANCH_ERROR);
}

void	mock_branch_resume(void)
{
	if (!mock_branch_internal()->paused)
		not_paused();
	mock_branch_internal()->paused = false;
}
