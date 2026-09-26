#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t messageQueue;

void producerA( void *pvParameters ){
    while(1){
        const char *message = "Task one is working";
        xQueueSend(messageQueue, &message, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void producerB( void *pvParameters){
    while(1){
        const char *message = "Task two is working";
        xQueueSend(messageQueue, &message, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

void consumer(void *pvParameters){
    while(1){
        const char *message;
        if(uxQueueMessagesWaiting(messageQueue) > 0 && xQueueReceive(messageQueue, &message, 0) == pdPASS){
            Serial.println(message);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


void setup() {
  Serial.begin(9600);
  messageQueue = xQueueCreate(10, sizeof(const char *));

  if (messageQueue == nullptr) {
    while (true) {
    }
  }

  xTaskCreate(consumer, "Consumer", 128, nullptr, 1, nullptr);
  xTaskCreate(producerA, "ProducerA", 128, nullptr, 1, nullptr);
  xTaskCreate(producerB, "ProducerB", 128, nullptr, 1, nullptr);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
}
