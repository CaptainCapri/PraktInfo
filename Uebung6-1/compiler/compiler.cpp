#include <cstdlib>
#include <cstdio>
#include <sys/mman.h>
#include <unistd.h>

int function(int x) {
  int y = x + 1;
  return y;
}

void write_program_x86(unsigned char *code) {
    unsigned ip = 0;
    printf("writing 32bit x86 code...\n");

    // move function parameter from stack to eax
    code[ip++] = 0x8b; // mov 4(%esp),%eax
    code[ip++] = 0x44;
    code[ip++] = 0x24;
    code[ip++] = 0x04;

    // add 1 to eax
    code[ip++] = 0x83; // add $0x1,%eax
    code[ip++] = 0xc0;
    code[ip++] = 0x01;

    // return from function
    code[ip++] = 0xc3; // ret
}

void write_program_x86_64(unsigned char *code) {
    unsigned ip = 0;
    printf("writing 64bit x86-64 code...\n");

    // move function parameter from edi to eax
    code[ip++] = 0x89; // mov %edi,%eax
    code[ip++] = 0xf8;

    // add 1 to eax
    code[ip++] = 0x83; // add $0x1,%eax
    code[ip++] = 0xc0;
    code[ip++] = 0x01;

    // return from function
    code[ip++] = 0xc3; // ret
}

int main() {
    unsigned char *my_own_code;
    int (*pointer_to_function)(int);

    pointer_to_function = function;

    int a = pointer_to_function(66);
    printf("a = %d\n", a);

    // get page size, usually 4096 bytes
    int pagesize = sysconf(_SC_PAGE_SIZE);
    printf("page size %d\n", pagesize);

    // allocate 128 bytes, aligned on page size
    int ret = posix_memalign((void**) &my_own_code, pagesize, 128);
    if (ret != 0) {
        fprintf(stderr, "posix_memalign() = %d\n", ret);
    }

    // change protection: memory is readable, writable, executable
    if (mprotect(my_own_code, 128, PROT_READ | PROT_WRITE | PROT_EXEC) < 0) {
        perror("mprotect");
        exit(EXIT_FAILURE);
    }

    // write program to memory
    if (sizeof(void*) == 8)
        write_program_x86_64(my_own_code);
    else
        write_program_x86(my_own_code);

    // set pointer to our code in memory
    pointer_to_function = (int (*)(int)) my_own_code;

    // execute
    int b = pointer_to_function(123);
    printf("b = %d\n", b);

    return EXIT_SUCCESS;
}
