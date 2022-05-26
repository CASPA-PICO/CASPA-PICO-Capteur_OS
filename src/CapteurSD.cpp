#include "CapteurSD.h"

CapteurSD::CapteurSD() {

}

/**
 * Initialise la carte micro SD
 * @return True en cas de succès, False en cas d'échec
 */
bool CapteurSD::init() {
	if(!SD.begin(SS, SPI, 4000000, "/sd", 5, false)){
#ifdef DEBUG_SD
		Serial.println("SD card mount failed !");
#endif
		return false;
	}

	sdcard_type_t cardType = SD.cardType();
#ifdef DEBUG_SD
	switch(cardType){
		case CARD_NONE:
			Serial.println("SD card type : none");
		case CARD_MMC:
			Serial.println("SD card type : MMC");
			break;
		case CARD_SD:
			Serial.println("SD card type : SD");
			break;
		case CARD_SDHC:
			Serial.println("SD card type : SDHC");
			break;
		default:
			Serial.println("SD card type : unknown");
			break;
	}
#endif

	if(cardType == CARD_NONE){
		return false;
	}

#ifdef DEBUG_SD
	Serial.println("SD card init successfully");
#endif

	return true;
}

/**
 * Vérifie si des données sont prêtes à être transférées
 * @return True si des fichiers peuvent être transférés, False sinon
 */
bool CapteurSD::dataAvailable() {
	File root = SD.open("/");
	if(!root){
#ifdef DEBUG_SD
		Serial.println("Impossible d'ouvrir le repertoire '/'");
#endif
		return false;
	}
	else if(!root.isDirectory()){
#ifdef DEBUG_SD
		Serial.println("Le repertoire '/' n'est pas un dossier");
#endif
		return false;
	}

	File file = root.openNextFile();
	int fileCount = 0;
	while(file){
		if(!file.isDirectory()){
			fileCount++;
		}
		file = root.openNextFile();
	}

#ifdef DEBUG_SD
	Serial.println(String(fileCount)+" fichiers disponible pour un transfert");
#endif
	root.close();
	return fileCount > 0;
}

void CapteurSD::end() {
	SD.end();
}

/**
 * Démarrage de la lecture des fichiers depuis la carte micro SD
 */
void CapteurSD::startReadingFiles() {
	if(root.available()){
		root.close();
	}
	root = SD.open("/");
}

/**
 * Ouvre le prochain fichier à la racine de la carte micro SD
 * @return Renvoie un fichier
 */
File CapteurSD::openNextFile() {
	File file = root.openNextFile();
	while(file && file.isDirectory()){
		file = root.openNextFile();
	}
	return file;
}