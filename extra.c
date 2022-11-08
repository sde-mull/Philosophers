/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:56:13 by sde-mull          #+#    #+#             */
/*   Updated: 2022/10/20 15:56:14 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *c)
{
	int index;

	index = 0;
	while (c[index] >= '0' && c[index] <= '9')
		index++;
	if (!c[index])
		return(0);
	return (1);
}

int	ft_atoi(const char *str)
{
	signed int	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{	
		if (*str == '-')
			sign = -1;
		str++;
	}	
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

int	check_input(int arg, char **str)
{
	int index;

	index = 1;
	if (!str || arg < 5 || arg > 6)
		return(1);
	while (index < arg)
	{
		if (ft_isdigit(str[index]))
			return (2);
		if (ft_atoi(str[index]) < 0)
			return (3);
		index++;
	}
	return(0);
}