# Philosophers

A multithreading simulation of the classic dining philosophers problem.

> *42 School project exploring concurrent programming, thread synchronization, and deadlock prevention.*

---

## The Problem

N philosophers sit around a table with N forks. Each philosopher needs two forks to eat. They alternate between **eating**, **sleeping**, and **thinking**. If a philosopher doesn't eat within a certain time, they die.

## Quick Start

```bash
make
./philo 5 800 200 200
```

## Usage

```
./philo <philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals]
```

| Parameter | Description |
|-----------|-------------|
| `philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Max milliseconds between meals before death |
| `time_to_eat` | Milliseconds spent eating |
| `time_to_sleep` | Milliseconds spent sleeping |
| `meals` | Optional: stop after each philosopher eats this many times |

### Examples

```bash
./philo 5 800 200 200      # 5 philosophers, no one dies
./philo 4 310 200 100 3    # stops after 3 meals each
./philo 1 800 200 200      # single philosopher (always dies)
```

## Output

```
timestamp_ms philosopher_id action
```

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

## Project Structure

```
philo/
├── philo/              # mandatory (threads + mutexes)
│   ├── main.c
│   ├── init.c
│   ├── simulation.c
│   ├── actions.c
│   ├── utils.c
│   └── cleanup.c
└── philo_bonus/        # bonus (processes + semaphores)
    ├── main.c
    ├── init.c
    ├── simulation.c
    ├── actions.c
    ├── forks.c
    ├── utils.c
    └── cleanup.c
```

## Build

```bash
make            # build mandatory
make bonus      # build bonus version
make clean      # remove objects
make fclean     # remove all
make re         # rebuild
```

## Implementation

### Mandatory Version
- One thread per philosopher + monitor thread
- Mutexes protect forks and shared state
- Asymmetric fork ordering prevents deadlock

### Bonus Version
- One process per philosopher
- Semaphores manage fork pool
- Parent process monitors for deaths

## Key Concepts

| Concept | Solution |
|---------|----------|
| Deadlock | Asymmetric resource ordering (odd/even) |
| Race conditions | Mutex-protected printing and state access |
| Starvation | Balanced timing and philosopher scheduling |
| Precise timing | Custom usleep with busy-wait |

---

*42 Heilbronn — nweber*
