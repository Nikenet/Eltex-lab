#include <stdio.h>
#include <stdlib.h>
#include "amessage.pb-c.h"

int main (int argc, char * argv[]) 
{
  DMessage msg    = DMESSAGE__INIT;   // DMESSAGE
  Submessage sub1 = SUBMESSAGE__INIT; // SUBMESSAGE A
  Submessage sub2 = SUBMESSAGE__INIT; // SUBMESSAGE B
  void *buf;
  unsigned len;
  
  if (argc != 2 && argc != 3)
  { // Allow one or two integers
    fprintf(stderr,"usage: dmessage a [b]\n");
    return 1;
  }
  sub1.value = argv[1]; 
  msg.a = &sub1;               // Point msg.a to sub1 data
  
  // NOTE: has_b is not required like amessage, therefore check for NULL on deserialze
  if (argc == 3) { sub2.value = argv[2]; msg.b = &sub2; } // Point msg.b to sub2 data
  
  len = dmessage__get_packed_size (&msg); // This is the calculated packing length
  buf = malloc (len);                     // Allocate memory
  dmessage__pack (&msg, buf);             // Pack msg, including submessagesmaw

  fprintf(stderr,"Writing %d serialized bytes\n",len); // See the length of message
  fwrite (buf, len, 1, stdout);           // Write to stdout to allow direct command line piping
  
  free(buf); // Free the allocated serialized buffer
  return 0;
}