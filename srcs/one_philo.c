/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:10 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/26 12:44:54 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

void	*one_philo_r(void *data)
{
	t_data	*cpdata = (t_data *)data;
	printf("PHILO\n");
	//lock fork
	print(data, 1, "as taking a fork");
	printf("%ldu\n", cpdata->time_to_die);
	//lock fork
	my_sleep(cpdata, cpdata->time_to_die);
	
	print(data, 1, "is dead");
	
	return 0;
}

int	one_phil(t_data *data)
{
	//mettre une fork qui sert a r
	pthread_create(&data->philos[0].thread_philo, NULL, &one_philo_r, data);
	pthread_join(data->philos[0].thread_philo, NULL);
	free(data->philos);
	return 0;
}
