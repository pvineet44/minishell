/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:17:47 by                   #+#    #+#             */
/*   Updated: 2020/02/25 15:52:57 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	pid_t pid;
	int mypipe[2];
	char buff[10];
	if (pipe(mypipe))
	{
		write(1, "Failed/n", 7);
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == (pid_t) 0)
	{
		close(mypipe[1]);
		read(mypipe[0], buff, 5);
	}
	else
	{
		close(mypipe[0]);
		write(mypipe[1], "ruler", 5);
		return (EXIT_SUCCESS);
	}
	write(1, buff, 5);
	return 0;
}
