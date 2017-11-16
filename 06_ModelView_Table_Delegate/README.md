Apprendre Qt   mise en oeuvre du modèle/vue 2
================
Présentation
----
Qt utilise  une architecture modèle-­vue (model-­view) entourée d'un délégué **(delegate)**. 
Cependant, pour des raisons de flexibilité, l'interaction  et les entrées utilisateurs ne sont non pas prises en compte  par un composant totalement séparé, à savoir le contrôleur, mais par un composant « interne » à la vue : le délégué. 
Ce composant est responsable de deux choses :

 - personnaliser l'édition des éléments au moyen d'un éditeur ;
 - personnaliser le rendu des éléments à l'intérieur d'une vue.

Tous les délégués fournis par Qt sont basés sur la classe **QAbstractItemDelegate**. Qt fournit deux délégués :

 -  QItemDelegate ;
 -  QStyledItemDelegate (utilise le style courant pour le rendu des données)
 
Les vues sont déjà dotées d'un délégué par défaut QStyledItemDelegate. 
Cependant, même si les vues sont dotées d'un délégué par défaut, il est bien 
entendu possible de le modifier. C'est le sujet de ce TP.


----------


Ici nous mettons en  œuvre le modèle de type **QStandardItemModel** qui permet de créer un tableau et le widget **QTableView** qui permet de créer la vue graphique correspondante.

Nous redéfinissons le délégué pour que l'utilisateur ne puissent éditer que des entiers compris dans intervalle [0 100].     L’éditeur choisi est le **QSpinBox**.   Pour personnaliser le rendu , la couleur de fond d'une cellule modifiée sera verte. Pour ce faire, nous devons créer une classe  Delegate qui hérite de la classe **QItemDelegate**.  Les méthodes  createEditor , setEditorData, setModelData et updateEditorGeometry doivent être définies.

 
 - **createEditor()** :  retourne le widget (éditeur) pour éditer l'item se trouvant à l'index *index*.
 - **setEditorData()** : permet de transmettre à l'éditeur *editor* les données à afficher à partir du modèle se trouvant à l'index *index*.
 - **setModelData()** : permet de récupérer les données de l'éditeur et de les stocker à
l'intérieur du modèle, à l'index identifié par le paramètre index.
 - **updateEditorGeometry()** : permet de redimensionner l'éditeur à la bonne taille 
lorsque la taille de la vue change

  





----------

La fonction **afficher la sélection** affiche le contenu des cellules et la position ligne colonne des cellule sélectionnées.  
il est également possible d'étendre le tableau en lui ajoutant soit une ligne ou un colonne supplémentaire.
 
L'objectif de ce TP est :
---
 - Mettre en œuvre le modele/vue avec **QStandardItemModel** et **QTableView**
 - Redéfinir le délégué  **QItemDelegate**
 - Mettre en œuvre la sélection multiple
 
Screenshot:
----
Voici une capture d'écran du TP terminé :
![enter image description here](https://lh3.googleusercontent.com/-IiO4ZuYtysk/WfyBgCq6StI/AAAAAAAANFE/cqKEBqnu7Ks82OZym1QhlAO0IC017dJJgCLcBGAs/s0/Capture1.PNG "Capture1.PNG")
Cet écran montre que l'utilisateur à modifié les cellules (3,3) (2,5) (2,6) et (1,9)
l'utilisateur a sélectionné les cellules (2,1) (4,1) et (5,3).
> - Auteur  **philippe SIMIER Lycée Touchard Le Mans**
> - Licence  **licence publique générale GNU (GPL)**
