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

#ifndef MOCK_BRANCH_INTERNAL_H
# define MOCK_BRANCH_INTERNAL_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_mock_branch
{
	bool	may_partial;
	bool	started;
	bool	paused;
	size_t	malloc_count;
	size_t	opened_fd_count;
}	t_mock_branch;

t_mock_branch	*mock_branch_internal(void);

#endif
