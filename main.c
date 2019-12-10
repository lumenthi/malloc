/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:37:35 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/10 14:00:15 by lumenthi         ###   ########.fr       */
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
	void *ptr = malloc(74);
	free(ptr);
}

void test4() {
	free(malloc_fill(28));
	malloc_fill(5);
	malloc_fill(120);
	malloc_fill(12);
	malloc_fill(776);
	malloc_fill(112);
	malloc_fill(1336);
	malloc_fill(216);
	malloc_fill(432);
	malloc_fill(104);
	malloc_fill(88);
	malloc_fill(120);
	malloc_fill(168);
	malloc_fill(104);
	malloc_fill(80);
	malloc_fill(192);
	free(malloc_fill(12));
	malloc_fill(171);
	malloc_fill(12);
	malloc_fill(181);
	malloc_fill(12);
	malloc_fill(191);
	malloc_fill(6);
	free(malloc_fill(4));
	malloc_fill(112);
	malloc_fill(120);
	malloc_fill(24);
	malloc_fill(18);
	malloc_fill(32);
	malloc_fill(24);
}

void test5() {
	int i = 0;
	int size = 10;
	char *ptr = malloc_fill(size);
	while (i < size) {
		write(1, &ptr[i], 1);
		i++;
	}
}

void test6() {
	int size = 20;
	void *ptr = malloc_fill(20);
	void *new_ptr = realloc(ptr, 20);
}

void test7() {
	free(malloc_fill(5));
	malloc_fill(120);
	malloc_fill(12);
	malloc_fill(776);
	malloc_fill(112);
	malloc_fill(1336);
	malloc_fill(216);
	malloc_fill(432);
	malloc_fill(104);
	malloc_fill(88);
	malloc_fill(120);
	malloc_fill(168);
	malloc_fill(104);
	malloc_fill(80);
	malloc_fill(192);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(5);
	malloc_fill(120);
	malloc_fill(12);
	malloc_fill(776);
	malloc_fill(112);
	malloc_fill(1336);
	malloc_fill(216);
	malloc_fill(432);
	malloc_fill(104);
	malloc_fill(88);
	malloc_fill(120);
	malloc_fill(168);
	malloc_fill(104);
	malloc_fill(80);
	malloc_fill(192);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(12);
	malloc_fill(281);
	malloc_fill(281);
	malloc_fill(29);
	malloc_fill(5);
	malloc_fill(5);
	malloc_fill(1264);
}

void test8() {
	void *ptr = malloc_fill(10);
	free(ptr);
}

void test9() {
void *ptr1 = malloc(120);
void *ptr2 = malloc(1024);
free(ptr1);
free(ptr2);
malloc(12);
write(1, "SLAYING LINE\n", 13);
malloc(776);
// malloc(112);
// malloc(1336);
// malloc(216);
// malloc(432);
}

void test10() {
	void *ptr1 = malloc_fill(10);
	void *ptr2 = malloc_fill(2);
	void *ptr3 = malloc_fill(869);
	// free(ptr2);
	void *ptr4 = malloc_fill(1);
	malloc(5);
	void *ptr = realloc(ptr2, 10);
	// free(ptr4);
}

void test11() {
	void *ptr1 = malloc(200);
	ptr1 = realloc(ptr1, 100);
	fill(&ptr1, 100);
	free(ptr1);
}

void test12() {
	void *ptr = malloc(10);
	void *ptr2 = malloc(10);
	free(ptr);
	free(ptr2);
}

void main() {
	test12();
}
