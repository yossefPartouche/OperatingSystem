#include <stdio.h>
#include <unistd.h>

int x = 0;
int main() {
    while (x <= 100){
        if (fork() != 0){
            printf("x = %d\n", x);
        }
        printf("x outside: %d\n", x);
        x++;
    }
    return 0;
}
