# Recherche de plus court chemin
Ce Projet entièrement rédigé en C est toujours en cours de développement.
Il vise à écrire un algorithme de recherche de plus court chemin en implémentant un algorithme génétique.
Dans cette finalité, il contient (ou contiendra):
* Un algorithme génétique, actuellement il ne prend en compte que les distances, mais devrait etre capable ulterieurement de prendre d'autre facteurs en compte tels que le vent, les courant ou le dénivelé
* Un algorithme basé sur le bruit de Perlin pour la création de carte aléatoire afin de vérifier le bon fonctionnement de l'argorithme génétique
* Un algorithme de transformation de carte en graphe (sous la forme d'un tableau de liste de voisin)
* Un algorithme de parcours en largeur et une implementation de l'algorithme de Dijkstra, qui servent a validé les resultats obtenu par l'algorithme génétique et prouver sa convergence

### Compilation
```shell
make
```

### License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Licence Creative Commons" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />Cette œuvre est mise à disposition selon les termes de la <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Licence Creative Commons Attribution -  Partage dans les Mêmes Conditions 4.0 International</a>.
