/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/11 15:59:14 by lbirloue         ###   ########.fr       */
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
				return (-1);
		i++;
	}

	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	
	if (verif_data(ac,av) == -1)
		return 1;
	printf("good data\n");
	return (0);
}