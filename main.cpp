#include "BinaryOperation.h"

int main() {
    Integer first_num(20);
    Integer second_num(8);

    Integer add  = first_num + second_num;
    Integer sub = first_num - second_num;
    Integer multiply = first_num * first_num;
    Integer divide = first_num / second_num;

    add.print();
    sub.print();
    multiply.print();
    divide.print();

    return 0;
}