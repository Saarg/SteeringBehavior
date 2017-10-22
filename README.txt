# Stearing Behavior
//////////////////////////////////////////////////////////////////////////////
    Travail effectu� par Erwann Large, Jean Milsonneau, Yannick Loussouarn.
//////////////////////////////////////////////////////////////////////////////

Travail r�alis� :
  - Cr�ation d'une classe Agent-pousuiveur
  - Cr�ation d'une classe Agent-Leader qui utilise l'agorithme de Wander
  - Cr�ation d'une interface graphique, avec menu, pour d�terminer le nombre de leader, leurs type et les formations des poursuiveurs
  - Cr�ation d'une classe Agent-Player comme un agent leader, mais controll� par le joueur humain
  - Cr�ation d'une formation en "V" pour les poursuiveurs
  - Cr�ation d'une formation en "X" pour les poursuiveurs
 
//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Cr�ation d'une classe Agent-pousuiveur:

  L'agent pousuiveur est un Vehicule, qui se d�plce en utilisant l'algorithme "Wander" tant qu'il ne rencontre pas de leader dans sa zone de trigger.
  Lorsqu'un leader rentre dans sa zone de trigger, l'agent poursuiveur se met � suivre le leader, et uniquement ce leader (l'introduction d'autre leader ne perturbe pas le comportement de l'agent)
  Lorsque l'agent rencontre un leader, on lui donne un offset selon la formation demand� par le leader, puis on le place dans la formation, soit selon le leader si l'agent est seul, soit selon le/les agents pr�cedents 
  (d�pendamment de la formation)
  Lorsque un agent est dans la formation, on recalcule sa position suivant selon: la position du leader, et la m�thode de flocking, pour rester en formation, et ne pas rentrer dans les autres agents, ou un mur.

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Cr�ation d'une classe Agent-Leader:

  L'agent leader est un Vehicule qui utilise l'algorithme de "Wander" vu en cours. Lorqu'un follower arrive dans la formation, le leader l'ajoute � sa table de follower.
  On recalule ensuite l'offset de ce follower, soit par rapport � l'agent leader (s'il est le seul), soit par rapport au follower pr�cedent (formation en ligne) soit par rapport au 2nd pr�c�dent (formation en V).
  C'est � l'agent leader que l'on demande une formation, et c'est lui qui la fait applique par les agent-poursuiveurs.

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Cr�ation d'une interface graphique:
  
  Ajout sur l'interface graphique d�j� existante de menus d�roulants permettants :
 	- Activer/D�sactiver les leader 1 et 2
	- Changer la formation pour un leader donn� (chaque leader peut avoir une formation diff�rente)
	- Ajout du menu permettant d'activer/d�sactiver le leader Player, et de choisir sa formation
	- Ajout du menu permettant de toggle les commandes du Player

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Cr�ation d'une classe Agent-Player:
 
  L'agent player est un Vehicule. Il se dirige avec les touches W-A-S-D. Lorsque le joueur appuis sur une de ces touches, le leader va recevoir une force dans cette diection.
  Pour la gestion et le fonctionnement des follower, l'agent player se comporte comme un agent leader classique. 
//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Cr�ation d'une formation en "V" pour les poursuiveurs:

  Nouvelle formation pour les follower d'un agent, elle permet de simulet le vol des oiseaux sauvages. Les followers vont prendre une formation en V (d'o� le nom), compos� de 2 "files", dont le follower suivant sera l�g�rement d�cal� 
  (vers la gauche pour la file gauche et vers la droite pour la file droite).
  Pour cela, il faut 2 offset initiaux, qui seront l'un pour la file droite, et l'autre pour la file gauche.
  Chaque follower aura alors sont offset selon, non pas le follower le pr�cedent, mais celui le pr�cedent dans la m�me file que lui, c'est � dire son second pr�cedent.
  Les r�gles du flocking s'applique pour cette formation, pour �viter les chevauchement des followers des 2 files, comme par exemple lors d'un mouvement vertical.

//////////////////////////////////////////////////////////////////////////////////////////////////

  -> Cr�ation d'une formation en "X" pour les poursuiveurs

//////////////////////////////////////////////////////////////////////////////////////////////////