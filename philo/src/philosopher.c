/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 04:07:22 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/18 16:17:07 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philosophers.h"

int	ft_usleep(unsigned int t, t_rick *rick)
{
	unsigned int	t_start;

	t /= 1000;
	t_start = get_timestamp_start();
	while (rick->sim_status == SIM_RUN && (get_timestamp_start() - t_start) < t)
		usleep(100);
	return (rick->sim_status == SIM_STOP);
}

t_philo	create_philo(t_rick *rick, unsigned int idx)
{
	t_philo	philo;

	philo.id = idx;
	philo.rick = rick;
	philo.last_eat = 0;
	philo.eat_times = 0;
	philo.forks[idx % 2] = rick->forks + idx;
	if (rick->nb_phils == 1)
		philo.forks[1] = NULL;
	else
		philo.forks[!(idx % 2)] = rick->forks + ((idx + 1) % rick->nb_phils);
	return (philo);
}

static int	philo_eat(t_philo *ph)
{
	pthread_mutex_lock(ph->forks[0]);
	print_msg(ph->rick, ph->id, PHIL_FORK_TAKEN);
	if (ph->forks[1] == NULL)
	{
		pthread_mutex_unlock(ph->forks[0]);
		return (1);
	}
	pthread_mutex_lock(ph->forks[1]);
	print_msg(ph->rick, ph->id, PHIL_FORK_TAKEN);
	pthread_mutex_lock(&ph->m_eat);
	ph->last_eat = get_timestamp_start();
	pthread_mutex_unlock(&ph->m_eat);
	print_msg(ph->rick, ph->id, PHIL_EAT);
	if (ft_usleep(ph->rick->time_to_eat, ph->rick))
	{
		pthread_mutex_unlock(ph->forks[1]);
		pthread_mutex_unlock(ph->forks[0]);
		return (1);
	}
	++ph->eat_times;
	pthread_mutex_unlock(ph->forks[1]);
	pthread_mutex_unlock(ph->forks[0]);
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo		*ph;

	ph = (t_philo *) args;
	while (ph->rick->sim_status == SIM_RUN)
	{
		if (philo_eat(ph))
			break ;
		print_msg(ph->rick, ph->id, PHIL_SLEEP);
		ft_usleep(ph->rick->time_to_sleep, ph->rick);
	}
	return (args);
}
