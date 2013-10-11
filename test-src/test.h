#ifndef TEST_H
#define TEST_H

#define HAVE_ERRNO_H
#define HAVE_UNISTD_H
#define HAVE_SYS_TYPES_H
#define HAVE_SYS_STAT_H
#define HAVE_FCNTL_H
#define HAVE_SHOUT_SHOUT_H

#define ices_log(...)  printf("\n" __VA_ARGS__)
#define ices_log_debug(...)  printf("\n" __VA_ARGS__)
#define ices_log_error(...)  printf("\n" __VA_ARGS__)

#endif // TEST_H
