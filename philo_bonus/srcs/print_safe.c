/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:00:05 by agruet            #+#    #+#             */
/*   Updated: 2025/04/17 16:00:17 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	itoa_custom(long num, char *str)
{
	int		i;
	long	n;
	long	div;

	i = 0;
	if (num == 0)
		str[i++] = '0';
	else
	{
		n = num;
		if (num < 0)
		{
			str[i++] = '-';
			n = -num;
		}
		div = 1;
		while (n / div >= 10)
			div *= 10;
		while (div > 0)
		{
			str[i++] = (n / div) + '0';
			n %= div;
			div /= 10;
		}
	}
}

void	print_safe(long timestamp, long id, char *message)
{
	char	buffer[100];
	char	time_str[20];
	char	id_str[20];
	int		i;
	int		j;

	memset(time_str, 0, 20);
	memset(id_str, 0, 20);
	itoa_custom(timestamp, time_str);
	itoa_custom(id + 1, id_str);
	i = 0;
	j = 0;
	while (time_str[j])
		buffer[i++] = time_str[j++];
	buffer[i++] = ' ';
	j = 0;
	while (id_str[j])
		buffer[i++] = id_str[j++];
	buffer[i++] = ' ';
	j = 0;
	while (message[j])
		buffer[i++] = message[j++];
	buffer[i++] = '\n';
	buffer[i] = '\0';
	write(STDOUT_FILENO, buffer, i);
}
