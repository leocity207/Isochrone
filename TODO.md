23/06/2021
==========
DONE
----
* organisation et planification

TODO 
----
* DATA
  * remplire les fiche des horraire de bus
  * crée un fichier contenant localisation des arret de bus 

07/07/2021
==========
DONE
----
* creation du fichier de localization
* creation du code permetant de convertir les coordoner geographique et de lire le fichier


TODO 
----
* DATA
  * remplire les fiche des horraire de bus
  * crée un fichier contenant localisation des arret de bus 
* Etablissement du model
  * 
                PREPARE
                - add date to stoptimes using trips + calandar_dates
                - compute walk duration between all stops

                INITIALIZE
                - input: start lat, start lon, start-time, max duration -> end-time
                - filter stoptimes between start-time and end-time
                - filter: walk duration too long

                START
                - from starting position, get all reachable stops. Columns:
                    - stop_id
                    - arrival_time (ie start time + walking duration to the stop)

                LOOP
                - from selected stops -> find reachable stoptimes
                    - same stop id
                    - end-time > trip-stoptime > arrival_time
                    - if no reachable stoptimes was found: exit loop
                - expand reachable stoptimes
                    - next stoptimes of the allready found trips
                - split stoptimes:
                    - A: those that were marked reachable
                    - B: all others, kept for next loop
                - from group A stoptimes:
                    - drop duplicate stops: keep earliest arrival_time
                - walk from the new stops to all possible stops -> new arrival times
                    - remove if arrival time > end-time
                    - drop duplicated stops: keep earliest arrival_time
                - we now have a new list of reachable stops (stop_id, arrival_time)
                - if it is the same as before: FINISHED
                - else:
                    - restart loop with these new selected stops*  

07/07/2021
==========
DONE
----
* model par optimization du trajet choisi
* debut de la programation du


TODO 
----
* DATA
  * remplire les fiche des horraire de bus
  * crée un fichier contenant localisation des arret de bus 
* Programme
  * crée la class IO pour lir les station et les coordone
  * crée l'algorithm pour obtimiser toute les station connaisant le trajet 

07/07/2021
==========
DONE
----
* algorithm pour trouver les calculer la map fonctionelle cependant il prend beaucoup de temps a s'executer


TODO 
----
* DATA
  * remplire les fiche des horraire de bus
  * crée un fichier contenant localisation des arret de bus 
* Programme
  * crée la class IO pour lir les station et les coordone
  * crée l'algorithm pour obtimiser toute les station connaisant le trajet 


13/07/2022
==========
DONE
----
* ajout de la logique pour l'optimisation du temps d'arriver des stations


TODO 
----
* DATA
  * remplire les fiche des horraire de bus
  * crée un fichier contenant localisation des arret de bus 
* Programme
  * crée la class IO pour lir les station et les coordone
  * crée l'algorithm pour obtimiser toute les station connaisant le trajet 
    * documentation pour les fonction des differente classes
    * verifier l'utilisation de chaque fonction
    * ajout la classe des 'lines' qui doit contenir les diferentes ligne et obtenir les temps entre de station a un heur donné
  * crée des teste pour valider l'algo d'optimisation
  * faire plus de recherche sur les diagrames de voronoi weighted additif   

24/07/2022
==========
DONE
----
* fonctionnement de l'algorithm de base


TODO 
----
* DATA
  * remplire les fiche des horraire de bus
* Programme
  * crée l'algorithm pour obtimiser toute les station connaisant le trajet 
    * documentation pour les fonction des differente classes
    * verifier l'utilisation de chaque fonction
    * ajout la classe des 'lines' qui doit contenir les diferentes ligne et obtenir les temps entre de station a un heur donné
  * crée des teste pour valider l'algo d'optimisation
  * faire plus de recherche sur les diagrames de voronoi weighted additif   

12/10/2022
==========
DONE
----
* ajout des données pour les stations


TODO 
----
* DATA
  * remplire les donnés pour le coordoné des stations
* Programme
  * crée l'algorithm pour obtimiser toute les station connaisant le trajet 
    * documentation pour les fonction des differente classes
    * verifier l'utilisation de chaque fonction
    * ajout la classe des 'lines' qui doit contenir les diferentes ligne et obtenir les temps entre de station a un heur donné
  * crée des teste pour valider l'algo d'optimisation
  * faire plus de recherche sur les diagrames de voronoi weighted additif   ss

19/10/2022
==========
DONE
----
* finition de l'algorithm principal avec le chercher de station
* ajout de data pour crée les lines


TODO 
----
* DATA
  * remplire les donnés pour le coordoné des stations
* Programme
  * crée l'algorithm pour obtimiser toute les station connaisant le trajet 
    * documentation pour les fonction des differente classes
    * revoir la manier dont on accede a a_way et r_way qui ne sera pas aussi simple
  * crée des teste pour valider l'algo d'optimisation
  * faire plus de recherche sur les diagrames de voronoi weighted additif   ss


31/10/2022
==========
DONE
----
* ajout des testes
* coordoné des station rempli et terminer
* relecture sur l'algorithme 
* revision de l'architecture des A_ways R_ways pour un acces plus simple


TODO 
----
* Programme
  * crée l'algorithm pour obtimiser toute les station connaisant le trajet 
    * documentation pour les fonction des differente classes
  * faire plus de recherche sur les diagrames de voronoi weighted additif
  * lire article sur les carte Isochrone et les transport
  * tester le programme grandeur nature
  * evolution vers le language C ?

03/12/2022
==========
DONE
----
* Working algorithm 


TODO 
----
* Programme
  * crée l'algorithm pour obtimiser toute les station connaisant le trajet 
    * documentation pour les fonction des differente classes
  * faire plus de recherche sur les diagrames de voronoi weighted additif
  * lire article sur les carte Isochrone et les transport
  * tester le programme grandeur nature
  * evolution vers le language C ?