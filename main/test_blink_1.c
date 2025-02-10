#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    //Initializing GPIO4 as input with a pull up.
    gpio_set_direction(GPIO_NUM_4,GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_4,GPIO_PULLUP_ONLY);

    gpio_set_direction(GPIO_NUM_5,GPIO_MODE_OUTPUT);
    
    while(true){
        if(gpio_get_level(GPIO_NUM_4)){
            gpio_set_level(GPIO_NUM_5,0);
        }else{
            gpio_set_level(GPIO_NUM_5,1);
        }

        vTaskDelay(10);
    }
}
