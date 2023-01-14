<p align="right">
  <img width="25%" height="25%"src="../images/klepsydra_logo.jpg">
</p>

# group `kpsr-geometry-dds-composition` 

This group of classes relates exclusively to the assemblying of the application for DDS middleware. In Spring terms, the 'wiring' of the application is done using this API. The use of DDS is light and minimal intrusion is needed as this modules does not peform any configuration at DDS level.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`kpsr::Mapper< kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData >`](#classkpsr_1_1Mapper_3_01kpsr_1_1geometry_1_1PoseEventData_00_01kpsr__dds__geometry_1_1PoseEventData_01_4) | The [Mapper<kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData>](#classkpsr_1_1Mapper_3_01kpsr_1_1geometry_1_1PoseEventData_00_01kpsr__dds__geometry_1_1PoseEventData_01_4) class.

# class `kpsr::Mapper< kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData >` 

The [Mapper<kpsr::geometry::PoseEventData, kpsr_dds_geometry::PoseEventData>](#classkpsr_1_1Mapper_3_01kpsr_1_1geometry_1_1PoseEventData_00_01kpsr__dds__geometry_1_1PoseEventData_01_4) class.

2023 Klepsydra Technologies AG

2.1.0

Geometry object mapper for DDS middleware

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void `[`fromMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1geometry_1_1PoseEventData_00_01kpsr__dds__geometry_1_1PoseEventData_01_4_1a680c2eeea47266aeded65f73efc0cd67)`(const kpsr_dds_geometry::PoseEventData & message,`[`kpsr::geometry::PoseEventData`](api-kpsr-geometry-application.md#structkpsr_1_1geometry_1_1PoseEventData)` & event)` | fromMiddleware
`public inline void `[`toMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1geometry_1_1PoseEventData_00_01kpsr__dds__geometry_1_1PoseEventData_01_4_1a1161a42f64bbe5f40ed8ffdddac065a0)`(const `[`kpsr::geometry::PoseEventData`](api-kpsr-geometry-application.md#structkpsr_1_1geometry_1_1PoseEventData)` & event,kpsr_dds_geometry::PoseEventData & message)` | toMiddleware

## Members

#### `public inline void `[`fromMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1geometry_1_1PoseEventData_00_01kpsr__dds__geometry_1_1PoseEventData_01_4_1a680c2eeea47266aeded65f73efc0cd67)`(const kpsr_dds_geometry::PoseEventData & message,`[`kpsr::geometry::PoseEventData`](api-kpsr-geometry-application.md#structkpsr_1_1geometry_1_1PoseEventData)` & event)` 

fromMiddleware

#### Parameters
* `message` 

* `event`

#### `public inline void `[`toMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1geometry_1_1PoseEventData_00_01kpsr__dds__geometry_1_1PoseEventData_01_4_1a1161a42f64bbe5f40ed8ffdddac065a0)`(const `[`kpsr::geometry::PoseEventData`](api-kpsr-geometry-application.md#structkpsr_1_1geometry_1_1PoseEventData)` & event,kpsr_dds_geometry::PoseEventData & message)` 

toMiddleware

#### Parameters
* `event` 

* `message`

