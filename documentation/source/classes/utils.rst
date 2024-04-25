Utils
=====

Generals
--------
.. doxygennamespace:: Generals

Daytimes
--------
.. doxygenclass:: DayTime
	:members:
	:undoc-members:
	:protected-members:

excpetion_defs
--------------
Look at :doc:`exceptions`

CTOR Helper
-----------

.. cpp:function:: DELETE_DEFAULT_CTOR(class_name)

	Delete the default constructor of the 'class_name'

.. cpp:function:: DEFAULT_DEFAULT_CTOR(class_name)

	Make the default constructor defaulted for 'class_name'

.. cpp:function:: DELETE_COPY(class_name)

	Delete copy for 'class_name' wether it's explicit or by assignation

.. cpp:function:: DEFAULT_COPY(class_name)

	Make the copy defaulted for 'class_name'

.. cpp:function:: DEFAULT_MOVE(class_name)

	Make move operation defaulted for 'class_name'

.. cpp:function:: DELETE_MOVE(class_name)

	Delete move for 'class_name' wether it's explicit or by assignation

.. cpp:function:: VIRTUAL_DESTRUCTOR(class_name)

	Make the destructor of 'class_name' virtual
