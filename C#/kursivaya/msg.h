#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdint.h>

#define MSGSZ 16	/* Size of text in MSG*/

struct msgbuf {
	long mtype;
	char mtext[MSGSZ];
};

