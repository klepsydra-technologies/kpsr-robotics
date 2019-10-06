/* Copyright (C) Alerion Technologies - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Pablo Ghiglino <pablo@aleriontec.com>, March 2016
 */

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

// read_directory()
//   Return an ASCII-sorted vector of filename entries in a given directory.
//   If no path is specified, the current working directory is used.
//
//   Always check the value of the global 'errno' variable after using this
//   function to see if anything went wrong. (It will be zero if all is well.)
//
class FileUtils {
   public:
      static void getSortedListOfFilesInDir(std::string dirName, std::vector<std::string> * fileNameList);
};

#endif
