#include "BinaryOperation.h"
#include <string.h>

//constructor with input a char array
//Integer::Integer(const char* bitset) {
//    this->bitset = new char[num_bits + 1];
//    for (char i = 0; i < num_bits; i++) {
//        this->bitset[i] = bitset[i];
//    }
//    this->bitset[num_bits] = '\0';
//}

Integer::Integer(const char* bitset) {
    this->bitset = new char[num_bits + 1];
    this->bitset[num_bits] = '\0';

    char len = strlen(bitset);

    if (len < num_bits) {
        for (unsigned char i = 0; i < len; i++) {
            this->bitset[i] = '0';
        }
        for (unsigned char i = len; i < num_bits; i++) {
            this->bitset[i] = bitset[i];
        }
    }
    else {
        for (unsigned char i = 0; i < num_bits; i++) {
            this->bitset[i] = bitset[i];
        }
    }
}

//constructor with input a int number
Integer::Integer(int number) {
    this->bitset = new char[num_bits + 1];
    this->bitset[num_bits] = '\0';

    for (char i = num_bits - 1; i >= 0; i--) {
        
        if (number & 0x0001) 
            bitset[i] = '1';
        else 
            bitset[i] = '0';

        number >>= 1;
    }

}

//convert to decimal using OR ( | )
char Integer::decimal() {
    char z = 0x0000; //0 in default

    for (char i = 0; i < num_bits; i++) {

        bool bit = (this->bitset[i] == '1');

        z |= (char)bit;
        if (i !=  num_bits - 1) 
            z = z << 1;
    }

    return z;
}

//display binary char array
char* Integer::binary() {
    return this->bitset;
}

//print binary and decimal form, set 0 or 1 in what you want to display
void Integer::print(bool binary, bool decimal) {
    if (binary) {
        printf("Binary: %s\n", Integer::binary());
    }
    if (decimal) {
        printf("Decimal: %d\n", Integer::decimal());
    }
}

//add function with overload the + operator (can use + operator as normal number)
Integer operator + (const Integer& first, const Integer& second) {
    Integer result("00000000");
    
    bool save = false;
    for (char i = 7; i >= 0; i--) {
        //case 1: second.bitset position is 0
        if (second.bitset[i] == '0') {
            //case A: first.bitset position is '0'
            if (first.bitset[i] == '0') {
                //case a: save last position
                if (save) {
                    result.bitset[i] = '1';
                    save = false;
                }
                //case b: dont save last position
                else {
                    result.bitset[i] = '0';
                }
            }

            //case B: second.bitset position is '1'
            else if (first.bitset[i] == '1') {
                if (save) {
                    result.bitset[i] = '0';
                    save = true;
                }
                else {
                    result.bitset[i] = '1';
                }
            }
        }

        //case 2: second.bitset position is 1
        else if (second.bitset[i] == '1') {
            //case A: first.bitset position is '0'
            if (first.bitset[i] == '0') {
                if (save) {
                    result.bitset[i] = '0';
                    save = true;
                }
                else {
                    result.bitset[i] = '1';
                }
            }
            //case A: first.bitset position is '1'
            else if (first.bitset[i] == '1') {
                if (save) {
                    result.bitset[i] = '1';
                    save = true;
                }
                else {
                    result.bitset[i] = '0';
                    save = true;
                }
            }
        }
    }

    return result;
}

//return the two complement of a number (negative number)
Integer Integer::two_complement() {

    char* one_complement = new char[num_bits + 1];
    for (char i = 0; i < num_bits; i++) {
        if (this->bitset[i] == '1') {
            one_complement[i] = '0';
        }
        else if (this->bitset[i] == '0') {
            one_complement[i] = '1';
        }
    }

    one_complement[num_bits] = '\0';

    return Integer(one_complement) + Integer("00000001");
}

