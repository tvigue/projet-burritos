#include "syscall.h"

int main ()
{
  char* s = "aaaaaa";
  int n = 7;
  GetString(s,n);
  PutString(s);

  PutChar('\n');
  return 0;
}
