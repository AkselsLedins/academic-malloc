/*
** malloc.c for Malloc
**
** Made by ledins_a
** Login   <aksels.ledins@gmail.com>
**
** Started on  Sun Feb 16 19:22:26 2014 ledins_a
** Last update Sun Feb 16 19:22:28 2014 ledins_a
*/

#include <pthread.h>
#include "malloc.h"

t_info g_info;
pthread_mutex_t mutexMalloc;

static void 	*insert_into_page(t_block **new_node,
	t_block *cur, size_t size)
{
  *new_node = (void*)((size_t)cur + cur->size + sizeof(t_block));
  (*new_node)->size = size;
  (*new_node)->state = ALLOCATED;
  (*new_node)->next = NULL;
  cur->next = *new_node;
  (*new_node)->zone = (void*)(*new_node) + sizeof(t_block);
  return ((*new_node)->zone);
}

static void *allocate_new_page(t_block **new_node,
	t_block *cur, size_t size, int nb)
{
  void 	*before;

  before = sbrk(0);
  *new_node = sbrk(getpagesize() * (nb));
  if (before == sbrk(0))
    return (NULL);
  (*new_node)->size = size;
  (*new_node)->state = ALLOCATED;
  (*new_node)->next = NULL;
  cur->next = *new_node;
  (*new_node)->zone = (void*)(*new_node) + sizeof(t_block);
  return ((*new_node)->zone);
}

static void 	*first_allocation(int nb, size_t size)
{
  void* before;

  before = sbrk(0);
  g_info.head = sbrk(getpagesize() * (nb));
  if (before ==  sbrk(0))
    return (NULL);
  g_info.head->next = NULL;
  g_info.head->state = ALLOCATED;
  g_info.head->size = size;
  g_info.head->zone = (void*)(g_info.head) + sizeof(t_block);
  return (g_info.head->zone);
}

static void* add_zone(size_t size)
{
  t_block		*cur;
  int 		nb_page_to_allocate;
  t_block		*new_node;

  nb_page_to_allocate = (((int)size + sizeof(t_block)) / getpagesize()) + 1;
  cur = g_info.head;
  while (cur && cur->next)
    cur = cur->next;
  if (cur)
    {
      if (((size_t)cur->zone + cur->size + sizeof(t_block) * 1 + size)  <
	(size_t)sbrk(0))
	return (insert_into_page(&new_node, cur, size));
      else
	return allocate_new_page(&new_node, cur, size, nb_page_to_allocate);
    }
  else
    return first_allocation(nb_page_to_allocate, size);
}

void *malloc(size_t size)
{
  void	 *addr;

  addr = NULL;
  if (size <= 0)
    return (NULL);
  pthread_mutex_lock(&mutexMalloc);
  addr = get_zone(size);
  if (addr)
    {
      pthread_mutex_unlock(&mutexMalloc);
      return (addr);
    }
  addr = add_zone(size);
  pthread_mutex_unlock(&mutexMalloc);
  return addr;
}
