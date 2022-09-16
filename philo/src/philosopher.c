/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 04:07:22 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/16 02:37:09 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philosophers.h"

void	ft_usleep(unsigned int t)
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
	philo.last_eat = 0;
	philo.eat_times = 0;
	philo.forks[idx % 2] = rick->forks + idx;
	if (rick->nb_phils == 1)
		philo.forks[1] = NULL;
	else
		philo.forks[!(idx % 2)] = rick->forks + ((idx + 1) % rick->nb_phils);
	return (philo);
}

void	*philo_routine(void *args)
{
	t_philo		*ph;

	ph = (t_philo *) args;
	while (ph->rick->sim_status == SIM_RUN)
	{
		pthread_mutex_lock(ph->forks[0]);
		print_msg(ph->rick, ph->id, PHIL_FORK_TAKEN);
		if (ph->forks[1] == NULL)
			break ;
		pthread_mutex_lock(ph->forks[1]);
		print_msg(ph->rick, ph->id, PHIL_FORK_TAKEN);
		pthread_mutex_lock(&ph->m_eat);
		ph->last_eat = get_timestamp_start();
		pthread_mutex_unlock(&ph->m_eat);
		print_msg(ph->rick, ph->id, PHIL_EAT);
		ft_usleep(ph->rick->time_to_eat);
		++ph->eat_times;
		pthread_mutex_unlock(ph->forks[0]);
		pthread_mutex_unlock(ph->forks[1]);
		print_msg(ph->rick, ph->id, PHIL_SLEEP);
		ft_usleep(ph->rick->time_to_sleep);
		print_msg(ph->rick, ph->id, PHIL_THINK);
	}
	return (args);
}
