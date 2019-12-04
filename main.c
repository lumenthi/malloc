/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:37:35 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/04 19:14:52 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void show_alloc_mem() {
}

void main1() {
	char *str;

	str = (char *)malloc(sizeof(char) * 12);
	write(1, "___main_segfault___\n", 20);
	strcpy(str, "0123456789\n");
	write(1, str, 11);
	free(str);
}

void test2() {
	void *ptr = malloc(2);
	malloc(2);
	free(ptr);
}

void test3() {
	void *ptr = malloc(1);
	void *ptr2 = malloc(1);
	free(ptr);
	free(ptr2);
}

void main() {
	test2();
}
