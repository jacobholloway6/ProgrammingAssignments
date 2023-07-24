Please answer the following questions regarding your programming assignment#2.



1) Please describe your design of your implementation.

  For my program I started with finding out how many files are present within the data folder that are .txt files. Once that was done I divided the number of files by the number of threads that was passed along when the executable was initially ran. Once the programs have started to process the files they will inform the user that the files are being processed by printing the file it is processing along with the thread ID that is being used to process the file. I figured that if my program knew the amount of files it will need to process it can divy it up properly to all threads. Throughout my program are various checks to validate that the files are correct .txt files along with printing any errors that might exist when attempting to either open the directory or read the file. Along with reading the files, I provided some checks to validate that it can succesfully create a file that can be opened to view the reslts instead of only relying on the output from the CLI although the information that is printed on the CLI is the same as what is in the file. 


2) Please execute your program by varying thread quantities: {3, 4, 6, 8, 10, 12}, measure the execution times and document your measurement below.

(Note: To ensure precise timing for each configuration, it may be necessary to conduct multiple experiments and calculate the average.)

Times for execution per thread:
Ran 5 times and the average is below

3: 4.20 seconds 
4: 4.96 seconds 
6: 4.90 seconds
8: 4.87 seconds
10: 5.72 seconds
12: 5.62 seconds
    

3) Do the observed trends in the measured execution times align with your initial expectations? Please provide a justification for your response.

They do not, when I started this assignment, I thought that adding more threads would alow for the program to run more efficiently. However I observed that as I added more threads it tended to make the execution time longer whenadding more. My fastest times were when I had it just use one or two threads which I found very interesting. I think that the way the computer is allocating resources to perform the execution of the program has to do with longer run times. When I allocate more threads the computer is suddenly being told to throw significantly more resources at something so it needs to stop what it is doing and push more resources to the executable. 






4) Is it possible to improve your design to achieve a greater speedup for your program?  If so, what are the possible improvements you can make to your design? 

 If not, why you think your current design is optimal?

I believe there is always room for improvement and optimization. One way that I might be able to improve this is with the use of a Thread Pool which will allow my program to pull from the threads that are already allocated for my program rather generating a new thread and then destroying it when it is finished its task. Another option is how I am designating the resources when going through the files, I could change it to use a work queue so that the threads are able to grab another text file when they have finished one instead of only having the threads perform their own tasks. This is equivalent to someone finishing a task early and then helping someone else who might be taking longer on their own task. I am unsure if in my case the times are supposed to be getting larger and larger when I provide the program with more threads but I feel like it should be going down so there will always be room for optimization

