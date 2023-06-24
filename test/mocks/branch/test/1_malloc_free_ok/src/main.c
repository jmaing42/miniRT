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

#include <stdio.h>
#include <stdlib.h>

#include "branch.h"
#include "mock_branch.h"

void	test(void)
{
	void	*first;
	void	*second;

	puts("start");
	first = malloc(1);
	if (!first)
	{
		puts("first failed");
		return ;
	}
	puts("first ok");
	second = malloc(1);
	if (!second)
	{
		puts("second failed");
		return ;
	}
	puts("second ok");
	free(first);
	free(second);
	puts("end");
}

int	main(void)
{
	mock_branch_start(true);
	test();
	mock_branch_stop(false);
	if (branch_all_ok())
		return (EXIT_SUCCESS);
	return (BRANCH_OK);
}
