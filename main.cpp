#include <iostream>
#include <string>
#include <vector>

// include modules 
#include "modules/headers/example.h"

using namespace std;

int main(int argc, char* argv[])
{
  vector<string> modules = {
    "example: " + example(),
  };
  for(int i = 0;i<modules.size();i++){
    cout << modules[i] << endl;
  };
  
      return 0;
}
