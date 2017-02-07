/*
** realloc.c for Malloc
**
** Made by ledins_a
** Login   <aksels.ledins@gmail.com>
**
** Started on  Sun Feb 16 19:22:35 2014 ledins_a
** Last update Sun Feb 16 19:22:37 2014 ledins_a
*/

#include "malloc.h"

t_info g_info;

/*!
   \brief Changed the size of the memory block pointed to by ptr to size bytes.
   \param ptr pointer to the memory zone
   \param size new size of the memory block
   \return pointer to the new memory block
*/
void	*realloc(void *ptr, size_t size)
{
  t_block *info;
  t_block *cur;
  void *new;

  /* if ptr null perform a normal malloc */
  if (!ptr)
    return (malloc(size));
  /* invalid size */
  if (size == 0)
    return (NULL);

  /* get header of the memory block */
  info = (void*)ptr - sizeof(t_block);
  cur = g_info.head;

  /* go to the memory block */
  while (cur && cur->zone != ptr)
    cur = cur->next;
  new = malloc(size);

  /* copy headers */
  if (cur)
  {
      if (size >= info->size)
	     memcpy(new, ptr, cur->size);
      else
	     memcpy(new, ptr, size);
  }

  /* return pointer */
  return (new);
}
