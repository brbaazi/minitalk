/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:34:45 by brbaazi           #+#    #+#             */
/*   Updated: 2025/03/26 14:25:08 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_ack_received;

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_atoi(char *str)
{
	int	r;
	int	s;
	int	i;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	if (r > 4194304)
		return (-1);
	return (r * s);
}

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

void	send_sig(int msg, int pid)
{
	int	i;
	int	bit;
	int	k;

	i = 7;
	while (i >= 0)
	{
		g_ack_received = 0;
		bit = ((msg >> i) & 1);
		if (bit == 1)
			k = kill(pid, SIGUSR1);
		else
			k = kill(pid, SIGUSR2);
		if (k == -1)
			write(1, "errorclient", 11);
		while (!g_ack_received)
			;
		i--;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client PID MESSAGE\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr("invalid pid\n");
		return (1);
	}
	signal(SIGUSR1, ack_handler);
	i = 0;
	while (argv[2][i])
	{
		send_sig(argv[2][i], pid);
		i++;
	}
	return (0);
}
