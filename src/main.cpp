#include "CapteurDataTransfert.h"
#include <esp_task_wdt.h>

static void IRAM_ATTR charge_detect_ISR();

CapteurDataTransfert *capteurDataTransfert = nullptr;

TaskHandle_t dataTransfertTask_handle;
[[noreturn]] static void dataTransferTask(void *pvParameters);

void setup() {
	Serial.begin(115200);
	Serial.println("Demarrage OS capteur...");

		xTaskCreatePinnedToCore(dataTransferTask, "DataTrans task", 20*1024, nullptr, 1, &dataTransfertTask_handle, 0);
	while(capteurDataTransfert == nullptr){ vTaskDelay(pdMS_TO_TICKS(500));}

	esp_task_wdt_init(2*60, true);
	esp_task_wdt_add(dataTransfertTask_handle);
	pinMode(PIN_CHARGE_DETECT, INPUT_PULLDOWN);
	attachInterrupt(PIN_CHARGE_DETECT, charge_detect_ISR, RISING);
}

void loop() {
	vTaskDelay(pdMS_TO_TICKS(10*1000));
	esp_task_wdt_reset();
}

static void IRAM_ATTR charge_detect_ISR(){
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(dataTransfertTask_handle, &pxHigherPriorityTaskWoken);
	if(pxHigherPriorityTaskWoken == pdTRUE){
		portYIELD_FROM_ISR();
	}
}

[[noreturn]] static void dataTransferTask(void *pvParameters){
	capteurDataTransfert = new CapteurDataTransfert();
	while(true){
		if(xTaskNotifyWait(UINT32_MAX, UINT32_MAX, nullptr, pdMS_TO_TICKS(60*1000)) == pdPASS){
			esp_task_wdt_reset();
			capteurDataTransfert->transfertData();
			vTaskDelay(pdMS_TO_TICKS(5*1000));
			ulTaskNotifyTake(UINT32_MAX, 1);
		}
		esp_task_wdt_reset();
	}
}