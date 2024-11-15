#include <iostream>
#include "BittArray.h"

//хедеры и cpp


int main() {

    BitArray d;
    d.resize(31,true);
    std::cout<<d.to_string();

    return 0;
}
