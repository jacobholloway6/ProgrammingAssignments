# programOne

Created by Jacob Holloway
Red ID: 827294826

The purpose of this project is to help understand system calls and how the program is able to spawn and run processes as well as terminate.

Your assignment is to write code in mulproc.c to fork two child processes running the two programs testalphabet and testspecial generated in preliminary programming test in parallel.

 

Detailed Requirements:

    Spawn exactly two child processes, one is to run testspecial program and the other is to run testalphabet program;
    When a child process starts executing a program, print a message to the output screen showing which child process (with PID) is running this program (with program name), for example:

        "CHILD <PID: 16741> process is executing testalphabet program!"

    When one child process finishes executing a program, this child process should be terminated, and at the same time, a message should be print to the output screen showing which  process (with PID) is done with this program (with program name), for example:

         "CHILD <PID: 16741> process has done with testalphabet program !"

    The messages should match the real execution orders, i.e. when the testspecial program starts/ends, the right message should pop up immediately.  Hence, you need to track the starting/ending point of each child process.

                The expected screen printing should be similar as follows:

     CHILD <PID: 16741> process is executing testalphabet program!

  CHILD <PID: 16742> process is executing testspecial program!

  ，-> 745668

  .  -> 798072

  ... ...

  CHILD <PID: 16742> process has done with testspecial program! See the results above! 

  a -> 2973036

  b -> 556908

... ...

CHILD <PID: 16741> process has done with testalphabet program! See the results above!

 

Note: Feel free to do any change of the file (fill the code, create new functions and etc). You also can create new .h and .c files (but I don’t think you really need).

 

Your program must execute correctly on Edoras machine, the instructor/TA will type the following commands to test your code:

make// generate executable file mulproc

./mulproc // two child processes will be generated to run testspecial and  testalphabet programs as stated above.