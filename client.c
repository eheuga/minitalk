/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:48:56 by emheuga           #+#    #+#             */
/*   Updated: 2026/04/03 12:50:09 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int	g_ack = 0;



void	handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	g_ack = 1;
}

void	send_len(int pid, int len)
{
	unsigned int	mask;

	mask = 1 << 31;
	while (mask)
	{
		if ((len & mask) == mask)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		mask = mask >> 1;
		while (!g_ack)
			usleep(50);
		g_ack = 0;
	}
}

int	send_text(int pid, char *text, int len)
{
	static int			i;
	static int			j;
	static unsigned int	mask;

	i = 0;
	j = 0;
	mask = 1 << 7;
	if (i < len + 1)
	{
		if (j < 8)
		{
			if ((text[i] & mask) == mask)
			{
				kill(pid, SIGUSR1);
				while (!g_ack)
					usleep(50);
				g_ack = 0;
			}
			else
			{
				kill(pid, SIGUSR2);
				while (!g_ack)
					usleep(50);
				g_ack = 0;
			}
			mask = mask >> 1;
			j++;
			return (1);
		}
		if (j == 8)
		{
			i++;
			mask = 1 << 7;
			j = 0;
			return (1);
		}
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	char				*text;
	int					len;
	int					i;
	int					pid;

	i = 0;
	pid = atoi(av[1]);
	if (ac != 3)
		return (0);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	len = ft_strlen(av[2]);
	text = av[2];
	send_len(pid, len);
	while (send_text(pid, text, len))
		i++;
}
