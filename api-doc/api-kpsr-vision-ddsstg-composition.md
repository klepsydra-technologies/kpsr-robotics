<p align="right">
  <img width="25%" height="25%"src="../images/klepsydra_logo.jpg">
</p>

# group `kpsr-vision-ddsstg-composition` 

This group of classes relates exclusively to the assemblying of the application for DDS middleware. In Spring terms, the 'wiring' of the application is done using this API. The use of DDS is light and minimal intrusion is needed as this modules does not peform any configuration at DDS level.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`kpsr::Mapper< kpsr::vision_ocv::ImageData, kpsr_dds_vision_ocv::ImageData >`](#classkpsr_1_1Mapper_3_01kpsr_1_1vision__ocv_1_1ImageData_00_01kpsr__dds__vision__ocv_1_1ImageData_01_4) | The Mapper<kpsr::vision::ImageData, kpsr_dds_vision::ImageData> class.

# class `kpsr::Mapper< kpsr::vision_ocv::ImageData, kpsr_dds_vision_ocv::ImageData >` 

The Mapper<kpsr::vision::ImageData, kpsr_dds_vision::ImageData> class.

Klepsydra Technologies 2019-2020.

2.1.0

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void `[`fromMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1vision__ocv_1_1ImageData_00_01kpsr__dds__vision__ocv_1_1ImageData_01_4_1a1bd9c8a0912fdf26f0095b59bbd1e27e)`(const kpsr_dds_vision_ocv::ImageData & message,`[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & event)` | fromMiddleware
`public inline void `[`toMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1vision__ocv_1_1ImageData_00_01kpsr__dds__vision__ocv_1_1ImageData_01_4_1ad20610b8fdd5af51c53e5e1a506a7122)`(const `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & event,kpsr_dds_vision_ocv::ImageData & message)` | toMiddleware

## Members

#### `public inline void `[`fromMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1vision__ocv_1_1ImageData_00_01kpsr__dds__vision__ocv_1_1ImageData_01_4_1a1bd9c8a0912fdf26f0095b59bbd1e27e)`(const kpsr_dds_vision_ocv::ImageData & message,`[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & event)` 

fromMiddleware

#### Parameters
* `message` 

* `event`

#### `public inline void `[`toMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1vision__ocv_1_1ImageData_00_01kpsr__dds__vision__ocv_1_1ImageData_01_4_1ad20610b8fdd5af51c53e5e1a506a7122)`(const `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & event,kpsr_dds_vision_ocv::ImageData & message)` 

toMiddleware

#### Parameters
* `event` 

* `message`

