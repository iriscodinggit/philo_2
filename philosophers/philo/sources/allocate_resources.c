#include "../header/philosophers.h"

/*void	allocate_forks(void)
{
	pthread_mutex_t	*forks;

	forks = ft_calloc(sizeof(pthread_mutex_t), r()->philo_nb);
	if (!forks)
		return ;
	r()->forks = forks;
}
void	allocate_philosophers(void)
{
	t_philo	*philosophers;

	philosophers = ft_calloc(sizeof(t_philo), r()->philo_nb);
	if (!philosophers)
		return ;
	r()->philo = philosophers;
}
*/

//quizá haya problemas con norminette por no declarar forks en caso de philos y viceversa, en cuyo caso, añadir forks igual a NULL despues del if y lo mismo con philosophers

void allocate_resources(e_alloc_type resource)
{
	pthread_mutex_t *forks;
    t_philo *philosophers;

    if (resource == FORKS)
    {
        forks = ft_calloc(sizeof(pthread_mutex_t), get_rules()->philo_nb);
        if (!forks)
            return;
        get_rules()->forks = forks;
    }
    else if (resource== PHILOS)
    {
        philosophers = ft_calloc(sizeof(t_philo), get_rules()->philo_nb);
        if (!philosophers)
            return;
        get_rules()->philo = philosophers;
    }
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	ptr = NULL;
	total_size = count * size;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	if (count == 0 || size == 0)
		return (malloc(0));
	if (count != 0 && total_size / count != size)
		return (NULL);
	ptr = malloc (total_size);
	if (!ptr)
		return (NULL);
	if (ptr != NULL)
	{
		ft_bzero(ptr, size * count);
		return (ptr);
	}
	return (NULL);
}
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
	((char *)b)[i] = c;
		i++;
	}
	return (b);
} 