/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:41:24 by romanbtt          #+#    #+#             */
/*   Updated: 2021/06/25 12:07:21 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

# define ERR_MALLOC "Malloc failed to allocate memory."
# define ERR_NEG "At least one argument is negative."
# define ERR_MAX_INT "At least one argument is superior at max int."
# define ERR_DIGIT "At least one argument is not a digit."
# define ERR_NB_ARGS "Wrong number of arguments."
# define ERR_PHILO_200 "You should not test with more than 200 philosophers."
# define ERR_PHILO_1 "You should not test with less than 1 philosopher."
# define ERR_ARG_DIE "You should not set time_to_die less than 60 ms."
# define ERR_ARG_EAT "You should not set time_to_eat less than 60 ms."
# define ERR_ARG_SLEEP "You should not set time_to_sleep less than 60 ms."
# define ERR_PTHREAD_CREATE "Pthread_create failed to create a thread."
# define ERR_PTHREAD_DETACH "Pthread_detach failed to detach a thread."
# define ERR_PTHREAD_JOIN "Pthread_join failed to join a thread."

typedef pthread_mutex_t	t_mutex;

typedef struct s_simul
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_time_each_philosophers_must_eat;
	t_mutex	*forks;
	t_mutex	lock_print;
	t_mutex	simulation_running;
	time_t	start_simulation;
	bool	someone_die;
}				t_simul;

typedef struct s_philo
{
	int		numero;
	int		right_fork;
	int		left_fork;
	int		eat_count;
	time_t	time_last_meal;
	time_t	time_out;
	t_simul	*setting;
	t_mutex	is_eating;
	bool	break_routine;
}				t_philo;

int		ft_isspace(const char c);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
size_t	ft_strlen(const char *str);
bool	error(char *str);
int		ft_isdigit(int c);
char	*ft_ltoa(long nb);
char	**ft_split_isspace(char const *s);
void	ft_free_array_string(char **arr);

bool	get_arguments(int argc, char **argv, int *args_philo);

bool	check_arguments(char **argv, int argc);
bool	check_number_arguments(char **argv);
bool	check_digits(char *argv[]);

time_t	get_time(void);

bool	initialization(t_philo **philos, t_simul *simulation, int *args_philo);

bool	start_simulation(t_philo *philos, t_simul *simulation);

void	*routines(void *parameter);

void	take_fork(t_philo *philosopher, int index_fork);
void	put_fork_down(t_philo *philosopher, int index_fork);

void	print_action(t_philo *philosopher, char *msg);

void	*monitor(void *parameter);

void	free_before_exit(t_philo *philo, t_simul *simulation);

#endif