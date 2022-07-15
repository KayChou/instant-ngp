#pragma once

#include <sys/time.h>

#include <iostream>

#define DEBUG_TIME 1


class Latency_profile {

    float getTimeDiffMS(timeval start, timeval end) {
        long time_ms_end  = (end.tv_sec * 1000000 + end.tv_usec);
        long time_ms_start = (start.tv_sec * 1000000 + start.tv_usec);
        return float(time_ms_end - time_ms_start) / 1000;
    }

private:
    timeval t_start;
    timeval t_end;

    int cnt = 0;
    float avg_latency = 0;
    int start_frame = 0;

    char module_name[128];

public:
    Latency_profile() {
        cnt = 0;
        avg_latency = 0;
        start_frame = 0;
    }

    Latency_profile(char* module_name) {
        strcpy(this->module_name, module_name);
    }

    void tick() {
        gettimeofday(&t_start, NULL);
    }

    void tock() {
        gettimeofday(&t_end, NULL);

        if(cnt >= start_frame) avg_latency += getTimeDiffMS(t_start, t_end);
        cnt++;
    }

    void print_log() {
        if(cnt >= start_frame) {
            avg_latency /= (cnt - start_frame + 1);
        }
        std::cout << "Latency of " << std::setw(20) << std::setiosflags(std::ios::right) << module_name << ": " << std::setw(15) << std::setiosflags(std::ios::right) << avg_latency << " ms" << std::endl;
    }
};