#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0
#define WRITE 1

int main() {

  pid_t pid;
  int   fd[2];

  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {

	  case 0:
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
		char *const cmd0[] = {"sort", NULL};
		execvp(cmd0[0], cmd0);

	  case -1:
		perror("fork() failed)");
		exit(EXIT_FAILURE);

	  default:
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		char *const cmd[] = { "cat", "/etc/hosts", NULL};
		execvp(cmd[0], cmd);
  }
}
