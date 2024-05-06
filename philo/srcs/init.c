/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:00:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/05/06 10:56:11 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

int	verif_data(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (-1);
	while (i < ac)
	{
		j = -1;
		while (++j < ft_strlen(av[i]))
			if (ft_is_nb(av[i][j]) == -1)
				return (1);
		i++;
	}
	if (ft_strlen(av[1]) > 10 || ft_strlen(av[2]) > 10
		|| ft_strlen(av[3]) > 10 || ft_strlen(av[4]) > 10)
		return (1);
	return (0);
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philos)
		return (-1);
	if (pthread_mutex_init(&data->mutex_msg, NULL))
		return (-1);
	if (pthread_mutex_init(&data->mutex_death, NULL))
	{
		pthread_mutex_destroy(&data->mutex_msg);
		return (-1);
	}
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (destroy_mutex_init(data, i));
		i++;
	}
	return (0);
}

int	init_data2(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philos) * data->nb_philo);
	if (!data->philos)
		return (-1);
	while (i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].last_eat_time = get_time_ms();
		data->philos[i].status = 0;
		data->philos[i].id = i + 1;
		data->philos[i].left_f = i;
		data->philos[i].right_f = i + 1;
		if (i + 1 == data->nb_philo)
			data->philos[i].right_f = 0;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	int	i;

	i = 0;
	data->death = 0;
	data->eat_max = 0;
	data->nb_philo = mini_atoi(av[1]);
	data->time_to_die = mini_atoi(av[2]);
	data->time_to_eat = mini_atoi(av[3]);
	data->time_to_sleep = mini_atoi(av[4]);
	if (av[5])
		data->nb_time_philo_eat = mini_atoi(av[5]);
	else
		data->nb_time_philo_eat = -2;
	if (data->nb_philo > INT_MAX || data->time_to_die > INT_MAX
		|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX
		|| data->nb_time_philo_eat > INT_MAX || data->nb_philo == 0
		|| data->nb_philo > 200 || data->nb_time_philo_eat == 0)
		return (-1);
	return (init_data2(data));
}
