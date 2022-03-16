# Integer Arithmetic
Binary integer operation simulation with C++/C

Hi all!

I conplete thís project in 2 days, so the code will not too clean in some way, but it run ok

# Describe
* First for the add operation (as + operator): I used the plus as human thinking by if clause (8 case at all)
* For the subtract operation (as - operator): I used the logic about adding the two's complement of the subtractor
* For the multiply operation (as * operator): I combined left shift bit with add operation as logic
* For the division operatiob (as / operator): This is the most comlicated things on this project, so I will describe below.

# About the binary division:
The division algorithm is divided into two steps:
1. Shift the upper bits of the dividend (the number we are dividing into) into the remainder.
2. Subtract the divisor from the value in the remainder. The high order bit of the result become a bit of the quotient (division result).
Sources: http://bearcave.com/software/divide.htm#:~:text=The%20division%20algorithm%20is%20divided,the%20quotient%20(division%20result).

```C++
    Integer result(0);
    char bit_pos = 0;
    Integer remainder = dividend.right_shift(num_bits - 1);

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
    
```
