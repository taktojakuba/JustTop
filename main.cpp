#include <iostream>
#include <string>
#include <vector>

// ftxui
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

// include modules 
#include "modules/headers/example.h"

using namespace std;
using namespace ftxui;

int main(int argc, char* argv[])
{
  vector<string> modules = {
    "example: " + example(),
  };

  // build lines out of module strings
  Elements lines;
  for(size_t i = 0;i<modules.size();i++){
    lines.push_back(text(modules[i]));
  }

  // static one-shot render
  auto document = vbox(lines) | border;
  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);
  cout << screen.ToString() << endl;

  return 0;
}
