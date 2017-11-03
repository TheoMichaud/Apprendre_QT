Apprendre Qt   mise en oeuvre du modèle/vue
================
Présentation
----
Dans l'architecture **modèle / vue**, le modèle fournit une interface standard que 
les vues et les délégués utilisent pour accéder aux données. 


----------


Tous les modèles fournis par Qt sont basés sur la classe QAbstractItemModel. 
Cette classe est la plus abstraite et la plus haute dans la hiérarchie des classes des 
différents modèles. Elle fournit une interface que tous les modèles doivent 
respecter, afin d'être utilisés correctement avec une vue. 
De base, Qt fournit un ensemble de modèles pouvant être directement utilisés 
comme par exemple :
 **QStringListModel** : stockage d'une liste de QString ;
 **QFileSystemModel** : un ensemble d'informations sur un fichier ou un répertoire du système de fichier local .

----------


la **vue** obtient les données depuis le modèle et les présente à l'utilisateur.
En plus de présenter les données, la vue gère certains aspects de la sélection d'éléments (simple ou multiple). Une vue peut fournir des fonctionnalités d'édition par défaut pour les éléments.
Qt fournit trois classes de vues prêtes à l'emploi qui présentent les données de modèles sous une forme standard.
**QListView** peut afficher les éléments d'un modèle sous forme d'une simple liste.
**QTableView** présente les éléments de modèles sous forme de table, de façon similaire à un tableur.
 **QTreeView** affiche les éléments de modèles sous forme d'une hiérarchie de listes, 
 


L'objectif de ce TP est :
---
 - Mettre en œuvre le modele/vue avec **QStringListModel** et **QListView**
 - Mettre en œuvre la sélection multiple et l'édition des éléments sur la vue. 
 
Screenshot:
----
Voici une capture d'écran du TP terminé :
![enter image description here](https://lh3.googleusercontent.com/-tPz7yAeLs7Y/WfndPhAyoOI/AAAAAAAANEo/KSWnx5n7DaEp5bsHw22-gKjIDQwPV7fJQCLcBGAs/s0/ScreenShot.PNG "ScreenShot.PNG")
> **Note :**

> - Auteur  **philippe SIMIER Lycée Touchard Le Mans**
> - Licence  **licence publique générale GNU (GPL)**