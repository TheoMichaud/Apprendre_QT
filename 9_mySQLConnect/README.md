Apprendre Qt   - Se connecter à un serveur MySQL
================
Présentation
----
Qt fournit des solutions intégrées pour accéder aux données sur des serveurs du type SQL. 
Ici nous mettons en  œuvre une connexion sur un serveur MySQL. Elle est possible grâce à la classe **QSqlDatabase** qui utilise le modèle du singleton. il ne faut pas l'instancier mais déclarer une connexion en lui donnant un nom.

Ensuite nous exécutons la requête `SELECT * FROM people` pour obtenir le contenu de la table people.  Toutes les requêtes s’exécutent de la même manière. Certaine renvoient des résultats `SELECT` d'autres non `UPDATE DELETE INSERT`. L’exécution d'une requête peut se faire uniquement sur une base de données ouverte. Une requête quelque soit son type est effectuée grâce à une instance de la classe **QSqlQuery** .
 
----------
L'objectif de ce TP est :
---
 - Mettre en œuvre une connexion pour accéder à un serveur SQL
 - Configurer le serveur pour autoriser les connexions à distance
 - Créer un utilisateur dédié à la base accessible à distance
 - lancer et récupérer le résultats d'une requête

----------
Prérequis  : Configurer MySQL
----
Par défaut MySQL n'écoute que les connexions locales.  Dans le fichier    `/etc/mysql/my.cnf`  Il faut commenter la ligne suivante

     # bind-address 127.0.0.1

Configurer un utilisateur 
----
Il est préférable de créer un utilisateur spécifique ayant accès à la base. (avec phpMyAdmin)
![enter image description here](https://lh3.googleusercontent.com/-fHw33WleqFI/Wf3aY5WAoSI/AAAAAAAANFk/BA8ZY4QMB_4pBXgUe0076YV_R3BOU0twACLcBGAs/s0/Capture4.PNG "Capture4.PNG")

ici ce sera **QtUtilisateur**

Installer le driver libmysql.dll 
-----
Copier le fichier  **libmysql.dll** dans le répertoire d'installation de Qt. 
![enter image description here](https://lh3.googleusercontent.com/-iBVunCncQ1U/Wf3cRZWPydI/AAAAAAAANF4/haZuHfutt00yN2RgnxgBRoDZ7Pt6jOwqgCLcBGAs/s0/Capture3.PNG "Capture3.PNG")

ScreenShot
----
![enter image description here](https://lh3.googleusercontent.com/-0YqjP-Kcplk/Wf3d_TcBCPI/AAAAAAAANGI/2D-gej7rxx0W0nl3YOwy6ZU1TcGtkdFdQCLcBGAs/s0/Capture1.PNG "Capture1.PNG")

le contenu de la même table à partir de phpMyAdmin
![enter image description here](https://lh3.googleusercontent.com/-upq70601l-4/Wf3eakWAveI/AAAAAAAANGQ/Ju4nm94W0mMoKM45ASgdxhw_tL_MH4qTgCLcBGAs/s0/Capture2.PNG "Capture2.PNG")