Setup
=====

project
-------
	project require C++20 as minimum requirement
	and cmake 3.22.1

	project as only been tested using MSVC compiler 

documentation
-------------
	generating the documentation require **python 3.10** with Sphinx

	.. code-block:: 

		pip install sphinx

	since the documentation use graphics to be generated you will also generate graphviz from <https://graphviz.org/>

	automatic graphical theming for the dot files also need the pydot 

	.. code-block::

		pip install pydot
