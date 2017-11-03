Apprendre Qt   mise en oeuvre du modèle/vue 2
================
Présentation
----
Ce Tp fait suite au précédent qui mettait en œuvre les listes simples. 
Ici nous mettons en  œuvre un modèle de type **QStandardItemModel** et le widget **QTableView** qui permettent respectivement de créer un modèle tableau et la vue graphique correspondante.
Nous redéfinissons le délégué pour que l'utilisateur ne puissent saisir que des entiers compris dans intervalle [0 100].   Pour modifier le contenu,  L’éditeur choisi est le **QSpinBox**.   La couleur de fond de la cellule sera vert pour chaque élément modifié par l'utilisateur. Pour ce faire, nous devons créer une classe  Delegate qui hérite de la classe virtuelle QItemDelegate.  Les méthodes virtuelles createEditor , setEditorData, setModelData et updateEditorGeometry doivent être définies.

----------

La fonction **afficher la sélection** affiche le contenu des cellules et la position ligne colonne des cellule sélectionnées.  
il est également possible d'étendre le tableau en lui ajoutant soit une ligne ou un colonne supplémentaire.
 
L'objectif de ce TP est :
---
 - Mettre en œuvre le modele/vue avec **QStandardItemModel** et **QTableView**
 - Mettre en œuvre la sélection multiple et l'édition des éléments sur la vue en redéfinissant le délégué. 
 
Screenshot:
----
Voici une capture d'écran du TP terminé :
![enter image description here](https://lh3.googleusercontent.com/-IiO4ZuYtysk/WfyBgCq6StI/AAAAAAAANFE/cqKEBqnu7Ks82OZym1QhlAO0IC017dJJgCLcBGAs/s0/Capture1.PNG "Capture1.PNG")
Cet écran montre que l'utilisateur à modifié les cellules (3,3) (2,5) (2,6) et (1,9)
l'utilisateur a sélectionné les cellules (2,1) (4,1) et (5,3).
> - Auteur  **philippe SIMIER Lycée Touchard Le Mans**
> - Licence  **licence publique générale GNU (GPL)**
