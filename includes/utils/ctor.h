#ifndef CTOR_H
#define CTOR_H

#define DELETE_DEFAULT(class_name) class_name() = delete;

#define DELETE_COPY(class_name) \
	class_name(const class_name&) = delete;\
	class_name& operator=(const class_name&) = delete;

#define DEFAULT_MOVE(class_name) \
	class_name(class_name&&) noexcept = default;\
	class_name& operator=(class_name&&) noexcept = default;

#define DELETE_MOVE(class_name) \
	class_name(class_name&&) noexcept = delete;\
	class_name& operator=(class_name&&) noexcept = delete;

#endif // !CTOR_H
