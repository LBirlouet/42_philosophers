/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/12 15:56:12 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

int	main(int ac, char **av)
{
	t_data	data;

	if (verif_data(ac,av)|| init_data(&data, ac, av))
		return (printf(error_0), 1);
	if (data.nb_philo == 1)
		return (printf("cas 1 seul philo !"));
	
	printf("good data\n");
	return (0);
}