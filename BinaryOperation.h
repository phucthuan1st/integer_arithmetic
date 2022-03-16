#include <iostream>

using namespace std;

#define num_bits 8

class Integer {
    private:
        //the int will be store as a 8-bit set (simulation with a 8-byte char array
        char* bitset; 
    public:
        //constructor
        Integer(const char* = "00000000");
        Integer(int = 0);

        //getter
        char decimal();
        char* binary();

        //relative components
        Integer two_complement();
        Integer left_shift(char);
        Integer right_shift(char);

        //output method
        void print(bool binary = true, bool decimal = true);
    
    public: //operator overload
        friend Integer operator + (const Integer&, const Integer&);
        friend Integer operator - (const Integer&, Integer&);
        friend Integer operator * (const Integer&, Integer&);
        friend Integer operator / (Integer&, Integer&);
};