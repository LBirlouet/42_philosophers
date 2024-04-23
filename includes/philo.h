/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:34:46 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/23 12:58:40 by lbirloue         ###   ########.fr       */
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

# define error_0 "./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]\n"



//STATUS
// 1 EATING
// 2 SLEEPING
// 3 THINKING
// 4 DEAD


//modif u_int64_t en t_time machin chouette

typedef struct s_philos{
	int id;
	int nb_eat;
	int status;
	int	left_f;
	int right_f;
	pthread_t	thread_philo;
	u_int64_t last_eat_time;
	struct s_data *data;
}	t_philos;

typedef struct s_data{
	int			ready;
	int			nb_philo;
	int			nb_time_philo_eat;
	bool		finish;
	int			death;
	int			index;
	int			eat_max;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_msg;
	u_int64_t	time_to_die;
	u_int64_t	time_to_eat;
	u_int64_t	time_to_sleep;
	t_philos	*philos;
	u_int64_t	time_start;

	int tempo;

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
void	print(t_data *data, int id, char *msg);


//ONE_PHILO
int	one_phil(t_data *data);
void	*one_philo_r(void *data);

//MAIN
int	main(int ac, char **av);

#endif