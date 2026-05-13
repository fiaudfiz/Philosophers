*This project has been created as part of the 42 curriculum by miouali.*

# Philosophers : I never thought philosophy would be so deadly

---

## Table des Matieres

1. [The Project](#1-the-project)
2. [Description](#2-description)
3. [Instructions](#3-instructions)
4. [Ressources](#4-ressources)

---

## 1. The Project

The Dining Philosophers problem is a problem stated by [Edsger Dijkstra](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra). It presents a table of philosophers who share forks to eat spaghetti. Each philosopher has a fork on his left, and in order to eat the dish in the middle, he must pick up 2 forks, therefore that of his neighbor on the right. The goal of [Edsger Dijkstra](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra) is to illustrate the phenomenon of deadlock that can occur in a computer system when sharing resources, here the forks. The problem highlights the conditions of this deadlock, in order to find solutions.
For this, the problem is presented as follows: a philosopher can be in 3 different states, "thinking", "sleeping" and "eating". He can think for an indefinite amount of time but the eating time and sleeping time are specified. If one of the philosophers does not eat after a certain time, he dies of starvation and the simulation stops.
In this project, we also add an optional argument, which is the maximum number of meals; as soon as all philosophers have eaten this minimum number of meals, the simulation stops.
This project allows us to discover the logic of threads and mutexes, as well as the problems they generate: deadlock, race condition etc...
We will here represent each philosopher by a thread and each fork by a mutex, concepts that will be presented below.
It is already necessary to distinguish two cases: the case where we have an even number of philosophers, and the case where we have an odd number of philosophers. This changes everything in the thread routine, since indeed, if we start all the philosophers at the same time and each takes his left fork first, we will end up blocked.

## 2. Description

This project is coded in C, and it follows the 42 norm, among other things no more than 25 lines per function, no more than 5 functions per file, etc... We have a Makefile and an include to include the libraries used.

### 2.1 Project Structure

All the code is in the srcs folder, and when compiling, an objs folder is then created containing all the objects of the project.

```plaintext
.
├── includes
│   └── philo.h
├── Makefile
├── README.md
├── srcs
│   ├── body_guard.c
│   ├── exit.c
│   ├── main.c
│   ├── parser.c
│   ├── prog_usage.c
│   ├── routine.c
│   ├── utils_0.c
│   └── utils_1.c
└── tester_philo.sh

```

### 2.2 Threads

Let us now talk about threads. A thread is similar to a process, and when several of them are used, they allow multiple instructions to be executed at the same time.
However, even if from a user point of view the instructions seem to run in parallel, the threads of the same process share its virtual memory.
It is therefore ideal here to make each philosopher a thread, because they can thus operate at the same time.

### 2.3 Mutex

The problem is that two philosophers cannot take the same fork at the same time, so we need a “locking” system; these are mutexes. They are used to lock/unlock a resource so that several threads do not read/write at the same time on the same memory area. This also ensures that all threads have the same version of the values. In this project, since other resources are shared apart from the forks, we will need to use more mutexes.

### 2.4 Routine

We therefore need to create a routine that will be followed by each thread, with a list of instructions in a specific order: the thread routine.

Problem: I said above that depending on whether the philosopher is even or odd, they should not do the same thing, so I simply separated the even case from the odd case. If we have an even number of philosophers, all even ones take left->right and the odd ones right->left. In the case of an odd number, it is a bit more complicated, because if all odd ones take right->left, the last one will have a problem with the first one, so in the case where the number is odd, the last odd one reverses its order of taking, like an even one.

After that, the chosen order is as follows:

* take forks
* eat
* sleep
* think

However, if we leave this routine as it is, it will generate deadlocks because some philosophers will eat more than others in the case of an odd number of philosophers. This is why when we have an odd number of philosophers, we add a second forced resting time in addition to the already specified sleeping time in order to maintain this balance.

### 2.5 Detect Death

Throughout the simulation, it must be possible to detect the death of a philosopher no later than 10 microseconds after their actual death. Therefore, the death of each philosopher must be continuously checked. The solution I implemented is the following: I added an additional thread called “body guard” and its role is to loop through all philosophers in order to verify death, and if a death occurs, set a flag that will allow the other threads to exit cleanly.

## 3. Instructions

### 3.1 Compiling

To compile the project, simply run `make`. The executable is then created with the name `philo`.

### 3.2 Execution

With the executable `./philo`, you must provide at least 4 arguments:

* number of philosophers
* time to die
* time to eat
* time to sleep

`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep (number_of_times_each_philosopher_must_eat)`

All times are in milliseconds.

The outputs are displayed as follows:
`time_since_execution    event`


## 4. Ressources

* [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* [Dining Philosophers Problem](https://diningphilosophers.eu)
* [Pthread.h](https://man7.org/linux/man-pages/man0/pthread.h.0p.html)
* [Notion of deadlock](https://github.com/fiaudfiz/Cours/blob/main/threads/notion_de_dead_lock.txt)
* [Notion of mutex](https://github.com/fiaudfiz/Cours/blob/main/threads/notion_de_mutex.txt)
* [Notion of race condition](https://github.com/fiaudfiz/Cours/blob/main/threads/notion_de_race_condition.txt)
* [Notion of thread](https://github.com/fiaudfiz/Cours/blob/main/threads/notion_de_thread.txt)
* [Race condition](https://en.wikipedia.org/wiki/Race_condition)
* [Deadlock](https://en.wikipedia.org/wiki/Deadlock_(computer_science))

