<h1>CASPA-PICO Capteur OS</h1>
<p>Le programme est un projet <a href="https://platformio.org/">Platform IO</a> testé sur une ESP32 modèle : <a href="https://www.dfrobot.com/product-1590.html">DFR0478</a><br/>
Il nécessite <b>obligatoirement</b> la bibliothèque <a href="https://github.com/CASPA-PICO/PLTP">PLTP</a> pour fonctionner.</p>
<h2>Fonctionnement global du programme</h2>
<h2>Fonctionnement global du programme</h2>
<p>Le microcontrôleur est en attente du déclenchement du transfert.<br/>
  Lorsque le pin <i>PIN_CHARGE_DETECT</i> (<a href="https://github.com/CASPA-PICO/CASPA-PICO-Capteur_OS/blob/master/src/CapteurDataTransfert.h">CapteurDataTransfert.h</a>) est mis à <i>HIGH</i> (3,3 V), le programme débute le transfert.<br/>
Le Bluetooth est activé le microcontrôleur tente de se connecter à la base.</br>
Une fois la connexion établie, le microcontrôleur attend de recevoir l'heure depuis la base</br>
Une fois l'heure reçue, le microcontrôleur transfert tous les fichiers se trouvant à la racine de la carte SD à la base</p>
<h2>Montage du système :</h2>
<img src="https://i.ibb.co/Dpgjx95/IMG-20220516-161056.jpg">
