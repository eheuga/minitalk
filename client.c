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

void	send_text(int pid, char *text, int len)
{
	int				i;
	int				j;
	unsigned char	mask;

	i = 0;
	while (i < len + 1)
	{
		j = 0;
		mask = 1 << 7;
		while (j < 8)
		{
			if ((text[i] & mask) == mask)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			while (!g_ack)
				usleep(50);
			g_ack = 0;
			mask = mask >> 1;
			j++;
		}
		i++;
	}
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

	if (ac != 3)
		return (0);
	i = 0;
	pid = atoi(av[1]);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	len = ft_strlen(av[2]);
	text = av[2];
	send_len(pid, len);
	send_text(pid, text, len);

}
