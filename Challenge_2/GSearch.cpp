/*******************************************************
*   Grady Shepherd
*   Software Optimization
*   Genome Search Utility
*   Due: October 30, 2017 at 2:40 p.m.
********************************************************/

//You can show my time in class

#include <iostream>
#include <vector>
#include <fstream>
//#include "Clock.hpp"
#include "../Clock.hpp"

int main(int argc, char **argv)
{

    // For both of us, let's see if there's a more efficient way
    // to reduce the amount of code in this declaration block.

    std::vector<std::string> shortReads;
    std::size_t foundIndex;
    std::string shortReadStr;
    std::string genomeStr;
    std::ifstream genomeFile;
    std::ifstream shortReadFile;

    genomeFile.open(argv[1]);
    shortReadFile.open(argv[2]);

    genomeFile >> genomeStr;

    // This is interesting. I haven't seen this way of reading in files,
    // but I'd like to compare it to mine (I used getline) and see which is
    // faster. It seems to be akin to "piping" the input.
    while (shortReadFile >> shortReadStr)
    {
        shortReads.push_back(shortReadStr);
    }

    Clock c;

    // I'd recommend breaking this out as a seperate function. First for readability,
    // and second so you can leverage const when iterating over the genome with the reads.
    // As neither the genome or reads mutate during runtime, they can benefit from a
    // const declaration.
    for(long i = 0; i < shortReads.size(); ++i)
    {
        foundIndex = 0;

        // Printing out during runtime might be slowing your program in searching.
        // Consider first finding (and storing) character, then printing your
        // results to improve code redability and to let the computer focus
        // on a given type of operation (searching the indexes of the genome)
        // before printing out the results.
        std::cout << shortReads.at(i) << " ";
        //search through until no more instances of short read are found

        // Consider switching out the use of .at(i) by changing the outer
        // for loop to one that uses auto! It should prevent little bits of
        // overhead from calling the method from impacting performance,
        // and also make this code even more concise.
        while(genomeStr.find(shortReads.at(i), foundIndex) <= genomeStr.length())
        {
            // Also, kudos for using find. I'd find a way to reduces calls to
            // find by storing the current position in a variable, then only
            // calling find when an update to that position variable is
            // required.
            foundIndex = genomeStr.find(shortReads.at(i), foundIndex);
            std::cout << foundIndex;

            //move foundIndex so that the same will not be found multiple times

            // Good on you for using std::size_t! It's a super effecient
            // data type that allows for possible bit-wise parallism when
            // the compiler sees it.
            foundIndex += (std::size_t)shortReads.at(i).length();

            //print space after each index until the last

            // This if statement seems unnecessary, as it only controls where the
            // whitespace is printed, and likely ends up slowing down each loop
            // a significant amount (as you perform an additional find and a comparison
            // in the if statment).
            if(genomeStr.find(shortReads.at(i), foundIndex) < genomeStr.length())
            {
                std::cout << " ";
            }
        }
    }

    std::cout << std::endl;
    c.ptock();
}
