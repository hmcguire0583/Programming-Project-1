/*   
insert #include directives for all needed header files here  */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *arv[]) { 
//create first pipe fd1 
// fork first child 

int fd1[2]; // create the first pipe fd1, has to be initalized with 2 ends

if (pipe(fd1) < 0) { // initializing the pipe itself
// pipe error
fprintf(stderr, "pipe error!\n"); 
exit(1); 
}
       
pid = fork();  // create first child for sort 

if (pid < 0) { 
// fork error 
fprintf(stderr, "forking error!\n");
exit(1); // program terminates unsuccesfully
} 


// NEXT PART I HAVEN'T STARTED:




if (pid == 0) { // first child process, run sort 

// sort ()

// tie write end of pipe fd1 to standard output (file descriptor 1) 
// close read end of pipe fd1 
// start the sort command using execlp 
// should not get here 
} 
//create second pipe fd2 
// fork second child 
pid = fork(); // create second child for uniq 
if (pid < 0) { 
// fork error 
} 
if (pid == 0) { // second child process, run uniq 
// tie read end of fd1 to standard input (file descriptor 0) 
// tie write end of fd2 to standard output (file descriptor 1) 
// close write end of pipe fd1 
// close read end of pipe fd2 
// start the uniq command using execlp 
// should not get here 
} 
// fork third child 
pid = fork() // create third child for wc -l 
if (pid < 0) { 
// fork error 
} 
if (pid == 0) { // third child process, run wc -l 
// tie read end of fd2 to standard input (file descriptor 0) 
// close write end of pipe fd2 
// close read end of pipe fd1 
// close write end of pipe fd1 
// start the wc -l command using execlp 
// should not get here 
} 
// parent process code 
// close both ends of pipes fd1 and fd2 
// wait for third process to end. 
} 