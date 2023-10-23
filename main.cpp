#include "main.hpp"

int main(int argc, char const *argv[])
{
    /*----------Initialisation Mersenne Twister----------*/
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, 
    length=4;
    init_by_array(init, length);
    //init_genrand(time(NULL));

    for (int i = 0; i < NUMBER_OF_YEAR; i++)
    {
        /*transition entre les categorys*/
    }

    return 0;
}
