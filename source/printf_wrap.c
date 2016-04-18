
#include "serial_api.h"
#include <stdarg.h>
#include <stdio.h>

void bprintf(const char *str) {
    extern serial_t stdio_uart;
    extern int stdio_uart_inited;

    static size_t buffer_size = 0;
    static uint8_t string_buffer[1024*5];

    if (stdio_uart_inited) {
        if (buffer_size) {
            {
                stdio_uart_inited = 0;
                printf("Dumped buffered cout: %uB\n\n", buffer_size);
                stdio_uart_inited = 1;
            }
            for (size_t ii=0; ii < buffer_size; ii++) {
                serial_putc(&stdio_uart, string_buffer[ii]);
            }
            buffer_size = 0;
        }
        while (*str != 0) {
            serial_putc(&stdio_uart, *str);
            str++;
        }
    } else {
        while (*str != 0) {
            if (buffer_size < sizeof(string_buffer)) {
                string_buffer[buffer_size++] = *str++;
            } else break;
        }
    }
}

/// printf uses malloc, which sucks when trying to use printf inside of malloc...
int __real_printf(const char *, ...);
int __wrap_printf(const char *fmt, ...) {
    va_list args;
    char buf[512];
    va_start(args, fmt);
    int ret = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    bprintf(buf);
    return ret;
}
