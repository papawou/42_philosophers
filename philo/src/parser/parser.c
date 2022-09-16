/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:29:09 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/16 02:47:58 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_args2(char *argv[], int argc, t_rick *rick)
{
	if (argc != 6)
	{
		rick->min_eat_times = -1;
		return (0);
	}
	if (ft_atoi_safe(argv[5], &rick->min_eat_times) == -1)
		return (1);
	else if (rick->min_eat_times < 0)
		return (1);
	return (0);
}

int	parse_args(char *argv[], int argc, t_rick *rick)
{
	int	n;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_atoi_safe(argv[1], &n) == -1)
		return (1);
	if (n < 1)
		return (1);
	rick->nb_phils = n;
	if (ft_atoi_safe(argv[2], &n) == -1)
		return (1);
	if (n < 0)
		return (1);
	rick->time_to_die = n;
	if (ft_atoi_safe(argv[3], &n) == -1)
		return (1);
	if (n < 0)
		return (1);
	rick->time_to_eat = n * 1000;
	if (ft_atoi_safe(argv[4], &n) == -1)
		return (1);
	if (n < 0)
		return (1);
	rick->time_to_sleep = n * 1000;
	return (parse_args2(argv, argc, rick));
}
