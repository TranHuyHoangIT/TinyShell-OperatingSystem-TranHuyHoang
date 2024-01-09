#include <stdio.h>
#include <unistd.h>

// The program prints consecutive numbers, printing 1 number every 1 second
//gcc -o PrintNum PrintNum.c 
int main() {
    int i = 1;
    printf("Print consecutive numbers:\n");
    while (1) {
        printf("%d\n", i++);
        fflush(stdout); 
        sleep(1);
    }

    return 0;
}
