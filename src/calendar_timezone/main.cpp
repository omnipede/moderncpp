#include <iostream>
#include <chrono>

// Calendar & time zone

int main() {
    // - time point
    // - time duration
    // - clock

    // C++11 chrono
    // C++20 calendar, time_zone
    // auto timeOfDay = std::chrono::hh_mm_ss(10.5h + 32min + 1004s + 0.6s);
    // std::chrono::year_month_day ymd{ 2021y, November, 14d };
    // std::chrono::year_month_day_last ymdl = 2021y / November / last;

    // Validation
    // std::chrono::day d{31};
    // d++;
    // bool valid = d.ok();

    // UTC (협정 세계시) <--> Local time
    // - 영국: UTC+0 (GMT)
    // - 한국: UTC+9 (KST)
    // auto utc_time = std::chrono::system_clock::now();
    // std::cout << utc_time << std::endl;
    // auto local_time = std::chrono::zoned_time(std::chrono::current_zone(), utc_time);
    // auto local_time = std::chrono::zoned_time("Asia/Shanghai"s, utc_time);

    // Unix epoch (1970년 1월 1일 UTC) 시간으로부터 얼마나 지났는지
    // utc_time.time_since_epoch()
}
