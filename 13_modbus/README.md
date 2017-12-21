
﻿Apprendre Qt  -  MODBUS TCP
================
Présentation
----
Modbus (marque déposée par Modicon) est un protocole de communication utilisé pour des réseaux d'automates programmables (API). Il fonctionne sur le mode maître / esclave(s). Il est constitué de trames contenant l'adresse de l'esclave concerné, la fonction à traiter
(écriture, lecture) et pour finir les données. 
Modbus TCP est la variante "encapsulée" dans TCP/IP du protocole
Modbus. Pour permettre l’établissement des connexions et l’échange de données entre équipements, le service  Modbus TCP doit fournir une socket d’écoute sur le port **502** qui  est réservé aux communications Modbus.
La classe client **modbustcp** construit les  requêtes sur la base des informations transmises par l'interface graphique.
 
L'objectif de ce TP est :
---
 - Développer un **client Modbus over TCP.**
 - Mettre en œuvre le protocole modbus 
 - les flux binaires avec **QDataStream** 
 
Screenshot:
----
Le client modbus TCP connecté à un variateur ATV32
![enter image description here](https://lh3.googleusercontent.com/-uxdI1BNIVwQ/WjvH8AsH-kI/AAAAAAAANgc/5xoV74j2rigp90PR6RhpTh2hDdNbK8OeQCLcBGAs/s0/screenshot1.png "screenshot1.png")
> - Auteur  **philippe SIMIER Lycée Touchard Le Mans**
> - Licence  **licence publique générale GNU (GPL)**
