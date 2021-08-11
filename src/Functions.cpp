#include "../include/Chessman.hpp"

#include <stdexcept>

using namespace std;


// CheckRange fucntion
void checkRange(Chessman::Index index)
{
  if(index.first < 0 || index.first > 7 || index.second < 0 || index.second > 7)
    throw invalid_argument("positon must between 0, 7");
}
