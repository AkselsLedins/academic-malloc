/*
** builtins.c for Malloc
**
** Made by ledins_a
** Login   <aksels.ledins@gmail.com>
**
** Started on  Sun Feb 16 19:21:57 2014 ledins_a
** Last update Sun Feb 16 19:21:59 2014 ledins_a
*/

#include "malloc.h"

t_info g_info;

void show_alloc_mem(void)
{
  t_block* cur = g_info.head;
  printf("break : %p\n", sbrk(0));
  while (cur != NULL)
    {
      if (cur->state != FREE)
	printf("%p - %p : %zd\n", cur->zone, cur->zone + cur->size, cur->size);
      cur = cur->next;
    }
}

void		*get_zone_build_node(t_block *cur, t_block **nextNode, size_t size) {
  size_t	oldSize;

  oldSize = cur->size;
  *nextNode = cur->next;
  cur->state = ALLOCATED;
  cur->size = size;
  cur->zone = (void*)cur + sizeof(t_block);
  cur->next = (void*)cur + sizeof(t_block) + size;
  cur->next->state = FREE;
  cur->next->size = oldSize - size - sizeof(t_block);
  cur->next->next = *nextNode;
  cur->next->zone = (void*)cur->next + sizeof(t_block);
  return (cur->zone);
}

void		*get_zone(size_t size) {
  t_block		*cur;
  t_block 	*nextNode;

  nextNode = NULL;
  cur = g_info.head;
  while (cur)
    {
      if (cur->state == FREE && cur->size > (size + sizeof(t_block)))
    	{
    	  return (get_zone_build_node(cur, &nextNode, size));
    	}
      cur = cur->next;
    }
  return (NULL);
}

void get_free_space(t_block **cur, size_t *freeSpace) {
  if ((*cur)->state == FREE)
    {
      *freeSpace += sizeof(t_block) + (*cur)->size;
      if (!(*cur)->next)
	*freeSpace += (size_t)sbrk(0) - (size_t)(*cur) -
	sizeof(t_block) - (*cur)->size;
    }
  else
    *cur = NULL;
  if (*cur)
    *cur = (*cur)->next;
}
