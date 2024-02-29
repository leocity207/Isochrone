#ifndef CTOR_H
#define CTOR_H


#define DELETE_DEFAULT_CTOR(class_name) class_name() = delete;
#define DEFAULT_DEFAULT_CTOR(class_name) class_name() = default;

#define DELETE_COPY(class_name) \
	class_name(const class_name&) = delete;\
	class_name& operator=(const class_name&) = delete;

#define DEFAULT_COPY(class_name) \
	class_name(const class_name&) = default;\
	class_name& operator=(const class_name&) = default;

#define DEFAULT_MOVE(class_name) \
	class_name(class_name&&) = default;\
	class_name& operator=(class_name&&) = default;

#define DELETE_MOVE(class_name) \
	class_name(class_name&&) = delete;\
	class_name& operator=(class_name&&) = delete;

#define VIRTUAL_DESTRUCTOR(class_name) \
	virtual ~class_name() {};\


#endif // !CTOR_H
