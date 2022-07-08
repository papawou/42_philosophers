/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 04:07:22 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/08 03:10:19 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philosophers.h"


void ft_usleep(unsigned int t)
{
	unsigned int	t_start;

	t /= 1000;
	t_start = get_timestamp();
	while ((get_timestamp() - t_start) < t)
		usleep(50);
}

t_philo	create_philo(t_rick *rick, unsigned int idx)
{
	t_philo	philo;

	philo.id = idx;
	philo.rick = rick;
	philo.last_eat = rick->lasteats + idx;
	philo.m_eat = rick->muts_lasteat + idx;
	
	philo.forks[idx % 2] = rick->forks + idx;
	philo.forks[!(idx % 2)] = rick->forks + ((idx + 1) % rick->nb_phils);
	
	return (philo);
}

void	*philo_routine(void *args)
{
	t_philo		ph;
	unsigned int time_to_eat;
	unsigned int time_to_sleep;

	ph = *(t_philo *) args;
	time_to_eat = ph.rick->time_to_eat;
	time_to_sleep = ph.rick->time_to_sleep;
	while (ph.rick->sim_status == SIM_RUN)
	{
		pthread_mutex_lock(ph.forks[0]);
		print_msg(ph.rick, ph.id, PHIL_FORK_TAKEN);
		pthread_mutex_lock(ph.forks[1]);
		print_msg(ph.rick, ph.id, PHIL_FORK_TAKEN);
		pthread_mutex_lock(ph.m_eat);
		*ph.last_eat = get_timestamp_start();
		pthread_mutex_unlock(ph.m_eat);
		print_msg(ph.rick, ph.id, PHIL_EAT);
		ft_usleep(time_to_eat);
		pthread_mutex_unlock(ph.forks[0]);
		pthread_mutex_unlock(ph.forks[1]);
		print_msg(ph.rick, ph.id, PHIL_SLEEP);
		ft_usleep(time_to_sleep);
		print_msg(ph.rick, ph.id, PHIL_THINK);
	}
	return args;
}
