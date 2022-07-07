/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 04:07:12 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/07 14:36:02 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static const char	*get_phil_msg(enum e_phil_msg msg)
{
	if (msg == PHIL_DIE)
		return ("%u %d is dying\n");
	else if (msg == PHIL_EAT)
		return ("%u %d is eating\n");
	else if (msg == PHIL_SLEEP)
		return ("%u %d is sleeping\n");
	else if (msg == PHIL_FORK_TAKEN)
		return ("%u %d has taken a fork\n");
	else if (msg == PHIL_THINK)
		return ("%u %d is thinking\n");
	return ("get_code_msg error: unknown enum in msg");
}

int	print_msg(t_rick *rick, int id, unsigned int ts, enum e_phil_msg msg)
{
	pthread_mutex_lock(&rick->mut_sim_status);
	if (rick->sim_status != SIM_RUN)
	{
		pthread_mutex_unlock(&rick->mut_sim_status);
		return (1);
	}
	printf(get_phil_msg(msg), ts, id);
	pthread_mutex_unlock(&rick->mut_sim_status);
	return (0);
}
