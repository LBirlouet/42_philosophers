/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndessard <ndessard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:19:19 by ndessard          #+#    #+#             */
/*   Updated: 2024/04/19 12:39:42 by ndessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_fork(t_data *data, int f, int id)
{
	int	i;

	i = -1;
	if (id == 1)
	{
		pthread_mutex_destroy(&data->m_print);
	}
	else
	{
		while (data->philo && ++i < f)
			pthread_mutex_destroy(&data->fork[i]);
	}
	free(data->fork);
}

void	destroy_all(t_data *data)
{
	destroy_fork(data, data->nb_philo, 1);
	free(data->philo);
}
