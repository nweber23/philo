# philosophers
A multithreading simulation of the classic dining philosophers problem, developed as part of the 42 School curriculum.

## Overview
This project implements a solution to the famous dining philosophers problem using threads and mutexes. It demonstrates concurrent programming concepts including thread synchronization, deadlock prevention, and race condition handling. The simulation shows philosophers alternating between thinking, eating, and sleeping while sharing limited resources (forks).

## Features
### Core Functionality
- Simulates N philosophers sitting around a circular table
- Each philosopher alternates between eating, sleeping, and thinking
- Philosophers share forks (resources) with their neighbors
- Prevents deadlock through careful resource ordering
- Real-time monitoring of philosopher states and deaths

### Threading & Synchronization
- **Multithreading**: Each philosopher runs in a separate thread
- **Mutex Protection**: Fork access and shared data protected by mutexes
- **Deadlock Prevention**: Asymmetric fork acquisition order for odd/even philosophers
- **Race Condition Prevention**: Thread-safe printing and data access
- **Monitor Thread**: Dedicated thread for death detection and meal counting

### Timing & Performance
- Precise microsecond-level timing using `gettimeofday()`
- Custom sleep function with busy-wait for accuracy
- Optimized philosopher scheduling to prevent starvation
- Configurable simulation parameters

## Project Structure
```
philo/
├── Makefile                     # Build configuration with ASCII art
├── philo.h                      # Main header file
├── main.c                       # Entry point and argument parsing
├── init.c                       # Data structure initialization
├── simulation.c                 # Thread creation and monitoring
├── actions.c                    # Philosopher behavior implementation
├── utils.c                      # Utility functions and timing
└── cleanup.c                    # Memory and resource cleanup
```

## Compilation
### Prerequisites
- GCC or compatible C compiler with pthread support
- Make build system
- UNIX-like system (Linux/macOS)

### Build Commands
```bash
# Compile the program
make

# Clean object files
make clean

# Full cleanup
make fclean

# Rebuild everything
make re
```

## Usage
### Basic Usage
```bash
# Basic simulation
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep

# With meal limit
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]

# Example: 5 philosophers, die in 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Example: Stop after each philosopher eats 3 times
./philo 4 310 200 100 3
```

### Parameters
- **number_of_philosophers**: Number of philosophers (and forks)
- **time_to_die**: Maximum time (ms) between meals before death
- **time_to_eat**: Time (ms) each philosopher spends eating
- **time_to_sleep**: Time (ms) each philosopher spends sleeping
- **number_of_meals** (optional): Simulation stops when all philosophers have eaten this many times

## Simulation Behavior
### Philosopher States
```bash
# Example output
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
400 2 has taken a fork
400 2 has taken a fork
400 2 is eating
600 2 is sleeping
```

### State Messages
- **"has taken a fork"**: Philosopher acquired a fork
- **"is eating"**: Philosopher is consuming food
- **"is sleeping"**: Philosopher is resting
- **"is thinking"**: Philosopher is contemplating
- **"died"**: Philosopher starved (exceeded time_to_die)

## Implementation Details
### Thread Management
- **Main Thread**: Argument parsing, initialization, cleanup
- **Philosopher Threads**: Individual philosopher behavior loops  
- **Monitor Thread**: Continuous death checking and meal counting
- **Thread Synchronization**: Proper joining and cleanup on exit

### Deadlock Prevention
- **Asymmetric Ordering**: Even philosophers take left fork first, odd take right first
- **Resource Hierarchy**: Consistent ordering prevents circular wait conditions
- **Timeout Prevention**: Monitor thread ensures no philosopher waits indefinitely

### Race Condition Prevention
```c
// Thread-safe printing
pthread_mutex_lock(&data->print_mutex);
printf("%ld %d %s\n", timestamp, philosopher_id, action);
pthread_mutex_unlock(&data->print_mutex);

// Protected data access
pthread_mutex_lock(&data->data_mutex);
philosopher->time_since_meal = get_time();
pthread_mutex_unlock(&data->data_mutex);
```

## Advanced Features
### Precise Timing
- Custom `ft_usleep()` function using busy-wait for microsecond precision
- Timestamp calculation relative to simulation start time
- Consistent timing across different system loads

### Edge Case Handling
- **Single Philosopher**: Special case handling (inevitable death)
- **Zero Values**: Input validation for all parameters
- **Resource Cleanup**: Proper mutex destruction and memory deallocation
- **Thread Termination**: Graceful shutdown of all threads

### Performance Optimizations
- **Staggered Start**: Philosophers start at slightly different times to reduce contention
- **Thinking Time**: Dynamic thinking duration to balance the simulation
- **Monitor Frequency**: Optimized checking interval for death detection

## Testing Examples
```bash
# Should not die (sufficient time)
./philo 5 800 200 200

# Should die quickly (insufficient time)  
./philo 5 200 300 100

# Single philosopher (always dies)
./philo 1 800 200 200

# Large number of philosophers
./philo 100 800 200 200

# Meal limit test
./philo 4 410 200 200 5
```

## Error Handling
```bash
# Invalid argument count
./philo 5 800 200
# Output: Usage: ./philo Numbers_of_Philos time_to_die time_to_eat time_to_sleep [numbers_of_meals]

# Negative values
./philo -5 800 200 200
# Output: Error

# Non-numeric input
./philo five 800 200 200  
# Output: Error

# Zero philosophers
./philo 0 800 200 200
# Output: Error
```

## Technical Specifications
### Threading Details
- **Thread Model**: One thread per philosopher plus monitor thread
- **Synchronization**: Mutex-based locking for forks and shared data
- **Thread Safety**: All shared resources protected by appropriate mutexes
- **Deadlock Freedom**: Guaranteed by asymmetric resource ordering

### Memory Management
- **Dynamic Allocation**: Philosophers and forks allocated based on input
- **Resource Cleanup**: All mutexes destroyed and memory freed on exit
- **Leak Prevention**: Proper cleanup even on error conditions

### Performance Characteristics
- **Scalability**: Handles 1-200 philosophers efficiently
- **Timing Accuracy**: Microsecond-level precision for state transitions
- **CPU Usage**: Optimized busy-wait loops for precise timing
- **Memory Usage**: O(n) space complexity for n philosophers

## Common Issues & Solutions
### No Death Occurs
- Increase `time_to_die` parameter
- Verify philosophers are eating regularly
- Check for balanced eat/sleep/think timing

### Immediate Deaths
- Decrease `time_to_eat` or increase `time_to_die`
- Ensure parameters allow sufficient eating time
- Check for proper fork acquisition

### Simulation Hangs
- Verify deadlock prevention is working
- Check mutex initialization and destruction
- Ensure monitor thread is running

## Standards Compliance
- **42 Norm**: Follows strict coding standards (Norminette compliant)
- **Thread Safety**: All shared data properly synchronized
- **Memory Safety**: No memory leaks or buffer overflows
- **POSIX Compliance**: Uses standard pthread library functions

## Author
**nweber** - 42 Heilbronn Student
