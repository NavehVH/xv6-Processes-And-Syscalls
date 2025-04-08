#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char** argv) {
    //(a)
    int initial = memsize();
    printf("Initial memory size: %d bytes\n", initial);

    //(b)
    void* buf = malloc(20 * 1024);
    if (!buf) {
        printf("Memory allocation failed\n");
        exit(1, "");
    }

    //(c)
    int after_alloc = memsize();
    printf("After allocation: %d bytes\n", after_alloc);

    //(d)
    free(buf);

    //(e)
    int after_free = memsize();
    printf("After free: %d bytes\n", after_free);

    exit(0, "");
}
