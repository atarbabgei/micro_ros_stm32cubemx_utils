#include <time.h>

#include "master_clock.h"

int clock_gettime(int clock_id, struct timespec * tp)
{
  uint64_t ticks;
  uint64_t nsec_total;

  (void)clock_id;

  ticks = master_clock_now_ticks();
  nsec_total = (ticks * 1000000000ULL) / MASTER_CLOCK_HZ;

  tp->tv_sec = (time_t)(nsec_total / 1000000000ULL);
  tp->tv_nsec = (long)(nsec_total % 1000000000ULL);

  return 0;
}
