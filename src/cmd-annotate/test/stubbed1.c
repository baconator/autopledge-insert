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
    stub1();
    stub2();
    i++;
    a();
    i=0;
    return 0;
}