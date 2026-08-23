#include <chrono>
#include <ftxui/component/event.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <thread>

// ftxui
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

// include modules 
#include "modules/headers/example.h"
#include "modules/headers/cpu.h"

using namespace std;
using namespace ftxui;

int main(int argc, char* argv[])
{
  auto renderer = Renderer([&]{
  float total = cpu_usage();
  Elements lines = {
    hbox({
      text("cpu:  ") | border ,
      gauge(total) | flex,
      text(to_string((int)(total * 100 + 0.5f)) + "%") | border, 
    }) | border | flex
  };
  for(int c = 0;;c++){
    float usage = cpu_per_core(c);
    if(usage < 0) break;
    lines.push_back(hbox({
      text("cpu" + to_string(c) + ": ") | border,
      gauge(usage) | flex,
      text(to_string((int)(usage * 100 + 0.5f)) + "%") | border,
    }));
  }
  return vbox(lines) | border;
  });
  auto screen = ScreenInteractive::TerminalOutput();
  thread refresher([&]{
      while(true){
      this_thread::sleep_for(chrono::milliseconds(1000));
      screen.PostEvent(Event::Custom);
      }
      });
  screen.Loop(renderer);

  return 0;
}
