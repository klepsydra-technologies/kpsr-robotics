/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2020-2022  Klepsydra Technologies GmbH
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

#ifndef IMAGE_FILE_UTILS_H
#define IMAGE_FILE_UTILS_H

#include <string>
#include <vector>

namespace kpsr {
namespace vision_ocv {
/**
 * @brief The ImageFileUtils class
 *
 * @details This class reads all images in a folder and provide names back in the passed reference vector.
 */
class ImageFileUtils {
public:
    /**
       * @brief getSortedListOfFilesInDir
       * @param dirName
       * @param fileNameList
       */
    static void getSortedListOfFilesInDir(const std::string & dirName, std::vector<std::string> & fileNameList);
};
}
}

#endif
