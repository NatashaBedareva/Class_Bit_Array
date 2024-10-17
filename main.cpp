#include <iostream>
#include <vector>


class BitArray
{
    std::vector<unsigned long> bits_vector; // Вектор для хранения битов
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

  //Конструирует массив, хранящий заданное количество бит.
  //Первые sizeof(long) бит можно инициализровать с помощью параметра value.
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


  //Обменивает значения двух битовых массивов.
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


  //Изменяет размер массива. В случае расширения, новые элементы
  //инициализируются значением value.
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
  //Очищает массив.
  void clear()
  {
      bits_vector.clear();
      size_vector = 0;
  }
  //Добавляет новый бит в конец массива. В случае необходимости
  //происходит перераспределение памяти.
  void push_back(bool bit)
  {
      if ( size_vector/32 <  ((size_vector+1)/32) )
          bits_vector.push_back(0);

      this->set(size_vector,bit);
      size_vector++;
  }


  //Битовые операции над массивами.
  //Работают только на массивах одинакового размера.
  //Обоснование реакции на параметр неверного размера входит в задачу.
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
      // Проверка на совпадение размеров
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
      // Проверка на совпадение размеров
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

  //Битовый сдвиг с заполнением нулями.
  BitArray& operator<<=(int n);
  BitArray& operator>>=(int n);
  BitArray operator<<(int n) const;
  BitArray operator>>(int n) const;


  //Устанавливает бит с индексом n в значение val.
  BitArray& set(int n, bool val = true)
  {
      int id = int(n/32);
      if (val)
        bits_vector[id] = bits_vector[id] |= (1 << (n-id*32));
      else bits_vector[id] = bits_vector[id]  &= ~(1 << (n-id*32));
      return *this;
  }

  //Заполняет массив истиной.
  BitArray& set()
  {
      for(int i=0;i<=size_vector/32;i++)
      {
          bits_vector[i]=4294967295;
      }
      return *this;
  }


  //Устанавливает бит с индексом n в значение false.
  BitArray& reset(int n)
  {
      int id = int(n/32);
      bits_vector[id] = bits_vector[id]  &= ~(1 << (n-id*32));
      return *this;
  }
  //Заполняет массив ложью.
  BitArray& reset()
  {
      for(int i=0;i<=size_vector/32;i++)
      {
          bits_vector[i]=0;
      }
      return *this;
  }

  //true, если массив содержит истинный бит.
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
  //true, если все биты массива ложны.
  bool none() const
  {
      if (any())
          return false;
      return true;
  }
  //Битовая инверсия
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
  //Подсчитывает количество единичных бит.
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


  //Возвращает значение бита по индексу i.
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

  //Возвращает строковое представление массива.
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
    BitArray d{35,500};
    //d.resize(10);

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

    return 0;
}
