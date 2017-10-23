# Stearing Behavior
//////////////////////////////////////////////////////////////////////////////
    Travail effectué par Erwann Large, Jean Milsonneau, Yannick Loussouarn.
//////////////////////////////////////////////////////////////////////////////

Travail réalisé :
  - Création d'une classe Agent-pousuiveur
  - Création d'une classe Agent-Leader qui utilise l'agorithme de Wander
  - Création d'une interface graphique, avec menu, pour déterminer le nombre de leader, leurs type et les formations des poursuiveurs
  - Création d'une classe Agent-Player comme un agent leader, mais controllé par le joueur humain
  - Création d'une formation en "V" pour les poursuiveurs
  - Création d'une formation en "X" pour les poursuiveurs
  - Création d'une formation en "Cercle" pour les poursuiveurs
 
//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Création d'une classe Agent-pousuiveur:

  L'agent pousuiveur est un Vehicule, qui se déplce en utilisant l'algorithme "Wander" tant qu'il ne rencontre pas de leader dans sa zone de trigger.
  Lorsqu'un leader rentre dans sa zone de trigger, l'agent poursuiveur se met à suivre le leader, et uniquement ce leader (l'introduction d'autres leaders ne perturbe pas le comportement de l'agent)
  Lorsque l'agent rencontre un leader, on lui donne un offset selon la formation demandé par le leader, puis on le place dans la formation, soit selon le leader si l'agent est seul dans la formation, soit selon le/les agents précedents 
  (dépendamment de la formation)
  Lorsque un agent est dans la formation, on recalcule sa position suivant selon: la position du leader, et la méthode de flocking, pour rester en formation, et ne pas rentrer dans les autres agents, ou un mur.

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Création d'une classe Agent-Leader:

  L'agent leader est un Vehicule qui utilise l'algorithme de "Wander" vu en cours. Lorqu'un poursuiveur arrive dans la formation, le leader l'ajoute à sa table de poursuiveur.
  On recalule ensuite l'offset de ce poursuiveur, soit par rapport à l'agent leader (s'il est le seul), soit par rapport au poursuiveur précedent (formation en ligne), soit par rapport au 2nd précédent (formation en V).
  C'est à l'agent leader que l'on demande une formation, et c'est lui qui la fait applique par les agent-poursuiveurs.

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Création d'une interface graphique:
  
  Ajout sur l'interface graphique déjà existante de menus déroulants permettants :
 	- Activer/Désactiver les leaders 1 et 2
	- Changer la formation pour un leader donné (chaque leader peut avoir une formation différente)
	- Ajout du menu permettant d'activer/désactiver l'Agent-Player, et de choisir sa formation
	- Ajout du menu permettant de toggle les commandes de l'Agent-Player

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Création d'une classe Agent-Player:
 
  L'Agent-Player est un Vehicule. Il se dirige avec les touches W-A-S-D. Lorsque le joueur appuis sur une de ces touches, le leader va recevoir une force dans cette diection, jusqu'à ce que le joueur lui donne un autre ordre.
  Pour la gestion et le fonctionnement des poursuiveurs, l'Agent-Player se comporte comme un agent leader classique. 

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Création d'une formation en "V" pour les poursuiveurs:

  Nouvelle formation pour les poursuiveurs d'un agent, elle permet de simulet le vol des oiseaux sauvages. Les poursuiveurs vont prendre une formation en V (d'où le nom), composé de 2 "files", dont le poursuiveur suivant sera 
  légèrement décalé (vers la gauche pour la file gauche et vers la droite pour la file droite).
  Pour cela, il faut 2 offsets initiaux, qui seront l'un pour la file droite, et l'autre pour la file gauche.
  Chaque poursuiveur aura alors son offset, selon non pas le poursuiveur précedent, mais celui le précedent dans la même file que lui, c'est à le son second précedent dans la formation.
  Les règles du flocking s'appliquent pour cette formation, pour éviter les chevauchements des poursuiveurs des 2 files, comme par exemple lors d'un mouvement vertical.

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Création d'une formation en "X" pour les poursuiveurs

  Même principe de fonctionnement que pour la formation en V, mais avec 2 formations en V, une dans un sens, et la seconde dans l'autre sens.

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Création d'une formation en "Cercle" pour les poursuiveurs

  Formation en cercle autour de l'agent leader. Cela pourait servir pour une escort ou une protection par exemple. 
  On récupère le nombre de poursuiveurs dans le fichier params.ini, et on en déduis l'angle des follower (ici 20 poursuiveurs-> 360/20 = 28). Arpès cela, les poursuiveurs sont placés grace à l'angle et leur numero dans la formation.
  Une piste d'amélioration éventuelle serai de créer l'angle dynamiquement, en fonction du nombre de poursuiveurs dans la formation à l'instant t.

//////////////////////////////////////////////////////////////////////////////////////////////////