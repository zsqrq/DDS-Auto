//
// Created by wz on 24-1-12.
//
#include	"common/unpipc.h"
#include <unistd.h>

int main(int argc, char **argv)
{
  printf("SEM_NSEMS_MAX = %ld, SEM_VALUE_MAX = %ld\n",
         Sysconf(_SC_SEM_NSEMS_MAX), Sysconf(_SC_SEM_VALUE_MAX));
  exit(0);
}
