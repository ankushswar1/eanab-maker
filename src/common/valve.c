#include "valve.h"
#include "storage.h"
#include "malloc.h"
#include "printf.h"
#include "strings.h"
#include "gpio.h"
#include "timer.h"

#define TIME_TOTAL 8000
#define TIME_DELAY 50

static unsigned int valves[4];

void valves_init(unsigned int pin_1, unsigned int pin_2, unsigned int pin_3, unsigned int pin_4) {
    valves[0] = pin_1;
    valves[1] = pin_2;
    valves[2] = pin_3;
    valves[3] = pin_4;

    gpio_set_output(pin_1);
    gpio_set_output(pin_2);
    gpio_set_output(pin_3);
    gpio_set_output(pin_4);
}

void test_on_off() {
  while (1) {

    for (int i = 0; i < 4; i++) {
      gpio_write(valves[i], 1);
    }

    timer_delay(1);

    for (int i = 0; i < 4; i++) {
      gpio_write(valves[i], 0);
    }
    timer_delay(1);
  }
}

void turn_on_valves(int time_1, int time_2, int time_3, int time_4) {
  for (int i = 0; i < 4; i++) {
    gpio_write(valves[i], 1);
  }

  // int time_1 = ingredients[0];
  // int time_2 = ingredients[1];
  // int time_3 = ingredients[2];
  // int time_4 = ingredients[3];

// time_1 > 0 || time_2 > 0 || time_3 > 0 || time_4 > 0
  while (time_1 > 0 || time_2 > 0 || time_3 > 0 || time_4 > 0) {
    time_1--;
    time_2--;
    time_3--;
    time_4--;
    printf("Time 1: %d\n", time_1);
    printf("Time 2: %d\n", time_2);
    printf("Time 3: %d\n", time_3);
    printf("Time 4: %d\n", time_4);

    if (time_1 == 1) {
      gpio_write(valves[0], 0);
    }

    if (time_2 == 1) {
      gpio_write(valves[1], 0);
    }

    if (time_3 == 1) {
      gpio_write(valves[2], 0);
    }

    if (time_4 == 1) {
      gpio_write(valves[3], 0);
    }

    timer_delay_ms(TIME_DELAY);
  }
}
