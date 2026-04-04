/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emheuga <emheuga@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:49:51 by emheuga           #+#    #+#             */
/*   Updated: 2026/04/04 14:14:06 by emheuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf/ft_printf.h"

void	get_len(int signum, unsigned int *len, int *bit)
{
	*len = *len << 1;
	if (signum == SIGUSR1)
		(*len)++;
	(*bit)++;
}

int	get_text(int signum, char *text)
{
	static int	i;
	static int	bit;
	static char	c;

	c = c << 1;
	if (signum == SIGUSR1)
		c++;
	bit++;
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

void	free_all(char **text, unsigned int *len, int *bit)
{
	free(*text);
	*text = NULL;
	*len = 0;
	*bit = 0;
}

void	handler(int signum, siginfo_t *info, void *context)
{
	static unsigned int	len;
	static int			bit;
	static char			*text;

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
	else if (get_text(signum, text) == 1)
		free_all(&text, &len, &bit);
	kill(info->si_pid, SIGUSR1);
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
	ft_printf("PID : %d\n", pid);
	while (1)
	{
		pause();
	}
}
