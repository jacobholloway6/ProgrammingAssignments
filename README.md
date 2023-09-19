# ProgrammingAssignments

Created by: Jacob Holloway

Class was taken Summer 2023 

The following folders are programming assignments that have been completed for CS480 Operating systems at SDSU. Each folder contains a specific program with different levels of functionality. Below you will see the purpose of each program. Initially the program was made on my Macbook Pro but and was inteded to run on the remote school computer running CentOS. If your environment is not setup to compile and run lixux programs on your mac you may run into some issues. 

To resolve issues with compilation on your computer you will need to download and install Homebrew. Which allows for the management of packages. 
Next you will need to install GCC using "brew install GCC"
Once that has been installed you will also need to create a symbolic link for the gcc to run homebrew version instead of clang. Then you should not run into any issues.

Alternatively the programs can be compiled manually using either gcc or c99.

**Zero:** Programming assignment zero scans the content of the data in the folder data, once it has scanned the contents of the data folder it takes the information and creates a txt file under the folder result. There are two different functions, one is testalphabet and the other is testspecial. The first one will tell you the frequency of standard characters and the latter will provide you with the special characters.

**One:** The purpose of this project is to help understand system calls and how the program is able to spawn and run processes as well as terminate.

Your assignment is to write code in mulproc.c to fork two child processes running the two programs testalphabet and testspecial generated in preliminary programming test in parallel.

**Two:** The purpose of this programming assignment is to familiarize yourself with utilizing multithreading. As more threads are given to the executable it will become faster and faster (as expected).
 
**Three:** Purpose of this assignment intends to familiarize you using POSIX semaphores to solve the bounded-buffer problems (aka the classical producer-consumer problem.)
Description
The bounded-buffer problems (aka the producer-consumer problem) is a classic example of concurrent access to a shared resource. A bounded buffer lets multiple producers and multiple consumers share a bounded buffer. Producers write data to the buffer and consumers read data from the buffer.
	•	Producers must block if the buffer is full.
	•	Consumers must block if the buffer is empty.

**Four:** This code implements two fundamental page replacement algorithms, namely First In First Out (FIFO) and Least Recently Used (LRU), to simulate memory access and page fault handling. 
