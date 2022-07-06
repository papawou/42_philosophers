/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 04:07:22 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/06 04:08:37 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	create_philo(t_rick *rick, unsigned int idx)
{
	t_philo	philo;

	philo.id = idx;
	philo.rick = rick;
	philo.last_eat = rick->lasteats + idx;
	philo.m_eat = rick->muts_lasteat + idx;
	philo.forks[0] = rick->forks + idx;
	philo.forks[1] = rick->forks + ((idx + 1) % rick->nb_phils);
	return (philo);
}

int	print_philo_msg(enum e_phil_msg msg, t_philo *ph)
{
	return (print_msg(ph->rick, ph->id, get_timestamp(), msg));
}

void	*philo_routine(void *args)
{
	t_philo		*ph;

	ph = (t_philo *) args;
	while (ph->rick->sim_status == SIM_RUN)
	{
		pthread_mutex_lock(ph->forks[0]);
		print_philo_msg(PHIL_FORK_TAKEN, ph);
		pthread_mutex_lock(ph->forks[1]);
		print_philo_msg(PHIL_FORK_TAKEN, ph);
		pthread_mutex_lock(ph->m_eat);
		gettimeofday(ph->last_eat, NULL);
		pthread_mutex_unlock(&ph->m_eat);
		print_philo_msg(PHIL_EAT, ph);
		usleep(TIME_TO_EAT);	
		pthread_mutex_unlock(ph->forks[0]);
		pthread_mutex_unlock(ph->forks[1]);
		print_philo_msg(PHIL_SLEEP, ph);
		usleep(TIME_TO_SLEEP);
		print_philo_msg(PHIL_THINK, ph);
	}
	return args;
}
