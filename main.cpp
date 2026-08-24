#include <chrono>
#include <ftxui/component/event.hpp>
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <thread>
#include "modules/headers/linux-system-usage.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "modules/headers/cpu.h"

using namespace std;
using namespace ftxui;

int main(int argc, char* argv[])
{
  

  auto renderer = Renderer([&]{
  float total = cpu_usage();
  Elements lines = {};

  //overal cpu usage
  lines.push_back(hbox({
      text("cpu:  ") | border ,
      gauge(total),
      text(to_string((int)(total * 100 + 0.5f)) + "%") | border, 
    }) | border | flex
  );
  //cpu per core usage 
  for(int c = 0;;c++){
    float usage = cpu_per_core(c);
    if(usage < 0) break;
    lines.push_back(hbox({
      text("cpu" + to_string(c) + ": ") | border,
      gauge(usage) | flex,
      text(to_string((int)(usage * 100 + 0.5f)) + "%") | border,
    }) | border
    );
  }
  // demo: ram / swap / disk from linux-system-usage.hpp
  auto mem = read_memory_data();
  float ram = mem.get_memory_usage();
  float swap = mem.get_swap_usage();
  float disk = get_disk_usage("/");

  lines.push_back(hbox({
    text("ram:    "),
    gauge(ram),
    text(to_string((int)(ram * 100 + 0.5f)) + "%"),
  }) | border
  );
  lines.push_back(hbox({
    text("swap:   "),
    gauge(swap),
    text(to_string((int)(swap * 100 + 0.5f)) + "%"),
  }) | border
  );
  lines.push_back(hbox({
    text("disk /: "),
    gauge(disk),
    text(to_string((int)(disk * 100 + 0.5f)) + "%"),
  }) | border
  );

  // demo: cpu package temperature (milli-C -> C)
  int thermal_zone = find_thermalzone_index();
  int temp = get_thermalzone_temperature(thermal_zone) / 1000;
  lines.push_back(text("cpu temp: " + to_string(temp) + "C"));

  return vbox(lines) | border;
  });


  // render
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
