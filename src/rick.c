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
		free(rick->ths);
		free(rick->forks);
		free(rick->muts_lasteat);
		free(rick->lasteats);
		free(rick->phs);
	}
	return (1);
}

int	create_rick(t_rick *rick)
{
	clean_rick(rick);

	rick->time_to_die = 310;
	rick->time_to_eat = 200 * 1000;
	rick->time_to_sleep = 100 * 1000;
	rick->nb_phils = 4;
	rick->nb_times_eat = -1;
	rick->ths = NULL;
	rick->forks = NULL;
	rick->muts_lasteat = NULL;
	rick->lasteats = NULL;
	rick->sim_status = SIM_WAIT;
	rick->phs = NULL;
	rick->ths = malloc(sizeof(pthread_t) * rick->nb_phils);
	rick->forks = malloc(sizeof(pthread_mutex_t) * rick->nb_phils);
	rick->muts_lasteat = malloc(sizeof(pthread_mutex_t) * rick->nb_phils);
	rick->lasteats = malloc(sizeof(unsigned int) * rick->nb_phils);
	rick->phs = malloc(sizeof(t_philo) * rick->nb_phils);
	if (!rick->ths || !rick->forks || !rick->muts_lasteat || !rick->lasteats || !rick->phs)
		return (clean_exit());
	memset(rick->lasteats, 0, sizeof(unsigned int) * rick->nb_phils);
	return (0);
}

int clean_muts_rick(t_rick *rick, int i)
{
	pthread_mutex_destroy(&rick->mut_sim_status);
	while (0 <= i)
	{
		pthread_mutex_destroy(rick->forks + i);
		pthread_mutex_destroy(rick->muts_lasteat + i);
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
		if (pthread_mutex_init(rick->forks + i, NULL))
			return clean_muts_rick(rick, i - 1);
		if (pthread_mutex_init(rick->muts_lasteat + i, NULL))
		{
			pthread_mutex_destroy(rick->forks + i);
			return clean_muts_rick(rick, i - 1);
		}
		rick->phs[i] = create_philo(rick, i);
		++i;
	}
	return (0);
}
