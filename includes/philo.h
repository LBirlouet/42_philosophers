/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:34:46 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/12 15:46:19 by lbirloue         ###   ########.fr       */
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

# define error_0 "Bad arguments\n./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_data{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_philo_eat;
	pthread_t	*thread_philos;
	
}	t_data;

//FONCITONS
//UTILS
int	ft_strlen(char *str);
int	ft_is_nb(char c);
int	mini_atoi(char *str);

//INIT
int	verif_data(int ac, char **av);
int	init_data(t_data *data, int ac, char **av);

//MAIN
int	main(int ac, char **av);

#endif