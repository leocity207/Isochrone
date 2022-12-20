#ifndef EXCEPTION_DEF_H
#define EXCEPTION_DEF_H

#include "submodule/logger/includes/exception.h"

DECLARE_EXCEPTION(Exception,File_Open_Failed,"Could not open file.");
DECLARE_EXCEPTION(Exception,Reading_File_Error,"Error while reading the file.");
DECLARE_EXCEPTION(Exception,Time_Badly_Formatted,"The time we are trying to read is badly formatted.");

DECLARE_EXCEPTION(Exception,Station_Not_In_Schedule,"The station is not in the Schedule.");
DECLARE_EXCEPTION(Exception,No_Matching_Schedule,"No Schedule was found for the day");

#endif //EXCEPTION_DEF_H