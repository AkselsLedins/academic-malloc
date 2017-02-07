/*
** malloc.h for Malloc
**
** Made by ledins_a
** Login   <aksels.ledins@gmail.com>
**
** Started on  Sun Feb 16 19:23:57 2014 ledins_a
** Last update Sun Feb 16 19:24:01 2014 ledins_a
*/

#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* state of the memory block */
typedef enum e_state {
	FREE,
	ALLOCATED
}t_state;

typedef struct s_block {
	struct s_block* next;
	size_t size;
	t_state state;
	void *zone;
}t_block;

typedef struct s_info {
	t_block *head;
	unsigned int nbPage;
}t_info;

extern t_info g_info;
extern pthread_mutex_t mutexMalloc;

void	*calloc(size_t n, size_t size);
void	*realloc(void *ptr, size_t size);
void 	show_alloc_mem(void);
void	*get_zone_build_node(t_block *cur, t_block **nextNode, size_t size);
void	*get_zone(size_t size);
void 	get_free_space(t_block **cur, size_t *freeSpace);
void 	free(void *ptr);
void	*malloc(size_t size);


#endif // MALLOC_H
