#ifndef CEPH_STAT_H
#define CEPH_STAT_H

#include <acconfig.h>

#include <sys/stat.h>

/*
 * Access time-related `struct stat` members.
 *
 * Note that for each of the stat member get/set functions below, setting a
 * high-res value (stat_set_*_nsec) on a platform without high-res support is
 * a no-op.
 */

/* modification time */

static inline uint32_t stat_get_mtime_nsec(struct stat *st)
{
#ifdef HAVE_STAT_TV_NSEC
  return st->st_mtim.tv_nsec;
#elif defined(HAVE_STAT_ST_TIMESPEC)
  return st->st_mtimespec.tv_nsec;
#else
  return 0;
#endif
}

static inline void stat_set_mtime_nsec(struct stat *st, uint32_t nsec)
{
#ifdef HAVE_STAT_TV_NSEC
  st->st_mtim.tv_nsec = nsec;
#elif defined(HAVE_STAT_ST_TIMESPEC)
  st->st_mtimespec.tv_nsec = nsec;
#endif
}

#define stat_get_mtime_sec(st) ((st)->st_mtime)
#define stat_set_mtime_sec(st, sec) do { (st)->st_mtime = sec; } while (0)

/* access time */

static inline uint32_t stat_get_atime_nsec(struct stat *st)
{
#ifdef HAVE_STAT_TV_NSEC
  return st->st_atim.tv_nsec;
#elif defined(HAVE_STAT_ST_TIMESPEC)
  return st->st_atimespec.tv_nsec;
#else
  return 0;
#endif
}

static inline void stat_set_atime_nsec(struct stat *st, uint32_t nsec)
{
#ifdef HAVE_STAT_TV_NSEC
  st->st_atim.tv_nsec = nsec;
#elif defined(HAVE_STAT_ST_TIMESPEC)
  st->st_atimespec.tv_nsec = nsec;
#endif
}

#define stat_get_atime_sec(st) ((st)->st_atime)
#define stat_set_atime_sec(st, sec) do { (st)->st_atime = sec; } while (0)

/* last status change time */

static inline void stat_set_ctime_nsec(struct stat *st, uint32_t nsec)
{
#ifdef HAVE_STAT_TV_NSEC
  st->st_ctim.tv_nsec = nsec;
#elif defined(HAVE_STAT_ST_TIMESPEC)
  st->st_ctimespec.tv_nsec = nsec;
#endif
}

#define stat_set_ctime_sec(st, sec) do { (st)->st_ctime = sec; } while (0)

#endif
