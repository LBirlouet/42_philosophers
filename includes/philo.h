/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:34:46 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/15 14:26:11 by lbirloue         ###   ########.fr       */
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

# define error_0 "./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]\n"


typedef struct s_philos{
	pthread_t	thread_philo;
	pthread_mutex_t	mutex_philo;
	int i;
	int	s_death;
}	t_philos;

typedef struct s_data{
	int			nb_philo;
	int			nb_time_philo_eat;
	u_int64_t	time_to_die;
	u_int64_t	time_to_eat;
	u_int64_t	time_to_sleep;
	t_philos	*philos;
	u_int64_t	time_start;

}	t_data;

//FONCITONS
//UTILS
int	ft_strlen(char *str);
int	ft_is_nb(char c);
long long	mini_atoi(char *str);
u_int64_t	get_time_ms(void);
void	my_sleep(t_data *data, uint64_t time);

//INIT
int	verif_data(int ac, char **av);
int	init_data(t_data *data, int ac, char **av);

//PRINT
void	print_eat(t_data *data, int wich_philo);
void	print_fork(t_data *data, int wich_philo);
void	print_death(t_data *data, int wich_philo);

//ONE_PHILO
int	one_phil(t_data *data);
void	*one_philo_r(void *data);

//MAIN
int	main(int ac, char **av);

#endif