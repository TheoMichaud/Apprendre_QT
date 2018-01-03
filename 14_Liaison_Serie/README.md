# Apprendre Qt 5 Liaison série

Présentation
---
**RS-232** est une norme standardisant une voie de communication de type série sur trois fils minimum (Rx, Tx et Gnd). Elle est disponible sur presque tous les PC.  Sur les systèmes d’exploitation Windows, les ports RS-232 sont désignés par les noms COM1, COM2, etc.  Sous linux ils sont désignés par ttyS0, ttyS1 ou ttyAMA0
Les portables  ne disposent pas en général d’interfaces physiques RS-232, on utilise alors des adaptateurs USB/RS-232 et cela revient à exploiter logiciellement un port série virtuel.  il est nécessaire d'installer un driver pour émuler un port série standard via USB.
Qt 5 : prend  nativement en charge les liaisons séries avec le module **QSerialPort**.  Ce module prend en charge la plupart des versions 32 et 64 bits des systèmes compatibles Microsoft Windows, Linux, Mac OS X et POSIX, tels que les UNIX. 
Ce module fournit deux classes principales: QSerialPort et QSerialPortInfo. Pour l'utiliser, ajoutez cette ligne à votre fichier de projet:

    QT += serialport
La classe **QSerialPortInfo** fournit des informations sur un port série du système. Vous pouvez créer un objet QSerialPortInfo en spécifiant un nom de périphérique ou un objet QSerialPort existant. Vous pouvez également obtenir une liste d'objets QSerialPort pour tous les ports série en appelant la méthode statique **availablePorts ()**. Une fois que vous avez un objet QSerialPortInfo, vous pouvez appeler différentes méthodes pour obtenir des informations telles que le nom, l'emplacement, la description et le fabricant du port.

La classe **QSerialPort** est utilisée pour la communication. Elle hérite de **QIODevice**, la classe de base de tous les périphériques d'E/S de Qt, tel que les fichiers, les buffers , les sockets TCP et UDP. Cela vous permet de tirer parti de vos connaissances en entrée/sortie dans Qt et de l'utiliser avec n'importe quelle classe qui fonctionne sur un QIODevice

Utilisation de QSerialPort
----
 - Fixer le nom au port soit par le constructeur soit par
**setPortName()**
 `QSerialPort *port = new QSerialPort(portName);`
 
 - Connexion des signaux au slots
    QSerialPort émet des signaux lorsque les opération sont terminées. Par exemple, après une écriture lorsque les données sont envoyées au port série, QSerialPort émet le signal **bytesWritten ()**. Lorsque des données sont disponibles à la lecture le signal **readyRead()** est émis.
    
    `connect(port, SIGNAL(readyRead()), this, SLOT(recevoir()));`
 
 - Ouvrir le port en précisant Lecture/Ecriture – lecture seule – Ecriture seule
   `port->open(QIODevice::ReadWrite);`

 - Si l’ouverture est réalisée avec succès, réglage des paramètres de communication.
  `if(port->isOpen())`
 `{ port->setBaudRate(QSerialPort::Baud9600);`
 `  port->setDataBits(QSerialPort::Data8);`
 `  port->setParity(QSerialPort::NoParity);`
 `  port->setStopBits(QSerialPort::OneStop);`
 `  port->setFlowControl(QSerialPort::NoFlowControl); }`
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
