

#ifndef BIT_ARRAY_BITTARRAY_H
#define BIT_ARRAY_BITTARRAY_H


#include <iostream>
#include <vector>
#include <string>

class BitArray
{
    std::vector<unsigned long> bits_vector; // Vector for storing bits
    int size_vector;
public:

    BitArray();
    ~BitArray();


    //Constructs an array storing a specified number of bits.
    BitArray(int num_bits, unsigned long value = 0);

    BitArray(const BitArray& b);
    //Exchanges the values of two bit arrays.
    void swap(BitArray& b);

    BitArray& operator= (const BitArray& b);

    //Changes the size of the array. In case of expansion, new elements
    //are initialized with the value value.
    void resize(int num_bits, bool value = false);
    //Cleaning masiv
    void clear();
    //Adds a new bit to the end of the array. If necessary
    //memory is being redistributed.
    void push_back(bool bit);

    //Bit operations on arrays.
    //Only work on arrays of the same size.

    BitArray& operator&=(const BitArray& b);

    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    //A zero-filled bit shift.
    BitArray& operator<<=(int n);

    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    //Sets the bit with index n to val.
    BitArray& set(int n, bool val = true);

    //Fills the array with the truth.
    BitArray& set();


    //Sets the bit with index n to false.
    BitArray& reset(int n);
    //Fills the array with a lie.
    BitArray& reset();

    //true if the array contains a true bit.
    bool any() const;
//true if all the bits of the array are false.
    bool none() const;
//Bit inversion
    BitArray operator~() const;
//Counts the number of single bits.
    int count() const;


//Returns the value of the bit at index i.
    bool operator[](int i) const;

    int size() const;

    bool empty() const;

//Returns the string representation of the array.
    std::string to_string() const;
};

bool operator==(const BitArray & a, const BitArray & b);
bool operator!=(const BitArray & a, const BitArray & b);

BitArray operator&(const BitArray& b1, const BitArray& b2);

BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);




#endif //BIT_ARRAY_BITTARRAY_H
