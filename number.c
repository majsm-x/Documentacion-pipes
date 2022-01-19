#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>



int main() {
  pid_t pid;
  int fd[2];
  char buf[10];
  srand(time(NULL));
  int num =  rand() % 1000 + 1;

  if (pipe(fd) == -1) {
        perror("Creating pipe");

        exit(EXIT_FAILURE);

  }

        switch ( pid = fork()) {
                case 0:
                        close (fd[1]);
                        num = read (fd[0], buf, sizeof(buf));
                        sscanf(buf,"%d",&num);
                        if (num >= 500)
                        {
                        printf("%d es mayor o igual a 500\n", num , buf);
                        }
                        else
                        {
                        printf("%d es menor que 500\n", num, buf);
                        }
                        close (fd[0]);
break;
                case -1:
                        perror("fork fail");

                        exit(EXIT_FAILURE);

                        break;
                default:

                        close (fd[0]);
                        int random = 1 + rand() % 1000;
                        sprintf(buf,"%d",random);
                        write (fd[1], buf, 3);
                        close (fd[1]);
                        break;
                        }
  return 0;
}
