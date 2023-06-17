/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:21:05 by dacortes          #+#    #+#             */
/*   Updated: 2023/06/17 14:17:50 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/philo.h"

#include <stdio.h>

void printProgressBar(int progress, int total) {
    int barWidth = 50;
    float percent = (float)progress / total;
    int filledWidth = percent * barWidth;

    printf("[%2d/%2d] [", progress, total);
    for (int i = 0; i < filledWidth; i++) {
        printf("█");
    }
    for (int i = filledWidth; i < barWidth; i++) {
        printf(" ");
    }
    printf("] (%.2f%%)", percent * 100);
    if (progress == total) {
        printf(" All done");
    }
    printf("\r");
    fflush(stdout);
}

int main() {
    int total = 28;

    for (int i = 1; i <= total; i++) {
        printProgressBar(i, total);
        usleep(100000); // Pequeña pausa para simular trabajo
    }

    printf("\n");

    return 0;
}