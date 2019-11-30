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

#include "image_encoding_helper.h"
#include <cv_bridge/cv_bridge.h>

void kpsr::vision_ocv::ros_mdlw::ImageEncodingHelper::cvTypeToRosImageEncoding(int cvType, char * rosImageEncoding) {
    const char * encoding = NULL;

    if (cvType==CV_8UC1) encoding = "8UC1";
    if (cvType==CV_8UC2) encoding = "8UC2";
    if (cvType==CV_8UC3) encoding = "8UC3";
    if (cvType==CV_8UC4) encoding = "8UC4";
    if (cvType==CV_8SC1) encoding = "8SC1";
    if (cvType==CV_8SC2) encoding = "8SC2";
    if (cvType==CV_8SC3) encoding = "8SC3";
    if (cvType==CV_8SC4) encoding = "8SC4";
    if (cvType==CV_16UC1) encoding = "16UC1";
    if (cvType==CV_16UC2) encoding = "16UC2";
    if (cvType==CV_16UC3) encoding = "16UC3";
    if (cvType==CV_16UC4) encoding = "16UC4";
    if (cvType==CV_16SC1) encoding = "16SC1";
    if (cvType==CV_16SC2) encoding = "16SC2";
    if (cvType==CV_16SC3) encoding = "16SC3";
    if (cvType==CV_16SC4) encoding = "16SC4";
    if (cvType==CV_32SC1) encoding = "32SC1";
    if (cvType==CV_32SC2) encoding = "32SC2";
    if (cvType==CV_32SC3) encoding = "32SC3";
    if (cvType==CV_32SC4) encoding = "32SC4";
    if (cvType==CV_32FC1) encoding = "32FC1";
    if (cvType==CV_32FC2) encoding = "32FC2";
    if (cvType==CV_32FC3) encoding = "32FC3";
    if (cvType==CV_32FC4) encoding = "32FC4";
    if (cvType==CV_64FC1) encoding = "64FC1";
    if (cvType==CV_64FC2) encoding = "64FC2";
    if (cvType==CV_64FC3) encoding = "64FC3";
    if (cvType==CV_64FC4) encoding = "64FC4";
    if (cvType==CV_8UC3) encoding = "bgr8";  //Opencv uses BGR
    if (cvType==CV_8UC4) encoding = "bgra8";
    if (cvType==CV_8UC1) encoding = "mono8";
    if (cvType==CV_16UC1) encoding = "mono16";
    if (cvType==CV_8UC2) encoding = "yuv422";
    //if (cvType==CV_8UC3) encoding = "yuv";
    if (cvType==CV_8UC1) encoding = "bayer_bggr8";
    if (cvType==CV_16UC1) encoding = "bayer_bggr16";

    if (encoding != NULL) {
        std::string strEncoding(encoding);
        std::size_t length = strEncoding.copy(rosImageEncoding, 20);
        rosImageEncoding[length]='\0';
    }
}

int kpsr::vision_ocv::ros_mdlw::ImageEncodingHelper::cvTypeFromRosImageEncoding(const char * rosImgEncoding) {
    int cvType;

    if(strcmp(rosImgEncoding,"8UC1") == 0) cvType=CV_8UC1;
    else if(strcmp(rosImgEncoding,"8UC2") == 0) cvType=CV_8UC2;
    else if(strcmp(rosImgEncoding,"8UC3") == 0) cvType=CV_8UC3;
    else if(strcmp(rosImgEncoding,"8UC4") == 0) cvType=CV_8UC4;
    else if(strcmp(rosImgEncoding,"8SC1") == 0) cvType==CV_8SC1;
    else if(strcmp(rosImgEncoding,"8SC2") == 0) cvType==CV_8SC2;
    else if(strcmp(rosImgEncoding,"8SC3") == 0) cvType==CV_8SC3;
    else if(strcmp(rosImgEncoding,"8SC4") == 0) cvType==CV_8SC4;
    else if(strcmp(rosImgEncoding,"16UC1") == 0) cvType=CV_16UC1;
    else if(strcmp(rosImgEncoding,"16UC2") == 0) cvType=CV_16UC2;
    else if(strcmp(rosImgEncoding,"16UC3") == 0) cvType=CV_16UC3;
    else if(strcmp(rosImgEncoding,"16UC4") == 0) cvType=CV_16UC4;
    else if(strcmp(rosImgEncoding,"16SC1") == 0) cvType=CV_16SC1;
    else if(strcmp(rosImgEncoding,"16SC2") == 0) cvType=CV_16SC2;
    else if(strcmp(rosImgEncoding,"16SC3") == 0) cvType=CV_16SC3;
    else if(strcmp(rosImgEncoding,"16SC4") == 0) cvType=CV_16SC4;
    else if(strcmp(rosImgEncoding,"32SC1") == 0) cvType=CV_32SC1;
    else if(strcmp(rosImgEncoding,"32SC2") == 0) cvType=CV_32SC2;
    else if(strcmp(rosImgEncoding,"32SC3") == 0) cvType=CV_32SC3;
    else if(strcmp(rosImgEncoding,"32SC4") == 0) cvType=CV_32SC4;
    else if(strcmp(rosImgEncoding,"32FC1") == 0) cvType=CV_32FC1;
    else if(strcmp(rosImgEncoding,"32FC2") == 0) cvType=CV_32FC2;
    else if(strcmp(rosImgEncoding,"32FC3") == 0) cvType=CV_32FC3;
    else if(strcmp(rosImgEncoding,"32FC4") == 0) cvType=CV_32FC4;
    else if(strcmp(rosImgEncoding,"64FC1") == 0) cvType=CV_64FC1;
    else if(strcmp(rosImgEncoding,"64FC2") == 0) cvType=CV_64FC2;
    else if(strcmp(rosImgEncoding,"64FC3") == 0) cvType=CV_64FC3;
    else if(strcmp(rosImgEncoding,"64FC4") == 0) cvType=CV_64FC4;
    else if(strcmp(rosImgEncoding,"bgr8") == 0) cvType=CV_8UC3;		//Opencv uses BGR
    else if(strcmp(rosImgEncoding,"bgra8") == 0) cvType=CV_8UC4;
    else if(strcmp(rosImgEncoding,"mono8") == 0) cvType=CV_8UC1;
    else if(strcmp(rosImgEncoding,"mono16") == 0) cvType=CV_16UC1;
    else if(strcmp(rosImgEncoding,"yuv422") == 0) cvType=CV_8UC2;
    else if(strcmp(rosImgEncoding,"yuv") == 0) cvType=CV_8UC3;
    else if(strcmp(rosImgEncoding,"bayer_bggr8") == 0) cvType=CV_8UC1;
    else if(strcmp(rosImgEncoding,"bayer_bggr16") == 0) cvType=CV_16UC1;

    //delete rosImgEncoding;

    return cvType;
}
