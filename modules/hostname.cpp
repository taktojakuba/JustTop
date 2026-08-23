#include "headers/example.h"
#include <fstream>
#include <string>

using namespace std;

string example()
{
  string hostname;
  ifstream file("/etc/hostname");
  getline(file,hostname);
  return hostname;
}
