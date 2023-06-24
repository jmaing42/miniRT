/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/06/25 02:13:01 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "branch.h"

#include <stdbool.h>

#include <unistd.h>
#include <sys/wait.h>

static bool	g_unexpected_error = false;
static bool	g_all_ok = true;

int	branch(int branch_count)
{
	int		i;
	pid_t	pid;
	int		exitstatus;

	i = 0;
	while (!g_unexpected_error && ++i < branch_count)
	{
		pid = fork();
		if (pid == -1)
			g_unexpected_error = true;
		if (!g_unexpected_error && pid)
		{
			waitpid(pid, &exitstatus, 0);
			if (WIFSIGNALED(exitstatus) || WEXITSTATUS(exitstatus) != BRANCH_OK)
				g_unexpected_error = 1;
		}
		else if (!g_unexpected_error)
		{
			g_all_ok = false;
			return (i);
		}
		else
			return (-1);
	}
	return (0);
}

void	branch_unexpected_error(void)
{
	g_unexpected_error = true;
}

bool	branch_all_ok(void)
{
	return (g_all_ok);
}
