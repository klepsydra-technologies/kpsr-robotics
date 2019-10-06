/* Copyright (C) Alerion Technologies - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Pablo Ghiglino <pablo@aleriontec.com>, March 2016
 */

#include <algorithm>
#include <dirent.h>
#include <sys/types.h>

#include "file_utils.h"

void FileUtils::getSortedListOfFilesInDir(std::string dirName, std::vector<std::string> * fileNameList) {
   
   dirent* de;
   DIR* dp;
   errno = 0;
   dp = opendir( dirName.c_str() );
   if (dp)
   {
      while (true)
      {
         errno = 0;
         de = readdir( dp );
         if (de == nullptr) break;
         fileNameList->push_back( std::string( de->d_name ) );
      }
      closedir( dp );
      std::sort( fileNameList->begin(), fileNameList->end() );
   }
}
