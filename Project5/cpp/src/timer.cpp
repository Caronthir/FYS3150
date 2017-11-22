#include <iostream>
#include <ctime>
#include <chrono>
#include "timer.h"

void Timer::start(){
  // Save time points at startup (both wall time and cpu time)
    startWallTime = std::chrono::high_resolution_clock::now();
    startCPUTime  = std::clock();
}

void Timer::print(){
    // Print wall time and cpu time when called
    std::cout << "Wall time: " << wallTime().count() << "s\n"
              << "CPU time: " << CPUTime() << "s" << std::endl;
}

duration Timer::wallTime(){
  return (std::chrono::high_resolution_clock::now() - startWallTime);
}

clock_t Timer::CPUTime(){
  return (std::clock() - startCPUTime)/static_cast<double>(CLOCKS_PER_SEC);
}