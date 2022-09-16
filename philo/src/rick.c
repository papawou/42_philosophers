/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 02:35:28 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/16 02:35:28 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "philosophers.h"

int	clean_rick(void *ptr_rick)
{
	static t_rick	*rick = NULL;

	if (ptr_rick)
	{
		rick = ptr_rick;
		return (0);
	}
	else if (rick)
	{
		free(rick->forks);
		free(rick->phs);
	}
	return (1);
}

int	create_rick(t_rick *rick)
{
	clean_rick(rick);
	rick->sim_status = SIM_WAIT;
	rick->forks = NULL;
	rick->phs = NULL;
	rick->forks = malloc(sizeof(pthread_mutex_t) * rick->nb_phils);
	rick->phs = malloc(sizeof(t_philo) * rick->nb_phils);
	if (!rick->forks || !rick->phs)
		return (clean_exit());
	return (0);
}

int	clean_muts_rick(t_rick *rick, int i)
{
	pthread_mutex_destroy(&rick->mut_sim_status);
	while (0 <= i)
	{
		pthread_mutex_destroy(rick->forks + i);
		pthread_mutex_destroy(&rick->phs[i].m_eat);
		--i;
	}
	return (1);
}

int	init_rick(t_rick *rick)
{
	unsigned int	i;

	if (pthread_mutex_init(&rick->mut_sim_status, NULL))
		return (1);
	i = 0;
	while (i < rick->nb_phils)
	{
		rick->phs[i] = create_philo(rick, i);
		if (pthread_mutex_init(rick->forks + i, NULL))
			return (clean_muts_rick(rick, i - 1));
		if (pthread_mutex_init(&rick->phs[i].m_eat, NULL))
		{
			pthread_mutex_destroy(rick->forks + i);
			return (clean_muts_rick(rick, i - 1));
		}
		++i;
	}
	return (0);
}
