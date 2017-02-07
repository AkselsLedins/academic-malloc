/*
** calloc.c for Malloc
**
** Made by ledins_a
** Login   <aksels.ledins@gmail.com>
**
** Started on  Sun Feb 16 19:22:06 2014 ledins_a
** Last update Sun Feb 16 19:22:08 2014 ledins_a
*/

#include <pthread.h>
#include "malloc.h"

t_info g_info = {NULL, 0};
pthread_mutex_t mutexMalloc = PTHREAD_MUTEX_INITIALIZER;

/*!
   \brief Allocates memory for an array of n elements of size bytes each.
   \param n number of elements of the array
   \param size size of a single element
   \return Either NULL or a pointer to the allocated memory.
*/
void	*calloc(size_t n, size_t size) {
  /* pointer to the memory block */
  char	*ptr;

  /* memory allocation */
  if (!(ptr = malloc(n * size)))
    return (NULL);
  else /* if allocation succeded set memory bytes to */
    memset(ptr, 0, n * size - 1);

  /* return pointer to the memory block */
  return (ptr);
}
