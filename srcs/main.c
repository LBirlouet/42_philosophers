/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/15 16:05:20 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

void	*more_philos_r(void *data)
{
	t_data	*cpdata = (t_data *)data;
	pthread_mutex_lock(&cpdata->philos->mutex_fork);
	printf("we\n");
	my_sleep(cpdata, 1000);
// sleep(1);
	pthread_mutex_unlock(&cpdata->philos->mutex_fork);
	return 0;
}

int	more_phil(t_data *data)
{
	printf("nb philos = %d\n", data->nb_philo);
	int	i;

	// i = 0;
	// while (i < 10)
	// {
	// 	printf("cc \n");
	// 	my_sleep(data, 1);
	// 	i++;
	// }


	i = 0;
	while (i < data->nb_philo - 1)
	{
		pthread_mutex_init(&data->philos[i].mutex_fork, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].thread_philo, NULL, &more_philos_r, data);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_philo, NULL);
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
		return (more_phil(&data));
	return (0);
}