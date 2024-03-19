## Philosophers (a School 42 project)

This repository contains the source code for the Philosophers project, completed as part of the curriculum at 42. This project explores concepts of concurrent programming, specifically focusing on using mutexes as the main synchronization mechanism.

This project is for educational purposes only.

## Project Overview

The project is based on the classic Dining Philosophers problem. It simulates a scenario where philosophers sit at a round table with shared forks and bowls of food. At each moment of time, they can be in one of three states: eating, sleeping, or thinking. 

To eat, a philosopher needs to grab two forks, one on their left and one on their right. Eating with just one fork is impossible in this simulation. However, the number of available forks is equal to the number of philosophers. This means that the first philosopher's left fork is also the second philosopher’s right fork and so on. The last philosopher’s left fork is also the first philosopher’s right fork. 

The main goal of the project is to design the simulation in such a way that the philosophers take turns using the shared forks and eating. Any philosopher who doesn’t get to eat X milliseconds after the start of their last meal dies. This situation should be avoided. 

Each simulation has the following parameters: 

* number of philosophers (and also the number of forks)
* time_to_die: an amount of time in milliseconds that every philosopher has since the start of their last meal. Each philosopher has to grab the two forks on their sides and start their next meal before this amount of time elapses, otherwise, they die of starvation.
* time_to_eat: an amount of time in milliseconds that it takes each philosopher to complete a meal after they’ve grabbed both forks (they will be holding both forks during this time).
* time_to_sleep: an amount of time in milliseconds that it takes each philosopher to sleep after a meal. 
* number_of_times_each_philosopher_must_eat (optional parameter): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies. 

The following conditions should be observed :

* Two philosophers sitting next to each other can’t be using the same fork at the same time
* There should be no deadlocks, i.e. situations where no philosopher can start eating because every philosopher holds on to just one fork and has to wait forever for the second fork to become available
* The simulation should be designed to minimize the risk of starvation, i.e. a situation where a philosopher has to wait too long for the two forks on his sides to become available. 

In this project, I use threads and mutexes to coordinate access to forks and ensure proper philosopher behavior.


### Code Structure:

* src/: Contains the source code files 
* Makefile: Build instructions for compiling and running the programs.
* README.md: This file (you are currently reading it!)


### Project Requirements:

* The project is coded in C, adhering to the 42 coding norm.
* The code should be free of memory leaks, crashes, undefined behavior, and norm violations. —Please, let me know if you identify any bugs or scenarios that lead to a crash!


### Running the Project

* Make sure you have a gcc compiler installed 
* Open a terminal in the project directory.
* Run make to compile the code.

```bash
make
```

Once you’ve compiled an executable called philo, you can launch it with the following command line arguments: 

1. number of philosophers (should be more than 1 and less than 200)
2. time_to_die in milliseconds (should be more than 60)
3. time_to_eat in milliseconds (should be more than 60)
4. time_to_sleep in milliseconds (should be more than 60)
5. optional argument: number_of_times_each_philosopher_must_eat (any integer)

### Example: 

```bash
./philo 5 800 200 200 6 
```

[![asciicast](https://asciinema.org/a/eMugvkuex75wMUrcAWJnEm5H7.svg)](https://asciinema.org/a/eMugvkuex75wMUrcAWJnEm5H7)

A simulation starts and the log entries start appearing on the screen documenting all the changes that are occurring until every philosopher has eaten enough times (when specified) or a philosopher dies. Depending on the parameters that you’ve entered, a simulation can potentially go on forever, in which case you can just stop the program. 






