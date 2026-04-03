/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:49:51 by emheuga           #+#    #+#             */
/*   Updated: 2026/04/03 12:50:09 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	get_len(int signum, unsigned int *len, int *bit)
{
	if (signum == SIGUSR1)
	{
		*len = *len << 1;
		(*len)++;
		(*bit)++;
	}
	else if (signum == SIGUSR2)
	{
		*len = *len << 1;
		(*bit)++;
	}
}

int	get_text(int signum, char *text)
{
	static int	i;
	static int	bit;
	static char	c;

	i = 0;
	bit = 0;
	c = 0;
	if (bit < 8)
	{
		if (signum == SIGUSR1)
		{
			c = c << 1;
			c++;
			bit++;
		}
		else if (signum == SIGUSR2)
		{
			c = c << 1;
			bit++;
		}
	}
	if (bit == 8)
	{
		if (c == 0)
		{
			write(1, text, i);
			write(1, "\n", 1);
			i = 0;
			bit = 0;
			c = 0;
			return (1);
		}
		text[i] = c;
		i++;
		bit = 0;
		c = 0;
	}
	return (0);
}

void	handler(int signum, siginfo_t *info, void *context)
{
	static unsigned int	len;
	static int			bit;
	static char			*text;
	int					client_pid;

	len = 0;
	bit = 0;
	client_pid = info->si_pid;
	(void)context;
	if (info->si_pid == getpid())
		return ;
	if (bit < 32)
	{
		get_len(signum, &len, &bit);
		if (bit == 32)
		{
			text = malloc(len + 1);
			if (!text)
				return ;
		}
	}
	else
	{
		if (get_text(signum, text) == 1)
		{
			free(text);
			text = NULL;
			len = 0;
			bit = 0;
		}
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("PID : %d\n", pid);
	while (1)
	{
		pause();
	}
}
