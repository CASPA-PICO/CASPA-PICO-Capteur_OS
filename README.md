<h1>CASPA-PICO Capteur OS</h1>
<p>Le programme est un projet <a href="https://platformio.org/">Platform IO</a> testé sur une ESP32 modèle : <a href="https://www.dfrobot.com/product-1590.html">DFR0478</a><br/></p>
<h2>Bibliothèques utilisées</h2>
<ul>
  <li><a href="https://github.com/CASPA-PICO/PLTP">PLTP</a></li>
  <li><a href="https://github.com/platformio/platform-espressif32">Espressif 32: development platform for PlatformIO</a></li>
  <li><a href="https://github.com/espressif/arduino-esp32">Arduino core for the ESP32</a></li>
</ul>
<h2>Fonctionnement global du programme</h2>
<p>Le microcontrôleur est en attente du déclenchement du transfert.<br/>
  Lorsque le capteur est branché à la base, le programme débute le transfert.<br/>
Le Bluetooth est activé le microcontrôleur tente de se connecter à la base.</br>
Une fois la connexion établie, le microcontrôleur attend de recevoir l'heure depuis la base</br>
Une fois l'heure reçue, le microcontrôleur transfert tous les fichiers se trouvant à la racine de la carte SD à la base.</p>
<h2>Configuration du programme</h2>
<p>Certains fichiers .h sont modifiables afin de changer la configuration du programme :
<ul>
  <li><b>CapteurDataTransfert.h</b> :
    <ul>
      <li><b>PIN_CHARGE_DETECT</b> : Pin de détection de la charge du capteur, lance le transfert en Bluetooth (par défaut 25)</li>
      <li><b>DEBUG_DATA_TRANSFERT</b> : Affichage des informations de débogage dans la console série (commenter pour désactiver)</li>
    </ul>
  </li>
  <li><b>CapteurSD.h</b>
    <ul>
      <li><b>DEBUG_SD</b> : Affichage des informations de débogage dans la console série (commenter pour désactiver)</li>
    </ul>
  </li>
</ul>
</p>
<h2>Montage du système :</h2>
<img src="https://i.ibb.co/Dpgjx95/IMG-20220516-161056.jpg">
