#include <stdio.h>
#include "amessage.pb-c.h"
#define MAX_MSG_SIZE 4096

int main (int argc, const char * argv[]) 
{
  DMessage *msg;         // DMessage using submessages
  Submessage *sub1,*sub2;// Submessages
  char c; int i=0;       // Data holders
  uint8_t buf[MAX_MSG_SIZE]; // Input data container for bytes
    
  while (fread(&c,1,1,stdin) != 0)
  {
    if (i >= MAX_MSG_SIZE)
    {
      fprintf(stderr,"message too long for allocated buffer\n");
      return 1;
    }
    buf[i++] = c;
  }
    
  msg = dmessage__unpack(NULL,i,buf); // Deserialize the serialized input
  if (msg == NULL)
  { // Something failed
    fprintf(stderr,"error unpacking incoming message\n");
    return 1;
  }
  sub1 = msg->a; sub2 = msg->b;
  printf("Received: a=%s",sub1->value);
  if (msg->b != NULL) printf(" b=%s",sub2->value);
  printf("\n");
    
  dmessage__free_unpacked(msg,NULL);
    
  return 0;
}