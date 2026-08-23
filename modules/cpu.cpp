#include "headers/cpu.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

const int SAMPLE_MS = 1000;

static vector<vector<long>> read_cpu_lines()
{
  vector<vector<long>> result;
  ifstream file("/proc/stat");
  string line;
  while(getline(file,line))
  {
    if(line.rfind("cpu",0) != 0) continue;  
    stringstream ss(line);
    string name;
    ss >> name;                          
    vector<long> times;
    long value;
    while(ss >> value) times.push_back(value);
    result.push_back(times);
  }
  return result;
}


static int usage_between(const vector<long>& prev, const vector<long>& cur)
{
  long prev_idle = prev[3] + prev[4];
  long cur_idle  = cur[3] + cur[4];

  long prev_total = 0;
  long cur_total = 0;
  for(size_t i = 0;i<prev.size();i++) prev_total += prev[i];
  for(size_t i = 0;i<cur.size();i++)  cur_total += cur[i];

  long total_delta = cur_total - prev_total;
  long idle_delta  = cur_idle  - prev_idle;
  if(total_delta <= 0) return 0;
  return (total_delta - idle_delta) * 100 / total_delta;  
}

float cpu_usage()
{
  static vector<long> prev;
  vector<vector<long>> all = read_cpu_lines();
  if(all.empty()) return 0.0f;
  if(prev.empty()){                         
    prev = all[0];
    this_thread::sleep_for(chrono::milliseconds(SAMPLE_MS));
    all = read_cpu_lines();
  }
  int percent = usage_between(prev, all[0]);
  prev = all[0];
  return percent / 100.0f;
}

float cpu_per_core(int core)
{
  static vector<vector<long>> prev;
  int line = core + 1;                     

  vector<vector<long>> all = read_cpu_lines();
  if(line >= (int)all.size()) return -1.0f;    
  if(prev.empty()){                        
    prev = all;
    this_thread::sleep_for(chrono::milliseconds(SAMPLE_MS));
    all = read_cpu_lines();
  }
  int percent = usage_between(prev[line], all[line]);
  prev = all;
  return percent / 100.0f;
}
