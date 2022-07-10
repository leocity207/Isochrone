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
  *  