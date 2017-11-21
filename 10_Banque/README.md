
﻿Apprendre Qt  -   Connexion et exécution de requètes SQL 
================
Présentation
----
Dans certaines situations il est plus simple de proposer une vue tabulaire d'un jeu de données.  Nous allons créer une application snirBanque qui fait appel **QSqlTableModel** pour permettre aux utilisateurs d'afficher et d'interagir avec les données stockées dans une base de données.  Nous allons créer une fenêtre principale de dialogue dans laquelle les utilisateurs pourront modifier une liste de clients, de comptes et d'opérations en utilisant une forme tabulaire.
Le fonctionnement est similaire à celui d'un tableur.

![enter image description here](https://lh3.googleusercontent.com/-LT0_EoexP9w/WhQFNcrfoZI/AAAAAAAANNQ/zWiUqaqkmp42vIjjGJEOja1C30Sv-PntwCLcBGAs/s0/Screenshot.png "Screenshot.png")

En plus de **QSqlQuery** utilisé lors du TP précédent, Qt fournit la classe       **QSqlTableModel** comme interface de haut niveau, ce qui permet d'éviter l'emploi du code SQL brut pour réaliser les opérations SQL les plus courantes (SELECT, INSERT, UPDATE et DELETE). La classe QSqlTableModel peut être utilisé comme source de donnée pour une vue **QtableView**. 

Le schéma de la base de données est le suivant :

![Concepteur snirBanque](https://lh3.googleusercontent.com/-Cv1TagFIoQY/WgiHk4AhjCI/AAAAAAAANIU/Te5LNoV-Hg0_agnqtSxNeyAlbKVC_wQRACLcBGAs/s0/Concepteur.PNG "Concepteur.PNG")

Pour réaliser une requête avec **QSqlTableModel**  :

    QSqlTableModel modele
    modele.setTable("client");
    modele.setFilter("`ville` = 'le mans'");
    modele.select();
   ce qui est équivalent à la requête 

    SELECT * FROM `client` WHERE `ville` = 'le mans' 
    
    

 
L'objectif de ce TP est :
---
 - Mettre en œuvre le modele/vue avec **QSqlTableModel** et **QTableView**
 - Insérer modifier ou supprimer des enregistrements dans une table
 
Screenshot:
----

> - Auteur  **philippe SIMIER Lycée Touchard Le Mans**
> - Licence  **licence publique générale GNU (GPL)**
