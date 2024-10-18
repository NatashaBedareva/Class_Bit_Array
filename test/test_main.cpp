#include <gtest/gtest.h>
#include <iostream>
#include <vector>


class BitArray
{
    std::vector<unsigned long> bits_vector; // Vector for storing bits
    int size_vector;
public:

    BitArray()
    {
        size_vector=0;
    }
    ~BitArray()
    {
        size_vector = 0;
    }

    //Constructs an array storing a specified number of bits.
    explicit BitArray(int num_bits, unsigned long value = 0)
    {
        if(num_bits>32)
            for(int i=0;i<int(num_bits/32)+1;i++)
                bits_vector.push_back(value);
        else
            bits_vector.push_back(value);
        size_vector = num_bits;
    }

    BitArray(const BitArray& b)
    {
        bits_vector=b.bits_vector;
        size_vector=b.size_vector;
    }

    //Exchanges the values of two bit arrays.
    void swap(BitArray& b)
    {
        std::swap(size_vector,b.size_vector);
        std::swap(bits_vector,b.bits_vector);
    }

    BitArray& operator= (const BitArray& b)
    {
        if (this != &b) {
            bits_vector = b.bits_vector;
            size_vector = b.size_vector;
        }
        return *this;
    }


    //Changes the size of the array. In case of expansion, new elements
    //are initialized with the value value.
    void resize(int num_bits, bool value = false)
    {
        if (!(int(size_vector/32)<=int((num_bits)/32) && int(num_bits/32)<(int(size_vector/32)+1)))
        {
            if (value)
                bits_vector.resize((int(num_bits)/32)+1,4294967295);
            else bits_vector.resize((int(num_bits)/32)+1,0);
        }
        size_vector=num_bits;
    }
    //Cleaning masiv
    void clear()
    {
        bits_vector.clear();
        size_vector = 0;
    }
    //Adds a new bit to the end of the array. If necessary
    //memory is being redistributed.
    void push_back(bool bit)
    {
        if ( size_vector/32 <  ((size_vector+1)/32) )
            bits_vector.push_back(0);

        this->set(size_vector,bit);
        size_vector++;
    }


    //Bit operations on arrays.
    //Only work on arrays of the same size.

    BitArray& operator&=(const BitArray& b) {
        if (size_vector != b.size_vector) {
            throw std::invalid_argument("Sizes of BitArray must be the same.");
        }

        for (int i = 0; i < size_vector/32+1; i++) {

            bits_vector[i]=bits_vector[i] & b.bits_vector[i];
        }

        return *this;
    }

    BitArray& operator|=(const BitArray& b)
    {
        if (size_vector != b.size_vector) {
            throw std::invalid_argument("Sizes of BitArray must be the same.");
        }

        for (int i = 0; i < size_vector; i++) {
            unsigned long N = bits_vector[i / 32];
            int r = (N >> (i % 32)) & 1;

            if (r == 1 || b[i] == 1)
                this->set(i);
            else
                this->reset(i);

        }
        return *this;
    }
    BitArray& operator^=(const BitArray& b)
    {
        if (size_vector != b.size_vector) {
            throw std::invalid_argument("Sizes of BitArray must be the same.");
        }

        for (int i = 0; i < size_vector; i++) {
            unsigned long N = bits_vector[i / 32];
            int r = (N >> (i % 32)) & 1;

            if ((r == 1 && b[i] == 0) || (r == 0 && b[i] == 1)) {
                this->set(i);
            } else {
                this->reset(i);
            }
        }
        return *this;
    }

