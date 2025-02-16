#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h> //para gettimeofday
# include <limits.h>
# include <stdbool.h>  //for true and false
#include <stdint.h> // For SIZE_MAX in calloc

typedef enum e_alloc_type
{
    FORKS,
    PHILOS
}   e_alloc_type;

typedef struct s_philo
{
	pthread_t		id; //needed for pthreadcreate
	int				index;
	long			last_meal;
	int				nb_of_meals;
	int				is_dead;
	long			time2die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_rules
{
	int				philo_nb;
	char			**argv;
	int				argc;
	bool			all_ate;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	meals;
	pthread_mutex_t	time;
	pthread_mutex_t	all_ate_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	int				min_meals;
	t_philo			*philo;
	bool			someone_died;
}					t_rules;

//routine.c
void	*routine(void *arg);

// print_log.c
void	print_log(t_philo *philo, char *msg);

// stop_simulation.c
void	stop_simulation(int philo_nb);

// allocate_resources.c
void	allocate_resources(e_alloc_type resource);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

// error.c
bool	write_error(char *str);

// start_simulation.c
bool	start_simulation(char **argv);
bool	philo_create(void);
bool	mutex_create(void);
bool	threads_create(void);

// get_rules.c //Creo que voy a tener problemas porque es un nombre demasiado largo...probar enter y si no s de struct
t_rules	*get_rules(void);

// parse_arguments.c
bool	parse_fill_rules(char **argv);
int		parse_int(char *str, int arg_index);
bool	fill_struct(void *dest, int src);
int		ft_atoi(const char *str);

// time.c
void	wait_time(long action_time);
long	time_passed(long *start, long *current);
void	get_time_mutex(long *time);
long	get_time_ms(long *time, int returning);
//long	get_time_ms(void);

// death.c
int		check_death_flag(void);
void	print_death(int i);
void	supervisor(void);

// forever_alone.c
bool	forever_alone(t_philo *philo);
int		death_one_philo(t_philo *philo);

// meals.c
bool	check_min_meals(int i);
bool	read_everyone_ate(void);
bool	dead_enough_food(int i);
void	set_everyone_ate(void);

#endif