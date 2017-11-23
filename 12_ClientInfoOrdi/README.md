Apprendre Qt  -   Client TCP avec QTcpSocket
================
Présentation
----
On se propose de créer un **client TCP** capable de se connecter à un serveur. Le client enverra une requête  sous forme d'un caractère au serveur et affichera la réponse reçue en retour à sa demande.
Le module QtNetwork
-----
Le module QtNetwork offre des classes qui vous permettent d’écrire vos propres clients et serveurs TCP/IP. Pour inclure les déclarations des classes de ce module, il vous faut utiliser la directive suivante :

    #include <QtNetwork>

Pour disposer ce module, il vous faut ajouter cette ligne à votre fichier de projet .pro :

    QT += network

Qt fournit de nombreuses classes pour la programmation réseau, on disposera :

 - des classes comme **QFtp** pour les protocoles de la couche Application
 - des classes de plus bas niveau comme **QTcpSocket** ,  **QTcpServer** et **QUdpSocket**
 - des classes de plus haut niveau pour une gestion simplifiée du réseau comme **QNetworkConfiguration** ,  **QNetworkConfigurationManager**, ...
 
La classe QTcpSocket
--------
La classe QTcpSocket est asynchrone et émet des signaux pour reporter des changements de statuts et des erreurs. Elle repose sur une boucle d’événements pour détecter des données arrivantes et automatiquement envoyer les données partantes.
Les signaux qu’il faut au minimum gérer par connect() côté client :
 - **readyRead()** signale que des données ont été reçues et sont prêtes à être lues ;
 -  **connected()** signale que la socket est dans l’état connecté ;
 - **disconnected()** signale que la socket est dans l’état déconnecté ;
 - **error()** signale qu’une erreur s’est produite sur la socket ;
 
Vous pouvez écrire des données dans le socket avec **QTcpSocket::write()** 
et en lire avec **QTcpSocket::read()**.
 
L'objectif de ce TP est :
---
 - Mettre en œuvre la classe QTcpSocket 
 - Définir un protocole application basique
 
Screenshot:
----

> - Auteurs  **BERNARD CRUCHET SIMIER Lycée Touchard Le Mans**
> - Licence  **licence publique générale GNU (GPL)**
