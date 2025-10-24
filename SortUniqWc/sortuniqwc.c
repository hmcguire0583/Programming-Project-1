/*   
insert #include directives for all needed header files here  */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 


int main(int argc, char *argv[]) { 
//create first pipe fd1 
// fork first child 
int fd1[2]; // create the first pipe fd1, has to be initalized with 2 ends

if (pipe(fd1) < 0) { // initializing the pipe itself
// pipe error
fprintf(stderr, "pipe error!\n"); 
return 1; 
}

pid_t pid1 = fork(); // create first child for sort 

if (pid1 < 0) { 
// fork error 
fprintf(stderr, "forking error!\n");
return 1; // program terminates unsuccesfully
} 

if (pid1 == 0) { // first child process, run sort 
printf("The child process running sort is: %d\n", getpid());     
// tie write end of pipe fd1 to standard output (file descriptor 1) 
dup2(fd1[1], 1);
// close read end of pipe fd1 
close(fd1[0]); // 0 is the read end of the pipe
// start the sort command using execlp 
execlp("/usr/bin/sort", "sort",  NULL);
// should not get here 
printf("Should not be here after execlp to sort\n"); // error message for exelcp failure
exit(1); // exits after execlp failure
} 

//create second pipe fd2 
int fd2[2]; // create the second pipe fd2, has to be initalized with 2 ends
if (pipe(fd2) < 0) { // initializing the pipe itself
// pipe error
fprintf(stderr, "pipe error!\n"); // pipe error message
return 1; // return
}

// fork second child 
pid_t pid2 = fork(); // create second child for uniq 
if (pid2 < 0) { 
// fork error 
fprintf(stderr, "forking error!\n");
return 1; // program terminates unsuccesfully
} 

if (pid2 == 0) { // second child process, run uniq 
printf("The child process running uniq is: %d\n", getpid());     
// tie read end of fd1 to standard input (file descriptor 0) 
dup2(fd1[0], 0);
// tie write end of fd2 to standard output (file descriptor 1) 
dup2(fd2[1], 1);
// close write end of pipe fd1 
close(fd1[1]);
// close read end of pipe fd2 
close(fd2[0]);
// start the uniq command using execlp 
execlp("/usr/bin/uniq", "uniq", NULL);
// should not get here 
printf("Should not be here after execlp to uniq\n"); // error message for exelcp failure
exit(1); // exits after execlp failure
} 

// fork third child 
pid_t pid3 = fork(); // create third child for wc -l 
if (pid3 < 0) { 
// fork error 
fprintf(stderr, "forking error!\n");
return 1; // program terminates unsuccesfully
} 

if (pid3 == 0) { // third child process, run wc -l 
printf("The child process running wc -l is: %d\n", getpid());     
// tie read end of fd2 to standard input (file descriptor 0) 
dup2(fd2[0], 0);
// close write end of pipe fd2 
close(fd2[1]);
// close read end of pipe fd1 
close(fd1[0]);
// close write end of pipe fd1 
close(fd1[1]);
// start the wc -l command using execlp 
execlp("/usr/bin/wc", "wc", "-l", NULL);
// should not get here 
printf("Should not be here after execlp to wc -l\n"); // error message for exelcp failure
exit(1); // exits after execlp failure
} 
// parent process code 
printf("I am the parent process: %d\n", getpid());
// close both ends of pipes fd1 and fd2 
close(fd1[0]);
close(fd1[1]);
close(fd2[0]);
close(fd2[1]);
// not implied in outline but we have to wait for pid1 and pid2 to avoid zombies.
waitpid(pid1, NULL, 0); 
// printf("First child process finished.\n"); 
waitpid(pid2, NULL, 0); 
// printf("Second child process finished.\n"); 
// wait for third process to finish.
waitpid(pid3, NULL, 0); 
printf("Third and last child process finished.\n"); // print Third child process finished as specified from pdf.
return 0;
} 