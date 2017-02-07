/*
** free.c for Malloc
**
** Made by ledins_a
** Login   <aksels.ledins@gmail.com>
**
** Started on  Sun Feb 16 19:22:17 2014 ledins_a
** Last update Sun Feb 16 19:22:19 2014 ledins_a
*/

#include <pthread.h>
#include "malloc.h"

t_info g_info;
pthread_mutex_t mutexMalloc;

static int get_free_space_lp()
{
  size_t freeSpace;
  t_block *cur;

  freeSpace = 0;
  cur = g_info.head;
  while (cur)
    {
      if ((size_t)cur >= (size_t)sbrk(0) - getpagesize())
	{
	  while (cur)
	    get_free_space(&cur, &freeSpace);
	  cur = NULL;
	}
      if (cur)
	cur = cur->next;
    }
  return (freeSpace);
}

static void free_zone(void *ptr)
{
  t_block *tmp;
  t_block *prev;

  prev = NULL;
  tmp = g_info.head;
  while (tmp && tmp->zone != ptr)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  if (tmp)
    tmp->state = FREE;
  if ( tmp && tmp->next && tmp->next->state == FREE )
    {
      tmp->size = tmp->next->size + sizeof(t_block);
      tmp->next = tmp->next->next;
    }
  if ( tmp && prev && prev->state == FREE )
    {
      prev->size = tmp->size + sizeof(t_block);
      prev->next = tmp->next;
    }
}

static void free_page()
{
  if (get_free_space_lp() == getpagesize())
    {
      sbrk(-getpagesize());
    }
}

static void free_last_block()
{
  t_block *tmp;

  tmp = g_info.head;
  if ((size_t)tmp >= (size_t)sbrk(0))
    {
      g_info.head = NULL;
      return;
    }
  while (tmp && tmp->next)
    {
      if ((size_t)tmp->next >= (size_t)sbrk(0))
	tmp->next = NULL;
      tmp = tmp->next;
    }
}

void free(void *ptr)
{
  if (!ptr)
    return;
  pthread_mutex_lock(&mutexMalloc);
  free_zone(ptr);
  free_page();
  free_last_block();
  pthread_mutex_unlock(&mutexMalloc);
}
