Apprendre Qt   mise en oeuvre du modèle/vue
================
Présentation
----
Dans l'architecture modèle / vue, le modèle fournit une interface standard que 
les vues et les délégués utilisent pour accéder aux données. 
Tous les modèles fournis par Qt sont basés sur la classe QAbstractItemModel. 
Cette classe est la plus abstraite et la plus haute dans la hiérarchie des classes des 
différents modèles. Elle fournit une interface que tous les modèles doivent 
respecter, afin d'être utilisés correctement avec une vue. 
De base, Qt fournit un ensemble de modèles pouvant être directement utilisés 
comme :
 **QStringListModel** : stockage d'une liste de QString ;
 **QFileSystemModel** : un ensemble d'informations sur un fichier ou un répertoire du système de fichier local ;


L'objectif de ce TP est :
---
 - Mettre en œuvre le modele/vue avec **QStringListModel** 
 
Screenshot:
----
Voici une capture d'écran du TP terminé :
![enter image description here](https://lh3.googleusercontent.com/-tPz7yAeLs7Y/WfndPhAyoOI/AAAAAAAANEo/KSWnx5n7DaEp5bsHw22-gKjIDQwPV7fJQCLcBGAs/s0/ScreenShot.PNG "ScreenShot.PNG")
> **Note :**

> - Auteur  **philippe SIMIER Lycée Touchard Le Mans**
> - Licence  **licence publique générale GNU (GPL)**