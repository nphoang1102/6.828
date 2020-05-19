// Output uptime in terms of system ticks

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 1) {
    fprintf(2, "usage: uptime\n");
    exit();
  }
  fprintf(2, "%d\n", uptime());
  exit();
}
