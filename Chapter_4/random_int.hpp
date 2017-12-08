#include <iostream>

template <class T>
T generateRandomNumber(T startRange, T endRange)
{
    T randNum = startRange + (T)rand()/((T)RAND_MAX/(T)(endRange-startRange));
    return(randNum);
}