    //A zero-filled bit shift.
    BitArray& operator<<=(int n)
    {
        bool f=false;
        int g=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=size_vector/32;j++)
            {
                unsigned long gran_bit = bits_vector[j] & 2147483648;
                BitArray nnn{size_vector,gran_bit};
                if (nnn.any() && (j+1)<=size_vector)
                {
                    f=true;
                    g=j;
                }
                bits_vector[j] = bits_vector[j]<<1;
                if (f && (g+1)==j)
                {
                    bits_vector[j] |=1;
                    f=false;
                }
            }

        }
        return *this;
    }

    BitArray& operator>>=(int n)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=size_vector/32;j++)
            {
                unsigned long gran_bit = bits_vector[j] & 1;
                BitArray nnn{size_vector,gran_bit};
                if (nnn.any() && (j-1)<=size_vector && j-1>=0)
                {
                    bits_vector[j-1] |=2147483648;
                }
                bits_vector[j] = bits_vector[j]>>1;
            }
        }
        return *this;
    }
    BitArray operator<<(int n) const
    {
        BitArray new_arr;
        new_arr=*this;
        bool f=false;
        int g=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=new_arr.size_vector/32;j++)
            {
                unsigned long gran_bit = new_arr.bits_vector[j] & 2147483648;
                BitArray nnn{new_arr.size_vector,gran_bit};
                if (nnn.any() && (j+1)<=new_arr.size_vector)
                {
                    f=true;
                    g=j;
                }
                new_arr.bits_vector[j] = new_arr.bits_vector[j]<<1;
                if (f && (g+1)==j)
                {
                    new_arr.bits_vector[j] |=1;
                    f=false;
                }
            }

        }
        return new_arr;
    }
    BitArray operator>>(int n) const
    {
        BitArray new_arr;
        new_arr=*this;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=new_arr.size_vector/32;j++)
            {
                unsigned long gran_bit = new_arr.bits_vector[j] & 1;
                BitArray nnn{new_arr.size_vector,gran_bit};
                if (nnn.any() && (j-1)<=new_arr.size_vector && j-1>=0)
                {
                    new_arr.bits_vector[j-1] |=2147483648;
                }
                new_arr.bits_vector[j] = new_arr.bits_vector[j]>>1;
            }
        }
        return new_arr;
    }


    //Sets the bit with index n to val.
    BitArray& set(int n, bool val = true)
    {
        int id = int(n/32);
        if (val)
            bits_vector[id] = bits_vector[id] |= (1 << (n-id*32));
        else bits_vector[id] = bits_vector[id]  &= ~(1 << (n-id*32));
        return *this;
    }

    //Fills the array with the truth.
    BitArray& set()
    {
        for(int i=0;i<=size_vector/32;i++)
        {
            bits_vector[i]=4294967295;
        }
        return *this;
    }


    //Sets the bit with index n to false.
    BitArray& reset(int n)
    {
        int id = int(n/32);
        bits_vector[id] = bits_vector[id]  &= ~(1 << (n-id*32));
        return *this;
    }
    //Fills the array with a lie.
    BitArray& reset()
    {
        for(int i=0;i<=size_vector/32;i++)
        {
            bits_vector[i]=0;
        }
        return *this;
    }

    //true if the array contains a true bit.
    bool any() const
    {
        for(int i=0; i<size_vector;i++)
        {
            unsigned long N = bits_vector[i/32];
            int id = int(i/32);
            if(  ((N >> (i-id*32)) & 1) )
                return true;
        }
        return false;
    }
//true if all the bits of the array are false.
    bool none() const
    {
        if (any())
            return false;
        return true;
    }
//Bit inversion
    BitArray operator~() const
    {
        BitArray new_arr{this->size_vector};

        for(int i=0; i<size_vector;i++)
        {
            unsigned long N = bits_vector[i/32];
            int id = int(i/32);
            if(  ((N >> (i-id*32)) & 1) )
                new_arr.reset(i);
            else new_arr.set(i);
        }
        return new_arr;
    }
//Counts the number of single bits.
    int count() const
    {
        int count=0;
        for(int i=0; i<size_vector;i++)
        {
            unsigned long N = bits_vector[i/32];
            int id = int(i/32);
            if(  ((N >> (i-id*32)) & 1) )
                count++;
        }
        return count;
    }


//Returns the value of the bit at index i.
    bool operator[](int i) const
    {
        unsigned long N = bits_vector[i/32];
        return ((N >> i) & 1);
    }

    int size() const
    {
        return size_vector;
    }

    bool empty() const
    {
        return ((size_vector==0) ? true : false);
    }

//Returns the string representation of the array.
    std::string to_string() const
    {
        std::string str="";
        for(int i=0; i<size_vector;i++)
        {
            unsigned long N = bits_vector[i/32];
            int id = int(i/32);
            if(  ((N >> (i-id*32)) & 1) )
                str+='1';
            else str+='0';
        }
        return str;
    }
};

