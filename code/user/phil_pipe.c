#include "phil_pipe.h"

int fds[PHIL_NUM][2];             // array that holds the field descriptor for each pipe
int pids[PHIL_NUM];               // array that holds the pid of each philosopher process
int advance[PHIL_NUM] = {0};      // array that holds the semaphores that controll the philosopher processes


void eat(int fd[2], int id){    
  // eat
  printString("\n", 1);
  printString("Philosopher ", 12);
  printNum(id);
  printString(" eats.\n", 6);
  printString("\n", 1);
  pipe_write_block(fd[1], finished);                                            // philosopher tells waiter he has finished eating and returns forks
}

void leftFork(int fd[2], int id){
  pipe_write_block(fd[1], wantsLeft);                       // phiosopher requests left fork
  printString("\n", 1);

  printString("Philosopher ", 12);
  printNum(id);
  printString(" waits to pick left fork.\n", 26);
  sem_wait(&advance[id]);                                   // philosopher blocks until he receives the left fork
  int response = pipe_read_block(fd[0], 1);                 // once the waiter provied the left fork, he writes to the pipe and updates 
  if (response == giveFork) {       
    printString("\n", 1);
                                                            // the semaphore so the philosopher can continue
    printString("Philosopher ", 12);
    printNum(id);
    printString(" picked left fork.\n", 19);
  }
  else {
    printString("Bug in execution\n", 17);
  }
  
}

void rightFork(int fd[2], int id){                            // same process as leftFork
  pipe_write_block(fd[1], wantsRight);
  printString("\n", 1);

  printString("Philosopher ", 12);
  printNum(id);
  printString(" waits to pick right fork.\n", 27);
  sem_wait(&advance[id]);
  int response = pipe_read_block(fd[0], 1);
  if (response == giveFork) {
    printString("\n", 1);

    printString("Philosopher ", 12);
    printNum(id);
    printString(" picked right fork.\n", 20);
  }
  else {
    printString("Bug in execution\n", 17);
  }
}




void philosopher(int id, int fd[2]){
  int i = 0;                        // set i to be the number of times each philosopher eats before leaving the table
  while(i < 2){ 
    sleep_s(0.5);                   // simulate a philosopher thinking by sleeping for 0.5s
    leftFork(fd, id);
    rightFork(fd, id);
    eat(fd, id);
    i++;
  }
  exit(EXIT_SUCCESS);
}  


void waiter(){
  int forkStatus[PHIL_NUM];                       //array to keep track of the status of each fork
  for(int i = 0; i < PHIL_NUM; i++){
    forkStatus[i] = available;
  }
  while(1){

    for(int i = 0; i < PHIL_NUM; i++){
      int philoWrite = pipe_read(fds[i][1], 0);    // go through the pipes and receive requests from philosophers (IMPORTANT: PIPE IS NOT 
                                                     // ERASED SO THE REQUEST IS NOT LOST IF IT CANNOT BE HANDLED IMMEDIATELY I.E FORKS ARE NOT AVAILABLE)
      if(philoWrite == wantsLeft){
        if(forkStatus[i] == available && forkStatus[(i+1) % PHIL_NUM] == available) {   
          philoWrite = pipe_read(fds[i][1], 1);                                         // pipe is now erased since it is certain the request can be handled
          pipe_write_block(fds[i][0], giveFork);                                        // provide the forks to the philosopher
          sem_post(&advance[i]);                                                        // use sem_post so the philosopher can unblock and continue execution
          printString("Waiter gives left fork to philosopher ", 38);
          printNum(i);
          printString("\n",1);
          forkStatus[i] = i;                                                            // update the fork array so that the fork is no longer available
          forkStatus[(i + 1 + PHIL_NUM) % PHIL_NUM] = i;
        }
      }
      if(philoWrite == wantsRight){                                                      // same process as left fork     
        if(forkStatus[(i+1) % PHIL_NUM] == i){
          philoWrite = pipe_read(fds[i][1], 1);
          printString("Waiter gives right fork to philosopher ", 39);
          printNum(i);
          printString("\n", 1);
          pipe_write_block(fds[i][0], giveFork);
          sem_post(&advance[i]);
        }
      }
      if(philoWrite == finished){
        philoWrite = pipe_read(fds[i][1], 1);
        if(forkStatus[i] == i)forkStatus[i] = available;
        if(forkStatus[(i + 1 + PHIL_NUM) % PHIL_NUM] == i)                                // set both fork status as available
          forkStatus[(i + 1 + PHIL_NUM) % PHIL_NUM] = available;
      }


    }
    yield();                                                                              // if the waiter finds no requests, yield() (so that processing power isnt)
  }                                                                                       // just waisted by the waiter waiting for requests
  exit(EXIT_SUCCESS);
}



void phil_pipe_main() {
    for (int i = 0; i < PHIL_NUM; i++) {
        int pid = fork();            

        if (pid == 0) { 
            pipe(fds[i]);

            philosopher(i, fds[i]);
        }

        else {
            pids[i] = pid;
        }
    }
    waiter();
    exit(EXIT_SUCCESS);
}