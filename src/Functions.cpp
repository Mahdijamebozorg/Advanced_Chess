#include "../include/Chessman.hpp"
#include "random"
#include <stdexcept>

using namespace std;

//CheckRange fucntion
void checkRange(Chessman::Index index)
{
  if(index.first < 0 || index.first > 7 || index.second < 0 || index.second > 7)
      throw out_of_range("positon must between 0, 7");
}
long unsigned randomNum()
{
    static mt19937 generator{random_device{}()}; //random engine

    uniform_int_distribution<long> distribution{0, 1000000000}; // range

    return distribution(generator);
}