//add function with overload the - operator (can use - operator as normal number)
Integer operator - (const Integer& first, Integer& second) {
    Integer result = first + second.two_complement();
    return result;
}

//return the number when shift x bit to the left
Integer Integer::left_shift(char bit_to_shift) {
    bool sign = (this->bitset[0] == '1');
    Integer result("00000000");

    for (char i = 0; i < num_bits - bit_to_shift; i++) {
        result.bitset[i] = bitset[i + bit_to_shift];
    }

    if (sign) {
        result.bitset[0] = '1';
    }
    else {
        result.bitset[0] = '0';
    }

    return result;
}

//add function with overload the * operator (can use * operator as normal number)
Integer operator * (Integer& first, Integer& second) {
    Integer result("00000000");
    
    bool isNegative = false;
    if (first.bitset[0] != second.bitset[0])
        isNegative = true;

    Integer first_num = (first.bitset[0] == '0') ? first : first.two_complement();
    Integer second_num = (second.bitset[0] == '0') ? second : second.two_complement();

    for (char i = 7; i >= 0; i--) {
        
        if (first_num.bitset[i] == '1') {
            Integer temp = second_num.left_shift(num_bits - i - 1);
            result = result + temp;
        }
    }

    if (isNegative) return result.two_complement();
    else return result;
}

//return the number when shift x bit to the right
Integer Integer::right_shift(char bit_to_shift) {
    bool sign = (this->bitset[0] == '1');

    Integer result("00000000");
    if (sign) result = Integer("11111111");

    for (char i = 0; i < num_bits - bit_to_shift; i++) {
        result.bitset[i + bit_to_shift] = this->bitset[i];
    }

    return result;
}

//add function with overload the / operator (can use / operator as normal number)
Integer operator / (Integer& dvend, Integer& dvsor) {

    Integer result(0);
    bool isNegative = false;
    if (dvend.bitset[0] != dvsor.bitset[0])
        isNegative = true;

    Integer dividend = (dvend.bitset[0] == '0') ? dvend : dvend.two_complement();
    Integer divisor = (dvsor.bitset[0] == '0') ? dvsor : dvsor.two_complement();

    Integer remainder = dividend.right_shift(num_bits - 1);

    char bit_pos = 0;
    while (bit_pos < num_bits) {
        Integer quotient = remainder - divisor;
        
        result = result.left_shift(1);
        bit_pos++;

        if (quotient.bitset[0] == '1') {
            result.bitset[num_bits - 1] = '0';
            remainder = remainder.left_shift(1);
        }
        else {
            result.bitset[num_bits - 1] = '1';
            remainder = quotient.left_shift(1);
        }

        remainder.bitset[num_bits - 1] = dividend.bitset[bit_pos];
    }

    if (isNegative) return result.two_complement();
    else return result;
}

Integer operator % (Integer& dvend, Integer& dvsor) {

    Integer dividend = (dvend.bitset[0] == '0') ? dvend : dvend.two_complement();
    Integer divisor = (dvsor.bitset[0] == '0') ? dvsor : dvsor.two_complement();

    Integer remainder = dividend.right_shift(num_bits - 1);

    char bit_pos = 0;
    while (bit_pos < num_bits) {
        Integer quotient = remainder - divisor;
        bit_pos++;

        if (quotient.bitset[0] == '1') {
            remainder = remainder.left_shift(1);
        }
        else {
            remainder = quotient.left_shift(1);
        }

        remainder.bitset[num_bits - 1] = dividend.bitset[bit_pos];
    }

    return remainder.right_shift(1);
}

/* 
The division algorithm for / operator implement using above is divided into two steps:
1. Shift the upper bits of the dividend (the number we are dividing into) into the remainder.
2. Subtract the divisor from the value in the remainder. The high order bit of the result become a bit of the quotient (division result).
Source: http://bearcave.com/software/divide.htm#:~:text=The%20division%20algorithm%20is%20divided,the%20quotient%20(division%20result).
*/