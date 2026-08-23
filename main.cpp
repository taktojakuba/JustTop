#include <iostream>
#include <fstream>
#include <string>
#include <array>

// include modules 
#include "modules/headers/example.h"

using namespace std;

int main(int argc, char* argv[])
{
  array<string, 1> modules = {
    "example: " + example(),
  };
  for(int i = 0;i<modules.size();i++){
    cout << modules[i] << endl;
  };
  
      return 0;
}
