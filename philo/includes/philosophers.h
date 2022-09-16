/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 04:07:19 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/16 02:39:55 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>

enum e_sim_status
{
	SIM_RUN,
	SIM_STOP,
	SIM_WAIT
};

typedef struct s_rick	t_rick;

typedef struct s_philo
{
	int									id;
	unsigned int						eat_times;
	unsigned int						last_eat;
	pthread_mutex_t						m_eat;
	pthread_mutex_t						*forks[2];
	pthread_t							th;
	t_rick								*rick;
}	t_philo;

typedef struct s_rick
{
	unsigned int				nb_phils;
	unsigned int				time_to_die;
	unsigned int				time_to_sleep;
	unsigned int				time_to_eat;
	int							min_eat_times;

	pthread_mutex_t				*forks;

	pthread_mutex_t				mut_sim_status;
	enum e_sim_status			sim_status;

	t_philo						*phs;
}	t_rick;

enum e_phil_msg {
	PHIL_FORK_TAKEN,
	PHIL_EAT,
	PHIL_SLEEP,
	PHIL_THINK,
	PHIL_DIE
};

//time.c
unsigned int	get_timestamp(void);
unsigned int	get_timestamp_start(void);

//msg.c
const char		*get_phil_msg(enum e_phil_msg msg);
int				print_msg(t_rick *rick, int id, enum e_phil_msg msg);

//philo
t_philo			create_philo(t_rick *rick, unsigned int idx);
void			*philo_routine(void *args);

//clean_exit
int				clean_exit(void);

//rick
int				clean_rick(void *ptr_rick);
int				create_rick(t_rick *rick);
int				init_rick(t_rick *rick);
int				clean_muts_rick(t_rick *rick, int i);

//parser
int				ft_atoi_safe(char *str, int *dst);
int				parse_args(char *argv[], int argc, t_rick *rick);

#endif