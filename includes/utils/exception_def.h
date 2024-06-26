#ifndef EXCEPTION_DEF_H
#define EXCEPTION_DEF_H

#include "submodule/logger/includes/exception.h"


//Resource Error
DECLARE_EXCEPTION(Exception,FILE_OPEN_FAILED,"Could not open file.");
DECLARE_EXCEPTION(Exception,READING_FILE_ERROR,"Error while reading the file.");
DECLARE_EXCEPTION(Exception,TIME_BADLY_FORMATED,"The time we are trying to read is badly formatted.");
DECLARE_EXCEPTION(Exception,ANGLE_BADLY_FORMATED,"The angle we are trying to read is badly formatted.");
DECLARE_EXCEPTION(Exception,TIMETABLE_BADLY_FORMATED,"The timetable is badly formatted.");

// Network Error
DECLARE_EXCEPTION(Exception,STATION_NOT_IN_SCHEDULE,"The station is not in the Timetable.");
DECLARE_EXCEPTION(Exception,NO_MATCHING_SCHEDULE,"No Timetable was found for the day");
DECLARE_EXCEPTION(Exception,CANNOT_ORDER_SAME_STATION,"The station Being compared order are the same.");
DECLARE_EXCEPTION(Exception,STATION_NOT_IN_NETWORK,"The station we are trying to find is not part of the network.");
DECLARE_EXCEPTION(Exception,STATION_NOT_IN_LIST, "The station we are trying to find is not part of the list.");

//General Error
DECLARE_EXCEPTION(Exception, ELEMENT_NOT_IN_LIST, "The element is not in the list.");
DECLARE_EXCEPTION(Exception, SIZE_IS_ZERO, "Size of the list is zero.");
DECLARE_EXCEPTION(Exception, NOT_RECTANGULAR, "Matrix is not rectangular.");
DECLARE_EXCEPTION(Exception, BAD_ANGULAR_VALUE_PROJECTION, "The Angular coordinate in parameter cannot be projected.");


#endif //EXCEPTION_DEF_H
