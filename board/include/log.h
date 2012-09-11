#ifndef __LOG_H
#define __LOG_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
/* LOG日志管理 */
extern void log_init(void);
extern void log_set_level(int level);
extern void log_close(void);
extern void log_write(int level, const char *fmt, ...)
        __attribute__((format(printf, 2, 3)));

#define ERROR(x...)     log_write(3, " error: " x)
#define INFO(x...)      log_write(4, " info : "x)

/* 默认记录级别 */
#define LOG_DEFAULT_LEVEL       5

#endif
