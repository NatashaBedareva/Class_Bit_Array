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




int main() {
    BitArray d{35};

    //d.resize(10);

    d.set(2);
    d.set(3);
    d.set(5);
    d.set(20);
    d.set(25);
    d.set(31);
    d.set(32);

/*
    d.set(5);
    d.set(6);
    d.set(7);


    d.push_back(true);
    d.push_back(true);
    d.push_back(true);
    d.push_back(true);

    d.printBitArray();

    d.set();
    std::cout<<std::endl;
    d.push_back(false);

    d.reset(5);
    d.reset();

    d.printBitArray();

    d.printBitArray();
    std::cout<<"----"<<d.any()<<std::endl;

    std::cout<<"----"<<d.none()<<std::endl;


    (~d).printBitArray();
    std::cout<<d.count()<<"\n";

    std::cout<<d[30]<<"\n";
    std::cout<<d[3]<<"\n";
    std::cout<<d[4]<<"\n";
    std::cout<<d[8]<<"\n";
    std::cout<<d[32]<<"\n";
    std::cout<<d[31]<<"\n";

    d.resize(10);
    std::cout<<d.to_string()<<std::endl;
    d.resize(200,true);
    std::cout<<d.to_string();


    BitArray d2{35,200};

    d.set(1);
    d.set(2);
    d.set(4);
    d2.set(1);
    d2.set(4);
    std::cout<<d.to_string()<<"\n";
    std::cout<<d2.to_string()<<"\n";
    d^=d2;
    std::cout<<"\n";
    std::cout<<d.to_string()<<"\n";

    BitArray d3{35,210};
    BitArray d4{35,280};
    std::cout<<"---------------\n";
    std::cout<<d4.to_string()<<"\n";
    std::cout<<d3.to_string()<<"\n";
    std::cout<<(d4 ^ d3).to_string()<<"\n";
    */

    std::cout<<d.to_string()<<"\n";
    d>>=1;
    std::cout<<d.to_string()<<"\n";

    return 0;
}
