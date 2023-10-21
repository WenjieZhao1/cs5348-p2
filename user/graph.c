#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "pstat.h"
#include "param.h"

void spin()
{
	int i = 0;
  int j = 0;
  int k = 0;
	for(i = 0; i < 50; ++i)
	{
		for(j = 0; j < 10000000; ++j)
		{
      k = j % 10;
      k = k + 1;
    }
	}
}

void print(struct pstat *stat, int data)
{  
    printf(1, "%d ", data);
    int i;
    for(i = 0; i < NPROC; i++) {
        if (stat->inuse[i] && stat->tickets[i] >= 10) {
            printf(1, "%d ", stat->ticks[i]);
      }
   }
   printf(1, "\n");
}
int
main(int argc, char *argv[])
{
    int base_tickets = 10;
    struct pstat procStats;
    int pid;
    int i;
    int tickets = base_tickets;
    for(i = 0; i < 3; i++){
        pid = fork();
        if(pid == 0){
            settickets(tickets);
            break;
            }       
        tickets += 10;
    }
    sleep(1);
    if(pid != 0)
    {
    int data;
    for(data = 0; data < 100; data++){
        if(getpinfo(&procStats) == 0)
            print(&procStats, data);
        sleep(1);
        }
    return 0;   
    }
   //spin
    else
    {
        for(;;)
        {
        spin();
        }
    }
}