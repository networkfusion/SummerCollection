#include <errno.h>
#include <sys/types.h>
#include "exception.h"


extern char _sheap __attribute__((section(".data")));
extern char _eheap __attribute__((section(".data")));


caddr_t _sbrk_r (struct _reent *prt, ptrdiff_t incr) {
    static char *curr_heap_end = &_sheap;
    char *prev_heap_end;

    prev_heap_end = curr_heap_end;
    curr_heap_end += incr;

    if (curr_heap_end > &_eheap) {
        errno = ENOMEM;
        return (caddr_t) -1;
    }

    return (caddr_t) prev_heap_end;
}


void __assert_func (const char *file, int line, const char *func, const char *failedexpr) {
    EXCEPTION_TRIGGER(TRIGGER_CODE_ASSERT);
    while (1);
}
