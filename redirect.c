/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:30:10 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/11 12:48:16 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int in;
	int out;
	char *buff;
	int i;


	int new0 = dup(0);
	int new2 = dup(1);

	close(0);
	close(1);

	int new_file = open("abc.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);

	write(STDOUT_FILENO,"hello", 5);
	write(STDIN_FILENO,"hello", 5);

	i = 1;
	buff = malloc(10);
	while(argv[i] != NULL)
	{
		in = open(argv[i], O_RDONLY);
		dup2(in, STDIN_FILENO);
		read(in, buff, 6);
		out = open(argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		dup2(out, STDOUT_FILENO);
		write(STDOUT_FILENO, buff, 5);
		i += 2;
		close(in);
		close(out);
	}

	return 0;
}
