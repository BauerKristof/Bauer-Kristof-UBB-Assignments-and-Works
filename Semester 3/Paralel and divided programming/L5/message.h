#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MQ_CLIENT "/bkim1790_c"   // clientQid -> a kliens itt kapja az uzenetet
#define MQ_SERVER "/bkim1790_s"   // serverQid -> a szerver itt kapja az uzenetet
#define MAXSIZE 256

typedef struct{
    char day[3], hour1[6], hour2[6];
} clientMsg;

typedef struct{
      char row[MAXSIZE];
} serverMsg;
