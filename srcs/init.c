/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:00:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/17 13:15:35 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

int	verif_data(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return -1;
	while (i < ac)
	{
		j = -1;
		while (++j < ft_strlen(av[i]))
			if (ft_is_nb(av[i][j]) == -1)
				return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	(void)ac;

	data->ready = 0;
	data->finish = false ;
	data->death = 0;
	data->time_start = get_time_ms();
	data->nb_philo = mini_atoi(av[1]);
	data->time_to_die = mini_atoi(av[2]);
	data->time_to_eat = mini_atoi(av[3]);
	data->time_to_sleep = mini_atoi(av[4]);
	if (av[5])
		data->nb_time_philo_eat = mini_atoi(av[5]);
	else
		data->nb_time_philo_eat = -2;
	if (data->nb_philo > INT_MAX || data->time_to_die > INT_MAX ||
		data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX ||
		data->nb_time_philo_eat > INT_MAX || data->nb_philo == 0 ||
		data->nb_philo > 200)
		return (-1);
	data->philos = malloc(sizeof(data->philos) * data->nb_philo);
	if (!data->philos)
		return -1;
	int i = 0;

	while (i < data->nb_philo)
	{
		data->philos[i].last_eat_time = get_time_ms();
		// printf("%llu\n", data->philos[i].last_eat_time);
		data->philos[i].status = 0;
		data->philos[i].id = i + 1;
		// printf("|%d|\n", data->philos[i].id);
		i++;
	}
	return (0);
}
