/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:56:07 by sde-mull          #+#    #+#             */
/*   Updated: 2022/12/30 17:26:02 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	main(int argc, char *argv[])
{
	if (check_input(argc, argv) != 0)
		return (printf("Error:\nInvalid input\n"));
	if (!ft_convert_info(argv, argc))
		return (printf("Error:\nThere must be at least 1 philo\n"));
	if (!ft_create_mutex())
		return (printf("Failed to create array\n"));
	init_philo();
	if (ft_reunion())
		return (printf("Error:\nFailed to create/join thread\n"));
	destroy_mutex();
	free(ginfo()->locker);
	free(ginfo()->eat);
	return (0);
}
