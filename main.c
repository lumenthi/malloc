/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:37:35 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/12 12:34:22 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	void *ptr = malloc(10);
	void *ptr2 = realloc(ptr, 20);
}

void main() {
	test2();
}
