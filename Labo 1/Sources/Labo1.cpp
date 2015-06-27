/*============================================================================
 * Name        : Labo1.cpp
 * Date        : 12 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Permet d'utiliser et de vérifier le code produit dans ce labo
 *============================================================================*/

#include <time.h>

#include "Labo1_tools.h"

int main()
{
    clock_t tick;
    
   // std::string filenameIn  = "input_nddp.txt";
    std::string filenameIn  = "input_nddp.txt";
    std::string filenameComp = "tmp_simple.txt";
    std::string filenameOut  = "output_simple.txt";

    std::cout << "Compression en cours..." << std::endl;
    tick = clock();
    compresser(filenameIn, filenameComp);
    std::cout << "Temps de compression: " << ((double)clock() - tick) / CLOCKS_PER_SEC << " sec." << std::endl;
    
    std::cout << "Decompression en cours..." << std::endl;
    tick = clock();
    decompresser(filenameComp, filenameOut);
    std::cout << "Temps de decompression: " << ((double)clock() - tick) / CLOCKS_PER_SEC << " sec." << std::endl;
    
    return EXIT_SUCCESS;
    
}
