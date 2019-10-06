<p align="right">
  <img width="25%" height="25%"src="../images/klepsydra_logo.jpg">
</p>

# group `kpsr-geometry-application` 

This group of classes contains the API for the application development. That means that the client codes that involves the actual logic of the application, should use this and only this API.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[`kpsr::geometry::PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData) | The [PoseEventData](#structkpsr_1_1geometry_1_1PoseEventData) struct.

# struct `kpsr::geometry::PoseEventData` 

```
struct kpsr::geometry::PoseEventData
  : public Sensor
```  

The [PoseEventData](#structkpsr_1_1geometry_1_1PoseEventData) struct.

Klepsydra Technologies 2019-2020.

2.1.0

Pose specific data. It should be compatible with ROS and Mavlink.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`eulerAvailable`](#structkpsr_1_1geometry_1_1PoseEventData_1a82292bec9e2b551a98d9ab4a1c436fa4) | eulerAvailable
`public bool `[`posCovarianceAvailable`](#structkpsr_1_1geometry_1_1PoseEventData_1a36b9d6406431fbc438dece1d37e951b2) | posCovarianceAvailable
`public double `[`x`](#structkpsr_1_1geometry_1_1PoseEventData_1a0a28028ad207166b8e15d4406d7fe698) | x
`public double `[`y`](#structkpsr_1_1geometry_1_1PoseEventData_1aeb935f23f0d5832fdddc1ed58b548d0d) | y
`public double `[`z`](#structkpsr_1_1geometry_1_1PoseEventData_1a7bada2f7e635ef40d281cb57883d6f1d) | z
`public double `[`roll`](#structkpsr_1_1geometry_1_1PoseEventData_1acb20bd6ce639d242823463f7663681a4) | roll
`public double `[`pitch`](#structkpsr_1_1geometry_1_1PoseEventData_1aa121791209594f6e9f3f532fd18028d7) | pitch
`public double `[`yaw`](#structkpsr_1_1geometry_1_1PoseEventData_1a098a9951fb7f65a2af65efaa52cbb258) | yaw
`public double `[`qx`](#structkpsr_1_1geometry_1_1PoseEventData_1a8edc03d2f3c0e462135a3c882cf925af) | qx
`public double `[`qy`](#structkpsr_1_1geometry_1_1PoseEventData_1ab47887df750383804f69fcb96b2a604a) | qy
`public double `[`qz`](#structkpsr_1_1geometry_1_1PoseEventData_1a496948911e58f35c4494b5275d4441e0) | qz
`public double `[`qw`](#structkpsr_1_1geometry_1_1PoseEventData_1ad320f04f06b7cf47482a3bc9d2098ae3) | qw
`public std::vector< double > `[`positionCovariance`](#structkpsr_1_1geometry_1_1PoseEventData_1a0b76e46e6c7b243744d1bc139e4c7ce0) | positionCovariance
`public inline  `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData_1a822f1e9029697fc06e4e41a70dadeef8)`()` | 
`public inline  `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData_1a33f2198d60b7af6e3fcb3d1176e2b68b)`(std::string frameId,int seq,bool eulerAvailable,bool posCovarianceAvailable,double x,double y,double z,double roll,double pitch,double yaw,double qx,double qy,double qz,double qw,std::vector< double > positionCovariance)` | [PoseEventData](#structkpsr_1_1geometry_1_1PoseEventData).
`public inline  `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData_1a6f0fba99df899f6e1921e918ce5b6294)`(const `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData)` & that)` | [PoseEventData](#structkpsr_1_1geometry_1_1PoseEventData).
`public inline void `[`clone`](#structkpsr_1_1geometry_1_1PoseEventData_1aa7b259445e3c109241338ae330b6211f)`(const `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData)` & that)` | clone

## Members

#### `public bool `[`eulerAvailable`](#structkpsr_1_1geometry_1_1PoseEventData_1a82292bec9e2b551a98d9ab4a1c436fa4) 

eulerAvailable

#### `public bool `[`posCovarianceAvailable`](#structkpsr_1_1geometry_1_1PoseEventData_1a36b9d6406431fbc438dece1d37e951b2) 

posCovarianceAvailable

#### `public double `[`x`](#structkpsr_1_1geometry_1_1PoseEventData_1a0a28028ad207166b8e15d4406d7fe698) 

x

#### `public double `[`y`](#structkpsr_1_1geometry_1_1PoseEventData_1aeb935f23f0d5832fdddc1ed58b548d0d) 

y

#### `public double `[`z`](#structkpsr_1_1geometry_1_1PoseEventData_1a7bada2f7e635ef40d281cb57883d6f1d) 

z

#### `public double `[`roll`](#structkpsr_1_1geometry_1_1PoseEventData_1acb20bd6ce639d242823463f7663681a4) 

roll

#### `public double `[`pitch`](#structkpsr_1_1geometry_1_1PoseEventData_1aa121791209594f6e9f3f532fd18028d7) 

pitch

#### `public double `[`yaw`](#structkpsr_1_1geometry_1_1PoseEventData_1a098a9951fb7f65a2af65efaa52cbb258) 

yaw

#### `public double `[`qx`](#structkpsr_1_1geometry_1_1PoseEventData_1a8edc03d2f3c0e462135a3c882cf925af) 

qx

#### `public double `[`qy`](#structkpsr_1_1geometry_1_1PoseEventData_1ab47887df750383804f69fcb96b2a604a) 

qy

#### `public double `[`qz`](#structkpsr_1_1geometry_1_1PoseEventData_1a496948911e58f35c4494b5275d4441e0) 

qz

#### `public double `[`qw`](#structkpsr_1_1geometry_1_1PoseEventData_1ad320f04f06b7cf47482a3bc9d2098ae3) 

qw

#### `public std::vector< double > `[`positionCovariance`](#structkpsr_1_1geometry_1_1PoseEventData_1a0b76e46e6c7b243744d1bc139e4c7ce0) 

positionCovariance

#### `public inline  `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData_1a822f1e9029697fc06e4e41a70dadeef8)`()` 

#### `public inline  `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData_1a33f2198d60b7af6e3fcb3d1176e2b68b)`(std::string frameId,int seq,bool eulerAvailable,bool posCovarianceAvailable,double x,double y,double z,double roll,double pitch,double yaw,double qx,double qy,double qz,double qw,std::vector< double > positionCovariance)` 

[PoseEventData](#structkpsr_1_1geometry_1_1PoseEventData).

#### Parameters
* `frameId` 

* `seq` 

* `eulerAvailable` 

* `posCovarianceAvailable` 

* `x` 

* `y` 

* `z` 

* `roll` 

* `pitch` 

* `yaw` 

* `qx` 

* `qy` 

* `qz` 

* `qw` 

* `positionCovariance`

#### `public inline  `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData_1a6f0fba99df899f6e1921e918ce5b6294)`(const `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData)` & that)` 

[PoseEventData](#structkpsr_1_1geometry_1_1PoseEventData).

#### Parameters
* `that`

#### `public inline void `[`clone`](#structkpsr_1_1geometry_1_1PoseEventData_1aa7b259445e3c109241338ae330b6211f)`(const `[`PoseEventData`](#structkpsr_1_1geometry_1_1PoseEventData)` & that)` 

clone

#### Parameters
* `that`

