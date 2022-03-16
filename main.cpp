#include "BinaryOperation.h"

int main() {
    Integer first_num(10);
    Integer second_num(5);

    Integer add  = first_num + second_num;
    Integer sub = first_num - second_num;
    Integer multiply = first_num * second_num;
    Integer divide = first_num / second_num;
    Integer remainder = first_num % second_num;

    first_num.print();
    second_num.print();
    printf("A + B = %d + %d\n", first_num.decimal(), second_num.decimal());
    add.print();
    printf("A - B = %d - %d\n", first_num.decimal(), second_num.decimal());
    sub.print();
    printf("A * B = %d * %d\n", first_num.decimal(), second_num.decimal());
    multiply.print();
    printf("A / B = %d / %d\n", first_num.decimal(), second_num.decimal());
    divide.print();
    printf("A %% B = %d %% %d\n", first_num.decimal(), second_num.decimal());
    remainder.print();

    return 0;
}