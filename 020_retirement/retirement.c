#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double endBalance(double c, double startBalance, double rate) {
  return startBalance + c + startBalance * rate;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double end = initial;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n",
           (startAge + i) / 12,
           (startAge + i) % 12,
           end);
    end = endBalance(working.contribution, end, working.rate_of_return);
  };
  int nowAge = working.months + startAge;
  for (int i = nowAge; i < nowAge + retired.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", i / 12, i % 12, end);
    end = endBalance(retired.contribution, end, retired.rate_of_return);
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
