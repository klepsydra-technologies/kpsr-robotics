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

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

/**
 * @brief The FileUtils class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.1.0
 */
class FileUtils {
   public:
      static void getSortedListOfFilesInDir(std::string dirName, std::vector<std::string> * fileNameList);
};

#endif
