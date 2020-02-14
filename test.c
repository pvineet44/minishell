/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 20:53:05 by                   #+#    #+#             */
/*   Updated: 2020/02/14 20:53:06 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    int stdin_copy = dup(0);
    int stdout_copy = dup(1);
    close(0);
    close(1);
    int file = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    int file1 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    write(STDOUT_FILENO, "file1", 5);
    write(STDIN_FILENO, "file2", 5);
    close(file);
    close(file1);
    dup2(stdin_copy, 0);
    dup2(stdout_copy, 1);
    close(stdin_copy);
    close(stdout_copy);
    write(STDOUT_FILENO, "file2", 5);
    write(STDIN_FILENO, "file2", 5);
}