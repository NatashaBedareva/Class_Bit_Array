
#include "BittArray.h"


    BitArray::BitArray()
    {
        size_vector=0;
    }
BitArray::~BitArray()
    {
        size_vector = 0;
    }

    //Constructs an array storing a specified number of bits.
    BitArray::BitArray(int num_bits, unsigned long value)
    {
        if(num_bits>32)
            for(int i=0;i<int(num_bits/32)+1;i++)
                bits_vector.push_back(value);
        else
            bits_vector.push_back(value);
        size_vector = num_bits;
    }

BitArray::BitArray(const BitArray& b)
    {
        bits_vector=b.bits_vector;
        size_vector=b.size_vector;
    }

    //Exchanges the values of two bit arrays.
    void BitArray::swap(BitArray& b)
    {
        std::swap(size_vector,b.size_vector);
        std::swap(bits_vector,b.bits_vector);
    }

    BitArray& BitArray::operator= (const BitArray& b)
    {
        if (this != &b) {
            bits_vector = b.bits_vector;
            size_vector = b.size_vector;
        }
        return *this;
    }

    //Changes the size of the array. In case of expansion, new elements
    //are initialized with the value value.
    void BitArray::resize(int num_bits, bool value)
    {

        if(size_vector==0 && num_bits<32)
        {
            bits_vector.resize(1);
        }

        if (!(int(size_vector/32)<=int((num_bits)/32) && int(num_bits/32)<(int(size_vector/32)+1)))
        {
            if (value)
                bits_vector.resize((int(num_bits)/32)+1,4294967295);
            else bits_vector.resize((int(num_bits)/32)+1,0);

            if(num_bits<size_vector)
            {
                for(int i = num_bits;i<size_vector;i++ )
                {
                    if(value)
                        this->set(i);
                    else
                        this->reset(i);
                }
            }
            else
            {
                for(int i = size_vector;i<num_bits;i++ )
                {
                    if(value)
                        this->set(i);
                    else
                        this->reset(i);
                }
            }

        }
        else
        {
            for(int i = num_bits;i<size_vector;i++ )
            {
                if(value)
                    this->set(i);
                else
                    this->reset(i);
            }

            for(int i = size_vector;i<num_bits;i++ )
            {
                if(value)
                    this->set(i);
                else
                    this->reset(i);
            }

        }
        size_vector=num_bits;
    }
    //Cleaning masiv
    void BitArray::clear()
    {
        bits_vector.clear();
        size_vector = 0;
    }
    //Adds a new bit to the end of the array. If necessary
    //memory is being redistributed.
    void BitArray::push_back(bool bit)
    {
        if ( size_vector/32 <  ((size_vector+1)/32) )
            bits_vector.push_back(0);

        this->set(size_vector,bit);
        size_vector++;
    }


    //Bit operations on arrays.
    //Only work on arrays of the same size.

    BitArray& BitArray::operator&=(const BitArray& b) {
        if (size_vector != b.size_vector) {
            throw std::invalid_argument("Sizes of BitArray must be the same.");
        }

        for (int i = 0; i < size_vector/32+1; i++) {

            bits_vector[i]=bits_vector[i] & b.bits_vector[i];
        }

        return *this;
    }

    BitArray& BitArray::operator|=(const BitArray& b)
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
    BitArray& BitArray::operator^=(const BitArray& b)
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
    BitArray& BitArray::operator<<=(int n)
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

    BitArray& BitArray::operator>>=(int n)
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
    BitArray BitArray::operator<<(int n) const
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
    BitArray BitArray::operator>>(int n) const
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
    BitArray& BitArray::set(int n, bool val)
    {
        int id = int(n/32);
        if (val)
            bits_vector[id] = bits_vector[id] |= (1 << (n-id*32));
        else bits_vector[id] = bits_vector[id]  &= ~(1 << (n-id*32));
        return *this;
    }

    //Fills the array with the truth.
    BitArray& BitArray::set()
    {
        for(int i=0;i<=size_vector/32;i++)
        {
            bits_vector[i]=4294967295;
        }
        return *this;
    }


    //Sets the bit with index n to false.
    BitArray& BitArray::reset(int n)
    {
        int id = int(n/32);
        bits_vector[id] = bits_vector[id]  &= ~(1 << (n-id*32));
        return *this;
    }
    //Fills the array with a lie.
    BitArray& BitArray::reset()
    {
        for(int i=0;i<=size_vector/32;i++)
        {
            bits_vector[i]=0;
        }
        return *this;
    }

    //true if the array contains a true bit.
    bool BitArray::any() const
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
    bool BitArray::none() const
    {
        if (any())
            return false;
        return true;
    }
//Bit inversion
    BitArray BitArray::operator~() const
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
    int BitArray::count() const
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
    bool BitArray::operator[](int i) const
    {
        unsigned long N = bits_vector[i/32];
        return ((N >> i) & 1);
    }

    int BitArray::size() const
    {
        return size_vector;
    }

    bool BitArray::empty() const
    {
        return ((size_vector==0) ? true : false);
    }

//Returns the string representation of the array.
    std::string BitArray::to_string() const
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

