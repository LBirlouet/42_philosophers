/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndessard <ndessard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:42:24 by ndessard          #+#    #+#             */
/*   Updated: 2024/04/19 16:12:23 by ndessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <stdatomic.h>

typedef struct s_philo
{
	int				id;
	long			last_eat;
	int				nbr_eat;
	int				left_fork;
	int				right_fork;
	int				verif;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	int				nb_of_time;
	int				dead;
	atomic_int		eat_en;
	int				all_eat;
	time_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_full;
	pthread_mutex_t	*fork;
}	t_data;

/*--utils.c--*/
int			check_value(char **av);
long long	ft_atol(char *av);
time_t		get_time(t_data *data);
void		print(int id, t_data *data, char *msg);
void		ft_sleep(t_data *data, time_t end);
void		ft_join(t_data *data);
/*--routine--*/
int			only_one(t_data *data);
void		*routine(void *phil);
void		eat(t_philo *philo, int id);
/*--destroy--*/
void		destroy_fork(t_data *data, int f, int id);
void		destroy_all(t_data *data);

#endif