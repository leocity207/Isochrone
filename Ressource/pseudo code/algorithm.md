1. Initialization
   1. Get the list of all the station.
   2. for each station set the isClosed parameter to false
   3. initialize the best time for each station to be the time needed to go o this station on foot
   4. s* the best station is initialized from being the best station to reach on foot
   

2. Iteration
   1. Lazy compute
      1. for all station s not closed
      2. compute the time needed from s* to the s
      3. if the time is better than the previous registered time
         - replace with the new time
         - don't change anything
 
   2. Line optimization
      1. get all the line l passing by s*
         1. for all station s in l and not closed
            1. find the closest train from curent time to reach s from s*
            2. if time to reach the station s is better than before:
               - replace with the new time
               - don't change anything for s
   3. s* is chosen as the best not closed station from the set S
   4. the number of iteration is equal to |S|-1



3. function needed to answer the problem ☐
   * ☑ Get all non closed station
   * ☑ Compute the time from s* to s
   * ☑ Get all line passing by a station 
   * ☑ Get all station from a line that are not closed
   * ☑ knowing a time T and a line l find the best shuttle to get from s* to s starting at time T