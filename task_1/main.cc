#include "Image.h"
#include "Parser.h"

#include <iostream> 
#include <string> 


int main(int argc, char** argv)
{
 
    using namespace std;
    
    Parser p(argc, argv);
    if (p.setBrightness())
        cout << p.setBrightness();
    return 0;
}
