<p align="right">
  <img width="25%" height="25%"src="../images/klepsydra_logo.jpg">
</p>

# group `kpsr-sensors-application` 

This group of classes contains the API for the application development. That means that the client codes that involves the actual logic of the application, should use this and only this API.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`kpsr::Mapper< kpsr::sensors::LaserScanEvent, kpsr_dds_sensors::LaserScanEvent >`](#classkpsr_1_1Mapper_3_01kpsr_1_1sensors_1_1LaserScanEvent_00_01kpsr__dds__sensors_1_1LaserScanEvent_01_4) | The [Mapper<kpsr::sensors::LaserScanEvent, kpsr_dds_sensors::LaserScanEvent>](#classkpsr_1_1Mapper_3_01kpsr_1_1sensors_1_1LaserScanEvent_00_01kpsr__dds__sensors_1_1LaserScanEvent_01_4) class.
`class `[`kpsr::sensors::LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent) | The [LaserScanEvent](#classkpsr_1_1sensors_1_1LaserScanEvent) struct.

# class `kpsr::Mapper< kpsr::sensors::LaserScanEvent, kpsr_dds_sensors::LaserScanEvent >` 

The [Mapper<kpsr::sensors::LaserScanEvent, kpsr_dds_sensors::LaserScanEvent>](#classkpsr_1_1Mapper_3_01kpsr_1_1sensors_1_1LaserScanEvent_00_01kpsr__dds__sensors_1_1LaserScanEvent_01_4) class.

Klepsydra Technologies 2019-2020.

2.1.0

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void `[`fromMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1sensors_1_1LaserScanEvent_00_01kpsr__dds__sensors_1_1LaserScanEvent_01_4_1a179d7bd28b57bb421cde13d2c304d9e3)`(const kpsr_dds_sensors::LaserScanEvent & message,`[`kpsr::sensors::LaserScanEvent`](api-kpsr-sensors-application.md#classkpsr_1_1sensors_1_1LaserScanEvent)` & event)` | 
`public inline void `[`toMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1sensors_1_1LaserScanEvent_00_01kpsr__dds__sensors_1_1LaserScanEvent_01_4_1aaf695a2a9494032a32c03beae12f9b36)`(const `[`kpsr::sensors::LaserScanEvent`](api-kpsr-sensors-application.md#classkpsr_1_1sensors_1_1LaserScanEvent)` & event,kpsr_dds_sensors::LaserScanEvent & message)` | 

## Members

#### `public inline void `[`fromMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1sensors_1_1LaserScanEvent_00_01kpsr__dds__sensors_1_1LaserScanEvent_01_4_1a179d7bd28b57bb421cde13d2c304d9e3)`(const kpsr_dds_sensors::LaserScanEvent & message,`[`kpsr::sensors::LaserScanEvent`](api-kpsr-sensors-application.md#classkpsr_1_1sensors_1_1LaserScanEvent)` & event)` 

#### `public inline void `[`toMiddleware`](#classkpsr_1_1Mapper_3_01kpsr_1_1sensors_1_1LaserScanEvent_00_01kpsr__dds__sensors_1_1LaserScanEvent_01_4_1aaf695a2a9494032a32c03beae12f9b36)`(const `[`kpsr::sensors::LaserScanEvent`](api-kpsr-sensors-application.md#classkpsr_1_1sensors_1_1LaserScanEvent)` & event,kpsr_dds_sensors::LaserScanEvent & message)` 

# class `kpsr::sensors::LaserScanEvent` 

```
class kpsr::sensors::LaserScanEvent
  : public Sensor
```  

The [LaserScanEvent](#classkpsr_1_1sensors_1_1LaserScanEvent) struct.

Klepsydra Technologies 2019-2020.

2.1.0

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float `[`angle_min`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a4c8cab70305e08de8c9b06aa781f380f) | angle_min
`public float `[`angle_max`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a3e2c0bff6c19bdaf9790ec6d9b6066ce) | angle_max
`public float `[`angle_increment`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a25d142ee6a5c402caee6d0be638f0984) | angle_increment
`public float `[`time_increment`](#classkpsr_1_1sensors_1_1LaserScanEvent_1ad526526b946387f73a06b5cc0c037994) | time_increment
`public float `[`scan_time`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a035d6a31d25fad3b2608ae9f37c031bd) | scan_time
`public float `[`range_min`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a5051dcda793cd4fb95ead16da78b1ee2) | range_min
`public float `[`range_max`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a38f338e899ce561680a42ce2f55c6a41) | range_max
`public std::vector< float > `[`ranges`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a1da5127d534a6a750313a0c2bc4c0493) | ranges
`public std::vector< float > `[`intensities`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a7a5f460be1ee6029ea22718a77e1e4e9) | intensities
`public inline  `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent_1abdc7e4f1f6d53d439cfcbb90677aa608)`()` | [LaserScanEvent](#classkpsr_1_1sensors_1_1LaserScanEvent).
`public inline  `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a9731ee6d4d12b008950922079ab337d9)`(std::string frameId,int seq,long timestamp,float angle_min,float angle_max,float angle_increment,float time_increment,float scan_time,float range_min,float range_max,std::vector< float > ranges,std::vector< float > intensities)` | [LaserScanEvent](#classkpsr_1_1sensors_1_1LaserScanEvent).
`public inline  `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a12e9f1d29a0f86312ad16e0d93b54a3b)`(const `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent)` & that)` | [LaserScanEvent](#classkpsr_1_1sensors_1_1LaserScanEvent).
`public inline void `[`clone`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a247e86fc338c51babfb2507f5219823d)`(const `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent)` & that)` | clone

## Members

#### `public float `[`angle_min`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a4c8cab70305e08de8c9b06aa781f380f) 

angle_min

#### `public float `[`angle_max`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a3e2c0bff6c19bdaf9790ec6d9b6066ce) 

angle_max

#### `public float `[`angle_increment`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a25d142ee6a5c402caee6d0be638f0984) 

angle_increment

#### `public float `[`time_increment`](#classkpsr_1_1sensors_1_1LaserScanEvent_1ad526526b946387f73a06b5cc0c037994) 

time_increment

#### `public float `[`scan_time`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a035d6a31d25fad3b2608ae9f37c031bd) 

scan_time

#### `public float `[`range_min`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a5051dcda793cd4fb95ead16da78b1ee2) 

range_min

#### `public float `[`range_max`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a38f338e899ce561680a42ce2f55c6a41) 

range_max

#### `public std::vector< float > `[`ranges`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a1da5127d534a6a750313a0c2bc4c0493) 

ranges

#### `public std::vector< float > `[`intensities`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a7a5f460be1ee6029ea22718a77e1e4e9) 

intensities

#### `public inline  `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent_1abdc7e4f1f6d53d439cfcbb90677aa608)`()` 

[LaserScanEvent](#classkpsr_1_1sensors_1_1LaserScanEvent).

#### `public inline  `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a9731ee6d4d12b008950922079ab337d9)`(std::string frameId,int seq,long timestamp,float angle_min,float angle_max,float angle_increment,float time_increment,float scan_time,float range_min,float range_max,std::vector< float > ranges,std::vector< float > intensities)` 

[LaserScanEvent](#classkpsr_1_1sensors_1_1LaserScanEvent).

#### Parameters
* `frameId` 

* `seq` 

* `angle_min` 

* `angle_max` 

* `angle_increment` 

* `time_increment` 

* `scan_time` 

* `range_min` 

* `range_max` 

* `ranges` 

* `intensities`

#### `public inline  `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a12e9f1d29a0f86312ad16e0d93b54a3b)`(const `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent)` & that)` 

[LaserScanEvent](#classkpsr_1_1sensors_1_1LaserScanEvent).

#### Parameters
* `that`

#### `public inline void `[`clone`](#classkpsr_1_1sensors_1_1LaserScanEvent_1a247e86fc338c51babfb2507f5219823d)`(const `[`LaserScanEvent`](#classkpsr_1_1sensors_1_1LaserScanEvent)` & that)` 

clone

#### Parameters
* `that`

