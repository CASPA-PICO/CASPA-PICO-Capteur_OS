#ifndef CAPTEUR_OS_CAPTEURDATATRANSFERT_H
#define CAPTEUR_OS_CAPTEURDATATRANSFERT_H

#include "CapteurSD.h"
#include "PLTP.h"

#define DEBUG_DATA_TRANSFERT

#define PIN_CHARGE_DETECT 25

class CapteurDataTransfert {
public:
	CapteurDataTransfert();
	void transfertData();
private :
	CapteurSD capteurSd;
	PLTP pltp = PLTP(false);
};


#endif //CAPTEUR_OS_CAPTEURDATATRANSFERT_H
