// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdio>

#include "libs/base/led.h"
#include "libs/base/tasks.h"
#include "third_party/freertos_kernel/include/FreeRTOS.h"
#include "third_party/freertos_kernel/include/task.h"

[[noreturn]] void blink_task(void* param) {
  auto led_type = static_cast<coralmicro::Led*>(param);
  bool on = true;
  while (true) {
    on = !on;
    coralmicro::LedSet(*led_type, on);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

extern "C" void app_main(void* param) {
  (void)param;
  auto user_led = coralmicro::Led::kUser;
  xTaskCreate(&blink_task, "blink_user_led_task", configMINIMAL_STACK_SIZE,
              &user_led, coralmicro::kAppTaskPriority, nullptr);
  vTaskSuspend(nullptr);
}
