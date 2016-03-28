#include <stdio.h>

void stub1() {
    return;
}

void stub2() {
    return;
}

void stub3() {
    return;
}


int main(int argc, char **argv) {
    for (int i=0;i<10000;i++) {
        if (i%2==100001) {
            stub1();
            stub2();
        } else {
            stub2();
        }
    }
    return 0;
}