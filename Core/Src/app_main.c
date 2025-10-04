#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

QueueHandle_t adcQueue;

void LED_Task1(void *arg)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(300));
        HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_7);
    }
}

void LED_Task0(void *arg)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    }
}

void ADC_Task(void *arg)
{
    static uint32_t adc_value;
    static char send_buf[32];
    while (1)
    {
        HAL_ADC_Start(&hadc1);
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            adc_value = HAL_ADC_GetValue(&hadc1);
            xQueueSend(adcQueue, &adc_value, 0);
        }
        HAL_ADC_Stop(&hadc1);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void UART_Task(void *arg)
{
    static uint32_t adc_buf = 0;
    static char send_buf[32];
    while (1)
    {
        if (xQueueReceive(adcQueue, &adc_buf, 0) == pdTRUE)
        {
            snprintf(send_buf, sizeof(send_buf), "%ldmV\r\n", adc_buf * 3300 / 4095);
            HAL_UART_Transmit(&huart1, (uint8_t *)send_buf, strlen(send_buf) + 1, 100);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    adcQueue = xQueueCreate(5, sizeof(uint32_t));
    xTaskCreate(LED_Task0, "LED0", 512, NULL, 10, NULL);
    xTaskCreate(LED_Task1, "LED1", 512, NULL, 10, NULL);
    xTaskCreate(ADC_Task, "ADC", 1024, NULL, 15, NULL);
    xTaskCreate(UART_Task, "UART", 1024, NULL, 15, NULL);
}
