<p align="right">
  <img width="25%" height="25%"src="../images/klepsydra_logo.jpg">
</p>

# group `kpsr-vision-application` 

This group of classes contains the API for the application development. That means that the client codes that involves the actual logic of the application, should use this and only this API.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[`kpsr::vision_ocv::ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData) | The [ImageData](#structkpsr_1_1vision__ocv_1_1ImageData) struct.

# struct `kpsr::vision_ocv::ImageData` 

```
struct kpsr::vision_ocv::ImageData
  : public Sensor
```  

The [ImageData](#structkpsr_1_1vision__ocv_1_1ImageData) struct.

Klepsydra Robotics 2017-2018.

2.0.1

Base image structure event data. Should be ROS and OpenCV compatible

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public cv::Mat `[`img`](#structkpsr_1_1vision__ocv_1_1ImageData_1a92545c38c2808b3c2b1b072242b6f10c) | img
`public inline  `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData_1a6952a2a68e35c02d67d6d4a60c00bdc6)`()` | [ImageData](#structkpsr_1_1vision__ocv_1_1ImageData).
`public inline  `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData_1ac9f87077e6c91397b27e088ba587af47)`(std::string frameId,int seq,cv::Mat img)` | [ImageData](#structkpsr_1_1vision__ocv_1_1ImageData).
`public inline  `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData_1aad4d0320908b56bcc9dc086ef6a26c74)`(const `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData)` & that)` | [ImageData](#structkpsr_1_1vision__ocv_1_1ImageData).
`public inline void `[`clone`](#structkpsr_1_1vision__ocv_1_1ImageData_1ac029172e0fa3af79bb4458414cb206e6)`(const `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData)` & that)` | clone

## Members

#### `public cv::Mat `[`img`](#structkpsr_1_1vision__ocv_1_1ImageData_1a92545c38c2808b3c2b1b072242b6f10c) 

img

#### `public inline  `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData_1a6952a2a68e35c02d67d6d4a60c00bdc6)`()` 

[ImageData](#structkpsr_1_1vision__ocv_1_1ImageData).

#### `public inline  `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData_1ac9f87077e6c91397b27e088ba587af47)`(std::string frameId,int seq,cv::Mat img)` 

[ImageData](#structkpsr_1_1vision__ocv_1_1ImageData).

#### Parameters
* `frameId` 

* `seq` 

* `img`

#### `public inline  `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData_1aad4d0320908b56bcc9dc086ef6a26c74)`(const `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData)` & that)` 

[ImageData](#structkpsr_1_1vision__ocv_1_1ImageData).

#### Parameters
* `that`

#### `public inline void `[`clone`](#structkpsr_1_1vision__ocv_1_1ImageData_1ac029172e0fa3af79bb4458414cb206e6)`(const `[`ImageData`](#structkpsr_1_1vision__ocv_1_1ImageData)` & that)` 

clone

#### Parameters
* `that`

