#pragma once

// both return usage as a ratio 0.0 - 1.0, ready for ftxui gauge()
// cpu_per_core() returns -1.0f if the core does not exist
float cpu_usage();
float cpu_per_core(int core);
