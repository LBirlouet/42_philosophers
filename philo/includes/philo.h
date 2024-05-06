/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:34:46 by lbirloue          #+#    #+#             */
/*   Updated: 2024/05/06 10:56:50 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdbool.h>

/*
# define ERROR "invalid arguments\n"
# define TAKE_FORK "\033[0;32;5;32mhas taken a fork\033[0m"
# define EATING "\033[0;38;5;39;3mis eating\033[0m"
# define THINKING "\033[0;38;5;226mis thinking\033[0m"
# define SLEEPING "\033[0;38;5;219mis sleeping\033[0m"
# define DIED "\033[1;38;5;210mdied\033[0m"
*/

# define ERROR "invalid arguments\n"
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DIED "\033[1;38;5;210mdied\033[0m"

typedef struct s_philos
{
	int				id;
	int				nb_eat;
	int				status;
	int				left_f;
	int				right_f;
	pthread_t		thread_philo;
	time_t			last_eat_time;
	struct s_data	*data;
}	t_philos;

typedef struct s_data
{
	long			nb_philo;
	long			nb_time_philo_eat;
	int				death;
	int				eat_max;
	pthread_mutex_t	only_one_f;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_death;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	t_philos		*philos;
	time_t			time_start;
}	t_data;

int			free_all(t_data *data);
int			destroy_all(t_data *data);
int			destroy_mutex_init(t_data *data, int i);
int			join(t_data *data);
int			ft_strlen(char *str);
int			ft_is_nb(char c);
long long	mini_atoi(char *str);
time_t		get_time_ms(void);
void		my_sleep(t_data *data, time_t time);
int			mutex_init(t_data *data);
int			verif_data(int ac, char **av);
int			init_data(t_data *data, char **av);
void		print(t_data *data, int id, char *msg);
int			one_phil(t_data *data);
void		*one_philo_r(void *data);
int			philosophers(t_data *data);
int			main(int ac, char **av);

#endif