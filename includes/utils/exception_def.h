#ifndef EXCEPTION_DEF_H
#define EXCEPTION_DEF_H

#include "submodule/logger/includes/exception.h"

//Resource Error
DECLARE_EXCEPTION(Exception,FILE_OPEN_FAILED,"Could not open file.");
DECLARE_EXCEPTION(Exception,READING_FILE_ERROR,"Error while reading the file.");
DECLARE_EXCEPTION(Exception,TIME_BADLY_FORMATED,"The time we are trying to read is badly formatted.");
DECLARE_EXCEPTION(Exception,ANGLE_BADLY_FORMATED,"The angle we are trying to read is badly formatted.");

// Network Error
DECLARE_EXCEPTION(Exception,Station_Not_In_Schedule,"The station is not in the Schedule.");
DECLARE_EXCEPTION(Exception,No_Matching_Schedule,"No Schedule was found for the day");
DECLARE_EXCEPTION(Exception,Cannot_Order_Same_Station,"The station Being compared order are the same.");
DECLARE_EXCEPTION(Exception,Station_Not_In_Network,"The station we are trying to find is not part of the network.");

#endif //EXCEPTION_DEF_H
