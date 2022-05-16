#include "CapteurDataTransfert.h"

CapteurDataTransfert::CapteurDataTransfert() {

}

void CapteurDataTransfert::transfertData() {
#ifdef DEBUG_DATA_TRANSFERT
	Serial.println("Begin data transfert...");
#endif
	if(!capteurSd.init() || !capteurSd.dataAvailable()){
		capteurSd.end();
		return;
	}

	if(!pltp.begin()){
#ifdef DEBUG_DATA_TRANSFERT
		Serial.println("Failed to begin PLTP !");
#endif
		return;
	}

#ifdef DEBUG_DATA_TRANSFERT
	Serial.println("PLTP init success !");
#endif

	if(pltp.processMessage(5*1000)) {
		PLTP::Message message = pltp.getLastMessage();
		if(message.type == PLTP::Time){
			struct timeval tv{};
			memcpy(&tv.tv_sec, &message.content[1], 4);
			tv.tv_usec = 0;
			settimeofday(&tv, nullptr);
#ifdef DEBUG_DATA_TRANSFERT
			Serial.println("Setting time : "+String(tv.tv_sec));
#endif
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
