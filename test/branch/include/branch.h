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

#ifndef BRANCH_H
# define BRANCH_H

# include <stdbool.h>

/**
 * @brief to test all branches, in mock functions
 *
 * @param branch_count count of branches to test
 * @return int 1 to branch_count - 1 and 0 on successful, -1 on failure
 *
 * 0: everything is ok
 * 1 to branch_count - 1: failure, or successful partially
 */
int		branch(int branch_count);

/**
 * @brief call when unexpected error occurred in mock functions
 *
 * @remarks don't call outside mock functions
 */
void	branch_unexpected_error(void);

/**
 * @brief check if all branch was OK
 *
 * @return true on all is OK. you may exit with any code
 * @return false on some branch is not OK. you must exit with code 126 or 127
 */
bool	branch_all_ok(void);

# define BRANCH_OK 127
# define BRANCH_ERROR 126

#endif
