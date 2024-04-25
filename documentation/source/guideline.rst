C++ codding Guidlines
=====================

	this are C++ codding guidlines that should be followed while adding c++ code to the project

pointer
-------

	* No raw pointer
	* pointer should always be wrapped inside Memory::Owned or used as reference
	* Memory::Unowned should only be used for interface with other library

Exception
---------

	* Exception Type are always in majuscule
	* All exception should inherit from 'Exception' (from Logger module)
	* All exception should be written inside "includes/utils/excpetion_defs.h"

Naming
------

	* Snake_Case for function and class
	* snake_case for variable
	* SNAKE_CASE for constant and enum or exception

class
-----

	class should have the folowing tag and order

	.. code-block:: cpp

		//####
		// TAG
		public:
			...
		protected:
			...
		private:
			...

	acceptable TAG shoudl apear in this order:

		* CTOR : for constructor
		* METHODS : for in class methods
		* STATIC_METHODS : for outter class methods
		* ATTRIBUTES : for in class attributes
		* STATIC_ATTRIBUTES : for outter class attributes

class constructor
-----------------

	use the "includes/utils/ctor.h fiels to tell about how the class should handle construction
	this can help you precise about default construction,default copy construction, default copy assignment, default move construction, default move assignment and default destruction

comments
--------

	documentation about the function shoudld be written using

	.. code-block:: cpp

		///////////////
		/// @brief :
		/// @param :
		/// @return:
		...

	this is mainly like the doxygene style documentation to identify parameters

spacing
-------

	Inside cpp and h add two blank line before begining the first implementation

includes
--------

	Always group and comment includes inside the cpp and header file, you may use the last folder level to group them together

	.. code-block:: cpp

		// STD
		#include <array>

		// Coordinate
		#include "includes/coordinate/planar_coordiante.h"

		// Projector
		#include "includes/coordinate/Projector/base.h"

Indentation
-----------

	Base indentation should be made with tabulation
	stylistic indentation should use space