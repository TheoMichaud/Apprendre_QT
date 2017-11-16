Apprendre Qt  -   Connexion et exécution de requètes SQL 
================
Présentation
----
Dans certaines situations il est plus simple de proposer une vue tabulaire d'un jeu de données.  Nous allons créer une application snirBanque qui fait appel **QSqlTableModel** pour permettre aux utilisateurs d'afficher et d'interagir avec les données stockées dans une base de données.  Nous allons créer une boîte de dialogue dans laquelle les utilisateurs pourront modifier une liste de clients, de comptes et d'opérations en utilisant une forme tabulaire.

![Vue tableur](https://lh3.googleusercontent.com/-Sl7zHU5gNGg/WgiGCLbwZQI/AAAAAAAANIE/p0pQyS0kAKQSQVcYoWT5XlrmpldDi0YegCLcBGAs/s0/Capture.PNG "Capture.PNG")

En plus de **QSqlQuery** utilisé lors du TP précédent, Qt fournit la classe       **QSqlTableModel** comme interface de haut niveau, ce qui permet d'éviter l'emploi du code SQL brut pour réaliser les opérations SQL les plus courantes (SELECT, INSERT, UPDATE et DELETE). La classe QSqlTableModel peut être utilisé comme source de donnée pour une vue **QtableView**. 

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
