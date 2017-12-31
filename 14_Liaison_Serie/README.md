# Apprendre Qt 5 Liaison série

Présentation
---
RS-232 est une norme standardisant une voie de communication de type série sur trois fils minimum. Disponible sur presque tous les PC. Sur les systèmes d’exploitation Windows, les ports RS-232 sont désignés par les noms COM1, COM2, etc.  
Sur les portables qui ne disposent pas en général d’interfaces physiques RS-232 on utilise des adaptateurs USB/RS-232, cela revient à exploiter logiciellement un port série virtuel.  Le port série virtuel est une solution logicielle qui émule un port série standard.
Qt 5 : prend  nativement en charge les liaisons séries avec la classe **QSerialPort**.

Utilisation
----
 - Fixer le nom au port soit par le constructeur soit par
**setPortName()**
 `QSerialPort *port = new QSerialPort(portName);`
 
 - Connexion des signaux
    `connect(port, SIGNAL(readyRead()), this, SLOT(recevoir()));`
 
 - Ouvrir le port en précisant Lecture/Ecriture – lecture seule – Ecriture seule
   `port->open(QIODevice::ReadWrite);`

 - Si l’ouverture est réalisée avec succès, réglage des paramètres.
  ` if(port->isOpen())`
 `{ port->setBaudRate(QSerialPort::Baud9600);`
 `port->setDataBits(QSerialPort::Data8);`
 `port->setParity(QSerialPort::NoParity);`
 `port->setStopBits(QSerialPort::OneStop);`
 `port->setFlowControl(QSerialPort::NoFlowControl); }`
 - Lecture et/ou Ecriture
   `nombresOctets = port->write(trame.toLatin1());`
 - Fermeture du port.
   `port->close();`

> **Notes :**

> - Auteur : **SIMIER Lycée Touchard Le Mans**
> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#
exemple http://eskimon.fr/108-arduino-304-ordinateur-voie-serie-autre-langage
-->
