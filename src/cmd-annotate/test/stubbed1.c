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

void b() {
    stub3();
}

void a() {
    b();
}

int main(int argc, char **argv) {
    int i=0;
//    stub1();
//    stub2();
    for (int i=0;i<10000;i++) {
        if (i%2==0) {
            stub1();
        } else if (i%3==0) {
            stub3();
        } else {
            stub2();
        }
    }
    i++;
    a();
    i=0;
    return 0;
}