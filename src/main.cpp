#include "CapteurDataTransfert.h"
#include <WiFi.h>
#include <esp_task_wdt.h>

static void IRAM_ATTR charge_detect_ISR();

CapteurDataTransfert *capteurDataTransfert = nullptr;

TaskHandle_t dataTransfertTask_handle;
[[noreturn]] static void dataTransferTask(void *pvParameters);

void setup() {
	Serial.begin(115200);
	Serial.println("Demarrage OS capteur...");
	WiFi.mode(WIFI_OFF);

	//Création de la tâche de transfert des données
	xTaskCreatePinnedToCore(dataTransferTask, "DataTrans task", 20*1024, nullptr, 1, &dataTransfertTask_handle, 0);
	while(capteurDataTransfert == nullptr){ vTaskDelay(pdMS_TO_TICKS(500));}

	//Initialistion du watchdog timer
	esp_task_wdt_init(2*60, true);
	esp_task_wdt_add(dataTransfertTask_handle);

	//Configuration des pins et de la LED
	pinMode(PIN_CHARGE_DETECT, INPUT);
	attachInterrupt(PIN_CHARGE_DETECT, charge_detect_ISR, RISING);
	pinMode(BUILTIN_LED, OUTPUT);
	digitalWrite(BUILTIN_LED, LOW);
}

void loop() {
	//On ne fait rien dans la boucle principale -> tout est géré dans la tâche Data transfert
	vTaskDelay(pdMS_TO_TICKS(10*1000));
	esp_task_wdt_reset();
}

/**
 * Interruption déclenchée lorsque l'on branche le capteur sur le socle (détection d'un front montant car
 * tension sur le port USB C de charge)
 */
static void IRAM_ATTR charge_detect_ISR(){
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	//Lorsque l'on reçoit l'interruption, on notifie la tâche Data transfert qu'il faut se synchroniser avec la base
	vTaskNotifyGiveFromISR(dataTransfertTask_handle, &pxHigherPriorityTaskWoken);
	if(pxHigherPriorityTaskWoken == pdTRUE){
		portYIELD_FROM_ISR();
	}
}

/**
 * Tâche gérant le transfert des données à la base
 * @param pvParameters : Non utilisé
 */
[[noreturn]] static void dataTransferTask(void *pvParameters){
	capteurDataTransfert = new CapteurDataTransfert();
	while(true){
		//Si on reçoit une notification, c'est qu'il faut se synchroniser avec la base
		if(xTaskNotifyWait(UINT32_MAX, UINT32_MAX, nullptr, pdMS_TO_TICKS(60*1000)) == pdPASS){
			esp_task_wdt_reset();
			capteurDataTransfert->transfertData();
			vTaskDelay(pdMS_TO_TICKS(5*1000));
			ulTaskNotifyTake(UINT32_MAX, 1);
		}
		esp_task_wdt_reset();
	}
}