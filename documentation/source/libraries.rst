Libraries
=========
	Isochrone Create and Use diferent libraries

	.. graphviz:: graph/libraries.dot

	This graph show all of the libraries used by Isochrone and how they are interconected

library dependancies
--------------------
	here is the list of dependancies that Isochrone relies uppon
		* googletest : Used for unitary test and validating the product
		* rappidjson : Used for parsing json files inside the ressource library
		* Logger     : A login library that can be used to debug at runtime

Own libraries
-------------
	Here is a small explanation about each of our small modules

Utils
^^^^^
	You can find general purpose object and function here including some header file that are use to make our life easier

coordinate
^^^^^^^^^^
	This module implement 2D coordinate of a sphere and plan, it also contain projector that can be used to transform spherical coordinate to planar coordinate

network
^^^^^^^
	This Module implement Network descriptiv object like a station or a line. these objects are mainly what can be extracted from ressource files
	this modules heavily relies on coordinates for positional desccription on object (mainly station) and also Utils for representim time in a nice way

resources
^^^^^^^^^
	This Module is intended to be a simple way to parse and validate data comming from different sources.
	More explanation can be found inside the module documentation

reach_algorithm
^^^^^^^^^^^^^^^
	This Module implement algorithm to solve the station reaching problem, a few algorithm are implemented with different flavor
	This module heavily relies on Network object and Context to solve the algorith

Context
^^^^^^^
	Context are the working support on wich you are working on. you can se them as a crafting table where you put all the ingredients on. therefore context doesn't contain any inteligence but are rather the glue that stick everything together
