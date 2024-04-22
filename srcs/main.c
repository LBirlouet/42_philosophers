/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/17 13:22:08 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*check_routine(void *data)
{
	t_data *cpdata = (t_data*)data;

	return 0;
}

void	*philo(void *data)
{
	t_philos *philo = (t_philos*)data;

	printf("||%d||\n", philo->id);
	printf("%llu\n", philo->data.time_start);
	return 0;
}


int	start_phil(t_data *data)
{
	data->tempo = 0;
	data->index = 0;
	// printf("nb philos = %d\n", data->nb_philo);
	int	i;

	i = 0;
	while (i < data->nb_philo - 1)
	{
		pthread_mutex_init(&data->philos[i].locked, NULL);
		pthread_mutex_init(&data->philos[i].left_f, NULL);
		pthread_mutex_init(&data->philos[i].right_f, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].thread_philo, NULL, &philo, &data->philos[i]);
		i++;
	}
	pthread_create(&data->philos[i].thread_philo, NULL, &check_routine, data);


	
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_philo, NULL);
		i++;
	}
		i = 0;
	while (i < data->nb_philo - 1)
	{
		pthread_mutex_destroy(&data->philos[i].locked);
		pthread_mutex_destroy(&data->philos[i].left_f);
		pthread_mutex_destroy(&data->philos[i].right_f);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (verif_data(ac,av)|| init_data(&data, ac, av))
		return (printf(error_0), 1);
	printf("good data\n");
	if (data.nb_philo == 1)
		return (one_phil(&data));
	else
		return (start_phil(&data));
	return (0);
}