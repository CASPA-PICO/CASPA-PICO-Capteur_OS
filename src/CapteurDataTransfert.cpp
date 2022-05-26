#include "CapteurDataTransfert.h"

CapteurDataTransfert::CapteurDataTransfert() {

}

/**
 * Lance le transfert des données vers la base
 */
void CapteurDataTransfert::transfertData() {
#ifdef DEBUG_DATA_TRANSFERT
	Serial.println("Begin data transfert...");
#endif
	if(!capteurSd.init() || !capteurSd.dataAvailable()){
		capteurSd.end();
		return;
	}

	digitalWrite(BUILTIN_LED, HIGH);
	bool pltpSucess = false;
	for(int i=0;i<3 && !pltpSucess;i++){
		pltpSucess = pltp.begin();
	}
	if(!pltpSucess){
#ifdef DEBUG_DATA_TRANSFERT
		Serial.println("Failed to begin PLTP !");
#endif
		for(int i=0;i<10;i++){
			digitalWrite(BUILTIN_LED, LOW);
			vTaskDelay(pdMS_TO_TICKS(100));
			digitalWrite(BUILTIN_LED, HIGH);
			vTaskDelay(pdMS_TO_TICKS(100));
		}
		digitalWrite(BUILTIN_LED, LOW);
		return;
	}
	digitalWrite(BUILTIN_LED, LOW);

#ifdef DEBUG_DATA_TRANSFERT
	Serial.println("PLTP init success !");
#endif

	//On attend de recevoir l'heure depuis la base
	if(pltp.processMessage(10*1000)) {
		PLTP::Message message = pltp.getLastMessage();
		if(message.type == PLTP::Time){
			struct timeval tv{};
			memcpy(&tv.tv_sec, &message.content[1], 4);
			tv.tv_usec = 0;
			settimeofday(&tv, nullptr);
#ifdef DEBUG_DATA_TRANSFERT
			Serial.println("Setting time : "+String(tv.tv_sec));
#endif
			//Une fois qu'on a reçu l'heure, on lance le transfert des fichiers à la racine de la carte micro SD
			capteurSd.startReadingFiles();
			File fileToSend = capteurSd.openNextFile();
			while(fileToSend){
#ifdef DEBUG_DATA_TRANSFERT
				Serial.println("Sending file : "+String(fileToSend.name()));
#endif
				if(pltp.sendFile(&fileToSend)){
#ifdef DEBUG_DATA_TRANSFERT
					Serial.println("File sent sucessfully !");
#endif
				}
				else{
#ifdef DEBUG_DATA_TRANSFERT
					Serial.println("Failed to send file !");
#endif
				}
				fileToSend.close();
				fileToSend = capteurSd.openNextFile();
			}
		}
	}

#ifdef DEBUG_DATA_TRANSFERT
	Serial.println("Ending data transfert");
#endif
	pltp.end();
	capteurSd.end();
}
