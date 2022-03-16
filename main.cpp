#include "BinaryOperation.h"

int main() {
    Integer first_num(38);
    Integer second_num(13);

    Integer add  = first_num + second_num;
    Integer sub = first_num - second_num;
    Integer multiply = first_num * second_num;
    Integer divide = first_num / second_num;
    Integer remainder = first_num % second_num;

    add.print();
    sub.print();
    multiply.print();
    divide.print();
    remainder.print();

    return 0;
}