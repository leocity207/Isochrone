* No raw pointer
* pointer should always be wrappet inside Memory::Owned or Memory::Unowned
* Memory::Unowned should only be used for interface with other library
* Exception Type are always in majuscule
* Snake_Case for function
* snake_case for variable
* class should have the folowing tag and order


////////
/// CTOR
public:
	...
protected:
	...
private:
	...

///////////
/// METHODS
public:
	...
protected:
	...
private:
	...

//////////////////
/// STATIC METHODS
public:
	...
protected:
	...
private:
	...

//////////////
/// ATTRIBUTES
public:
	...
protected:
	...
private:
	...

 * inside the contructor
   * use the "includes/utils/ctor.h fiels to tell about how the class should handle construction
 * documentation about the function shoudld be in the doxygen style
 * inside cpp add two blank line before begining the first implementation
 * always group and comment includes