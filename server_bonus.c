/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:33:03 by brbaazi           #+#    #+#             */
/*   Updated: 2025/03/26 15:19:32 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putnbr(int nb)
{
	char	c;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	c = nb % 10 + 48;
	write(1, &c, 1);
}

static void	sign_handler(int s, siginfo_t *infos, void *context)
{
	static unsigned char	c = 0;
	static int				bit_position = 7;
	static pid_t			pid;
	int						k;

	(void)context;
	if (pid != infos->si_pid)
	{
		pid = infos->si_pid;
		c = 0;
		bit_position = 7;
	}
	if (s == SIGUSR1)
		c |= (1 << bit_position);
	bit_position--;
	if (bit_position < 0)
	{
		write(1, &c, 1);
		bit_position = 7;
		c = 0;
	}
	k = kill(pid, SIGUSR1);
	if (k == -1)
		write(1, "errorserver!!", 13);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	sa.sa_sigaction = sign_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