bool operator==(const BitArray & a, const BitArray & b)
{
    if (a.size()==b.size())
    {
        for(int i=0;i<a.size();i++)
            if(a[i]!=b[i]) return false;
        return true;
    }

    return false;
}
bool operator!=(const BitArray & a, const BitArray & b)
{
    return !(a==b);
}
BitArray operator&(const BitArray& b1, const BitArray& b2)
{
    BitArray new_b{b1.size()};
    new_b =b1;
    new_b &= b2;
    return new_b ;
}
BitArray operator|(const BitArray& b1, const BitArray& b2)
{
    BitArray new_b{b1.size()};
    new_b =b1;
    new_b |= b2;
    return new_b ;
}
BitArray operator^(const BitArray& b1, const BitArray& b2)
{
    BitArray new_b{b1.size()};
    new_b =b1;
    new_b ^= b2;
    return new_b ;
}


TEST(TestBitsArray,TestSwap) {
    BitArray d{10,5};
    BitArray d2{15,7};

    d.swap(d2);

    EXPECT_EQ(d.size(), 15);
    EXPECT_EQ(d2.size(), 10);

    EXPECT_TRUE(d.to_string()=="111000000000000");
}

TEST(TestBitsArray,TestResize) {
    BitArray d{10,5};
    d.resize(40,true);

    EXPECT_EQ(d.size(), 40);
    EXPECT_TRUE(d.to_string()=="1010000000000000000000000000000011111111");
    d.resize(5);
    EXPECT_EQ(d.size(), 5);
    EXPECT_TRUE(d.to_string()=="10100");

}
TEST(TestBitsArray,TestPushBack) {
    BitArray d{10,5};
    d.push_back(true);

    EXPECT_EQ(d.size(), 11);
    EXPECT_TRUE(d.to_string()=="10100000001");

    d.resize(31);
    d.push_back(true);
    EXPECT_EQ(d.size(), 32);
    EXPECT_TRUE(d.to_string()=="10100000001000000000000000000001");
}

TEST(TestBitsArray,TestSet) {
    BitArray d{33};
    d.set(3);
    std::cout<<d.to_string();
    EXPECT_TRUE(d.to_string()=="000100000000000000000000000000000");
    d.set();
    EXPECT_TRUE(d.to_string()=="111111111111111111111111111111111");
}

TEST(TestBitsArray,TestReset) {
    BitArray d{10};
    d.set();
    d.reset(5);
    EXPECT_TRUE(d.to_string()=="1111101111");
    d.reset();
    EXPECT_TRUE(d.to_string()=="0000000000");
}

TEST(TestBitsArray,TestAnyNone) {
    BitArray d{10};
    d.set(2);
    EXPECT_TRUE(d.any());
    d.reset(2);
    EXPECT_FALSE(d.any());

    EXPECT_TRUE(d.none());
}

TEST(TestBitsArray,TestCount) {
    BitArray d{50};
    d.set(2);
    d.set(10);
    d.set(32);
    d.set(40);
    d.set(45);

    EXPECT_EQ(d.count(),5);
}

TEST(TestBitsArray,TestEmptyClear) {
    BitArray d{50};
    d.set(2);
    d.set(10);
    d.set(32);
    d.set(40);
    d.set(45);
    d.clear();

    EXPECT_TRUE(d.empty());
}

TEST(TestBitsArray,TestIndex) {
    BitArray d{50};
    d.set(2);
    d.set(10);
    d.set(32);
    d.set(40);
    d.set(45);

    EXPECT_EQ(d[2],1);
    EXPECT_EQ(d[0],0);
    EXPECT_EQ(d[32],1);
}

TEST(TestBitsArray,TestOperatorBit) {
    BitArray d{10};
    d.set(2);
    d.set(5);
    d.set(4);
    BitArray d2{10};
    d2.set(4);
    d2.set(7);

    EXPECT_TRUE((d|d2).to_string()=="0010110100");
    d&=d2;
    EXPECT_TRUE(d.to_string()=="0000100000");

    BitArray d3{35};
    d3.set(31);
    d3.set(2);
    d3.set(3);
    d3.set(10);
    d3.set(34);
    EXPECT_TRUE((d3>>3).to_string()=="10000001000000000000000000001001000");
    d3<<=5;
    EXPECT_TRUE(d3.to_string()=="00000001100000010000000000000000000");

}

