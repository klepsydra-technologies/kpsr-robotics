/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/

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
         if (de == NULL) break;
         fileNameList->push_back( std::string( de->d_name ) );
      }
      closedir( dp );
      std::sort( fileNameList->begin(), fileNameList->end() );
   }
}
