/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:37:35 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/20 15:30:47 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "headers/manager.h"

void fill(void **ptr, int size) {
	char *str = *ptr;
	int i = 0;
	while (i < size) {
		str[i++] = 'f';
	}
}

void *malloc_fill(size_t size) {
	void *ptr = NULL;
	ptr = malloc(sizeof(char) * size);
	fill(&ptr, size);
	return ptr;
}

void test1() {
	malloc(10);
	malloc(16);
	malloc(1);
	malloc(20);
	malloc_fill(160000);
}

void test2() {
	void *ptr = malloc(3);
	void *ptr2 = realloc(ptr, 33);
}

void test3() {
	int size = 25;
	char *str = (char *)calloc(size, sizeof(char));
	//malloc_fill(15 * sizeof(char));
	int i = 0;
	while (i < size)
		str[i++] = 'a';
	write(1, str, size);
}

void test4() {
	int size = 5;
	char *str = (char *)calloc(size, sizeof(char));
	//malloc_fill(15 * sizeof(char));
	int i = 0;
	while (i < size)
		str[i++] = 'a';
	i = 0;
	while (str[i]) {
		write(1, ".", 1);
		i++;
	}
}

void test5() {
	void *ptr = malloc(10);
	malloc(10);
}

void main() {
	test5();
	show_alloc_mem();
}
