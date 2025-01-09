# Philosophers

<p align=center>
  <img src="https://github.com/miladrahmat/42-badges/blob/master/badges/philosopherse.png"><img height="144" src="https://github.com/user-attachments/assets/46c6bd9e-a045-43c6-986a-681cb2fb72bc">
</p>

<p align=center>
  <b>A text based simulator for the dining philosophers problem</b>
</p>

## Content

- [Introduction](#introduction)
  - [Problem overview](#problem-overview)
- [Usage](#usage)
  - [Example](#example)
- [Installation](#installation)


## Introduction

In this project we wrote a text based simulation for [the dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). The problem in this project is not exactly the same because in the original problem the philosophers can only alternately think and eat, and in this project they also sleep between meals.

For the simulation to work properly, each philosopher should be a thread and each fork should be protected with a mutex.

The goal of this project is to learn the basics of threading a process, learn to use mutexes and how to prevent data races and deadlocks.

### Problem overview

> One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
> 
> - The philosophers alternatively **eat**, **think** or **sleep**.
> - There are as many forks on the table as there are philosophers.
> - A philosopher can only eat their spaghetti when they have both their left and right fork.
> - When a philosopher has finished eating they put their forks back on the table and start sleeping. Once awake, they start thinking again.
>   
> The simulation stops when a philosopher dies of starvation.

## Usage

The program takes the following arguments:
- **Number of philosophers**: The number of philosophers and forks.
- **Time to die** (in milliseconds): If a philosopher didn't start eating **time_to_die** milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- **Time to eat** (in milliseconds): The time it takes for a philosopher to eat.
- **Time to sleep** (in milliseconds): The time a philosopher will spend sleeping.
- **Number of times each phlosopher must eat** (optional argument): If all philosophers have eaten at least **number of times each philosopher must eat** times, the simulation stops. If not specified the simulation stops when a philosopher dies.

The program outputs any state change of a philosopher in the following format:
- **timestamp_in_ms** **X** **has taken a fork**
- **timestamp_in_ms** **X** **is eating**
- **timestamp_in__ms** **X** **is sleeping**
- **timestamp_in_ms** **X** **is thinking**
- **timestamp_in_ms** **X** **died**

***time_stamp_in_ms** is the current timestamp in milliseconds and **X** is the number of the philosopher* 
### Example

When given the program is run with the following arguments:
```
./philo 5 800 300 400
```
The output should be:
```
0 2 is thinking
0 1 is thinking
0 1 has taken a fork
0 4 is thinking
0 5 is thinking
0 3 is thinking
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
0 1 has taken a fork
0 1 is eating
300 1 is sleeping
300 5 has taken a fork
300 5 has taken a fork
300 4 has taken a fork
300 2 has taken a fork
300 2 has taken a fork
300 2 is eating
300 3 is sleeping
300 5 is eating
600 2 is sleeping
600 5 is sleeping
600 4 has taken a fork
600 4 is eating
701 3 is thinking
701 1 is thinking
701 1 has taken a fork
701 1 has taken a fork
701 1 is eating
800 3 died
```

## Installation

To install and test the program, run the following on the command line:
```
git clone https://github.com/miladrahmat/Philosophers.git
cd Philosophers
make
```
