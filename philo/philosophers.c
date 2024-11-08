#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct s_table
{
    int             num_of_philos;
    int             num_of_meals;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    bool            simulation_running;
    struct timeval  start_time;
    pid_t           *processes;
} t_table;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long long       last_meal_time;
    int             *left_fork;
    int             *right_fork;
    t_table         *table;
} t_philo;

// Time utility functions
long long get_current_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long get_elapsed_time(struct timeval start)
{
    return (get_current_time() - ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
}

void precise_sleep(int ms)
{
    long long start = get_current_time();
    while (get_current_time() - start < ms)
        usleep(100);
}

// Status printing
void print_status(t_philo *philo, const char *status)
{
    if (philo->table->simulation_running)
        printf("%lld %d %s\n", get_elapsed_time(philo->table->start_time), 
               philo->id, status);
}

// Fork management using file descriptors
void grab_forks(t_philo *philo)
{
    *philo->left_fork = philo->id;
    print_status(philo, "has taken a fork");
    *philo->right_fork = philo->id;
    print_status(philo, "has taken a fork");
}

void release_forks(t_philo *philo)
{
    *philo->left_fork = 0;
    *philo->right_fork = 0;
}

// Philosopher actions
void handle_eat(t_philo *philo)
{
    philo->last_meal_time = get_elapsed_time(philo->table->start_time);
    print_status(philo, "is eating");
    philo->meals_eaten++;
    precise_sleep(philo->table->time_to_eat);
}

void handle_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
    precise_sleep(philo->table->time_to_sleep);
}

void handle_think(t_philo *philo)
{
    print_status(philo, "is thinking");
}

// Main philosopher routine
void philosopher_routine(t_philo *philo)
{
    if (philo->id % 2 == 0)
        precise_sleep(philo->table->time_to_eat / 2);

    while (philo->table->simulation_running)
    {
        if (get_elapsed_time(philo->table->start_time) - philo->last_meal_time 
            > philo->table->time_to_die)
        {
            print_status(philo, "died");
            philo->table->simulation_running = false;
            return;
        }

        grab_forks(philo);
        handle_eat(philo);
        release_forks(philo);
        
        if (philo->table->num_of_meals && 
            philo->meals_eaten >= philo->table->num_of_meals)
            return;

        handle_sleep(philo);
        handle_think(philo);
    }
}

// Initialization functions
t_table *init_table(int argc, char **argv)
{
    t_table *table = malloc(sizeof(t_table));
    if (!table)
        return NULL;

    table->num_of_philos = atoi(argv[1]);
    table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->num_of_meals = (argc == 6) ? atoi(argv[5]) : 0;
    table->simulation_running = true;
    gettimeofday(&table->start_time, NULL);

    if (table->num_of_philos < 1 || table->num_of_philos > 200)
    {
        free(table);
        return NULL;
    }

    return table;
}

t_philo *init_philosophers(t_table *table, int *forks)
{
    t_philo *philos = malloc(sizeof(t_philo) * table->num_of_philos);
    if (!philos)
        return NULL;

    int i = 0;
    while (i < table->num_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].last_meal_time = 0;
        philos[i].table = table;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % table->num_of_philos];
        i++;
    }

    return philos;
}

// Main function
int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return 1;
    }

    t_table *table = init_table(argc, argv);
    if (!table)
        return 1;

    int *forks = calloc(table->num_of_philos, sizeof(int));
    if (!forks)
    {
        free(table);
        return 1;
    }

    t_philo *philos = init_philosophers(table, forks);
    if (!philos)
    {
        free(table);
        free(forks);
        return 1;
    }

    table->processes = malloc(sizeof(pid_t) * table->num_of_philos);
    if (!table->processes)
    {
        free(table);
        free(forks);
        free(philos);
        return 1;
    }

    int i = 0;
    while (i < table->num_of_philos)
    {
        table->processes[i] = fork();
        if (table->processes[i] == 0)
        {
            philosopher_routine(&philos[i]);
            exit(0);
        }
        i++;
    }

    // Wait for any philosopher to die or finish meals
    i = 0;
    while (i < table->num_of_philos)
    {
        int status;
        waitpid(table->processes[i], &status, 0);
        if (WIFEXITED(status))
        {
            table->simulation_running = false;
            break;
        }
        i++;
    }

    // Cleanup
    i = 0;
    while (i < table->num_of_philos)
    {
        if (table->processes[i] > 0)
            kill(table->processes[i], SIGTERM);
        i++;
    }

    free(table->processes);
    free(table);
    free(forks);
    free(philos);

    return 0;
}