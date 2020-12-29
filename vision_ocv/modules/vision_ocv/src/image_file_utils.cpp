/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*                            All Rights Reserved.
*
*  This file is subject to the terms and conditions defined in
*  file 'LICENSE.md', which is part of this source code package.
*
*  NOTICE:  All information contained herein is, and remains the property of Klepsydra
*  Technologies GmbH and its suppliers, if any. The intellectual and technical concepts
*  contained herein are proprietary to Klepsydra Technologies GmbH and its suppliers and
*  may be covered by Swiss and Foreign Patents, patents in process, and are protected by
*  trade secret or copyright law. Dissemination of this information or reproduction of
*  this material is strictly forbidden unless prior written permission is obtained from
*  Klepsydra Technologies GmbH.
*
*****************************************************************************/

#include <algorithm>
#include <dirent.h>
#include <sys/types.h>

#include <klepsydra/vision_ocv/image_file_utils.h>

void kpsr::vision_ocv::ImageFileUtils::getSortedListOfFilesInDir(const std::string & dirName, std::vector<std::string> & fileNameList) {
   
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
         fileNameList.push_back( std::string( de->d_name ) );
      }
      closedir( dp );
      std::sort( fileNameList.begin(), fileNameList.end() );
   }
}
