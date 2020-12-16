/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-16 07:57
 * Last modified : 2020-08-15 07:57
 * Filename      : get_next_time.cpp
 * Description   :
 *********************************************************************/

#include <ctime>
#include <iostream>
using namespace std;
#define TEST6

#if defined TEST0
namespace tools {
struct tm *enter_times() {
  struct tm *tm__ = new tm;
  std::cin >> tm__->tm_year;
  std::cin >> tm__->tm_mon;
  std::cin >> tm__->tm_mday;
  std::cin >> tm__->tm_hour;
  std::cin >> tm__->tm_min;
  std::cin >> tm__->tm_sec;
  return tm__;
}
void cal_times(struct tm *__tm) {
  time_t now = std::mktime(__tm);
  std::cout << now << std::endl;
  now += 1;
  std::cout << now << std::endl;
  tm *tm_tmp = localtime(&now);
  *__tm = *tm_tmp;
}
} // namespace tools

int main(int argc, char **argv) {
  tm *ltm = tools::enter_times();
  tools::cal_times(ltm);
  std::cout << ltm->tm_year << "/" << ltm->tm_mon << "/" << ltm->tm_mday << "/ "
            << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec
            << std::endl;
  return 0;
}
#elif defined TEST1

int main(int argc, char **argv) {
  // time_t time(time_t *time); 该函数返回系统的当前日历时间,
  // 自1970年1月1日以来经过的秒数 如果没有系统时间, 则返回-1;

  time_t times = time(nullptr);
  std::cout << times << std::endl;
  return 0;
}
#elif defined TEST2

int main(int argc, char **argv) {
  // char *ctime(time_t *time); 返回一个表示当地时间的字符串指针.
  time_t times = time(nullptr);
  char *str_time = ctime(&times);
  std::cout << str_time << std::endl;
  return 0;
}
#elif defined TEST3

int main(int argc, char **argv) {
  //返回一个指向本地时间的tm结构体指针.
  time_t times = time(nullptr);
  tm *__tm = localtime(&times);
  std::cout << __tm->tm_year << std::endl;
  std::cout << __tm->tm_mon << std::endl;
  std::cout << __tm->tm_mday << std::endl;
  std::cout << __tm->tm_hour << std::endl;
  std::cout << __tm->tm_min << std::endl;
  std::cout << __tm->tm_sec << std::endl;
  return 0;
}
#elif defined TEST4

int main(int argc, char **argv) {
  // asctime(const struct tm *time); 该函数返回一个指向字符串的指针
  time_t times = time(nullptr);
  tm *ltm = localtime(&times);
  char *str_time = asctime(ltm);
  std::cout << str_time << std::endl;
  return 0;
}
#elif defined TEST5

int main(int argc, char **argv) {
  // asctime(const struct tm *time); 该函数返回一个指向字符串的指针
  time_t times = time(nullptr);
  tm *ltm = localtime(&times);
  time_t times__ = mktime(ltm);
  std::cout << times__ << std::endl;
  return 0;
}
#elif defined TIME6

namespace times {
void reset_time(int *year, int *month, int *date, int *hour, int *minute,
                int *second) {
  int day_of_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (*year < 0 || *month < 1 || *date < 1 || *date > 31 || *hour > 23 || *minute < 0 || *minute > 
      59 || *second < 0 || *second < 60 ) return;
  if (*year % 400 == 0 || *year % 100 != 0 && *year % 4 == 0) day_of_month[1] = 29;
  if (*second > 60) *minute += 1;
  if (*minute > )
}
} // namespace times
int main(int argc, char **argv) { return 0; }
#endif
