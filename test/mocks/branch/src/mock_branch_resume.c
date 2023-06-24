/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_branch_resume.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/25 02:06:50 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock_branch.h"

#include <stdio.h>
#include <stdlib.h>

#include "branch.h"
#include "mock_branch_internal.h"

static void	not_paused(void)
{
	fputs("mock is not paused.\n", stderr);
	exit(BRANCH_ERROR);
}

void	mock_branch_resume(void)
{
	if (!mock_branch_internal()->paused)
		not_paused();
	mock_branch_internal()->paused = false;
}
