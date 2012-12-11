#include "log.h"

static int log_fd = -1;
static int log_level = LOG_DEFAULT_LEVEL;

void log_set_level(int level) 
{
        log_level = level;
}

void log_init(void)
{
        static const char *name = "/dev/__kmsg__";
        if(mknod(name, S_IFCHR | 0600, (1 << 8) | 11) == 0) {
                log_fd = open(name, O_WRONLY);
        }
}

#define LOG_BUF_MAX     512

void log_write(int level, const char *fmt, ...) 
{
        char buf[LOG_BUF_MAX];
        va_list ap;

        if(level > log_level) return;
        if(log_fd < 0) return;

        va_start(ap, fmt);
        vsnprintf(buf, LOG_BUF_MAX, fmt, ap);
        buf[LOG_BUF_MAX - 1] = 0;
        va_end(ap);
        write(log_fd, buf, strlen(buf));
}

void log_close(void)
{
        close(log_fd);
}

