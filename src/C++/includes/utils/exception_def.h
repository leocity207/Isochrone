#include "submodule/logger/includes/exception.h"

DECLARE_EXCEPTION(Exception,File_Open_Failed,"Could not open file.");
DECLARE_EXCEPTION(Exception,Reading_File_Error,"Error while reading the file.");

DECLARE_EXCEPTION(Exception,Station_Not_In_Schedule,"The station is not in the Schedule.");
DECLARE_EXCEPTION(Exception,No_Matching_Schedule,"No Schedule was found for the day");