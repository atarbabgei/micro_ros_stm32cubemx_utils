#include <time.h>

#include "master_clock.h"

int clock_gettime(int clock_id, struct timespec * tp)
{
  uint64_t ticks;
  uint64_t mono_ns;
  int64_t  utc_ns;

  (void)clock_id;

  ticks = master_clock_now_ticks();
  mono_ns = (ticks * 1000000000ULL) / MASTER_CLOCK_HZ;

  /* Same UTC epoch offset the trigger/PPS/NMEA path uses (0 when unsynced). */
  utc_ns = (int64_t)mono_ns + master_clock_epoch_offset_ns();
  if (utc_ns < 0) {
    utc_ns = 0;
  }

  tp->tv_sec = (time_t)((uint64_t)utc_ns / 1000000000ULL);
  tp->tv_nsec = (long)((uint64_t)utc_ns % 1000000000ULL);

  return 0;
}
