// Ping pong a bytes between 2 processes over a pair
// of pipes, one for each direction

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Only ping pong one byte for now
#define MESSAGE_LEN 1

void
pingpong(void)
{
  int child_pid, pid;
  char buf[MESSAGE_LEN + 1];
  const char message[] = "a";
  int parent_fd[2]; // [0] is read end, [1] is write end

  // Parent process, sends 1 byte to child and waits for reply
  pipe(parent_fd);
  child_pid = fork();
  if (child_pid > 0) {
    pid = getpid();
    write(parent_fd[1], message, MESSAGE_LEN);
    wait();
    read(parent_fd[0], buf, MESSAGE_LEN);
    fprintf(2, "%d: received pong\n", pid);
  
  // Child process, waits for byte from parent and replies
  } else if (child_pid == 0)  {
    pid = getpid();
    read(parent_fd[0], buf, MESSAGE_LEN);
    fprintf(2, "%d: received ping\n", pid);
    write(parent_fd[1], message, MESSAGE_LEN);
  
  // This shouldn't happen...
  } else {
    fprintf(2, "fork failed, got child pid: %d\n", child_pid);
  }
}

int
main(int argc, char *argv[])
{
  if (argc != 1) {
    fprintf(2, "usage: pingpong\n");
    exit();
  }
  pingpong();
  exit();
}
