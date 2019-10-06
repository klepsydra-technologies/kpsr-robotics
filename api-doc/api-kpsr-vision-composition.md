<p align="right">
  <img width="25%" height="25%"src="../images/klepsydra_logo.jpg">
</p>

# group `kpsr-vision-composition` 

This group of classes relates exclusively to the assemblying of the application. In Spring terms, the 'wiring' of the application is done using this API.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`kpsr::vision_ocv::mem::BasicVisionMiddlewareProvider`](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider) | The [BasicVisionMiddlewareProvider](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider) class.
`class `[`kpsr::vision_ocv::ImageDataFactory`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory) | The [ImageDataFactory](#classkpsr_1_1vision__ocv_1_1ImageDataFactory) class.

# class `kpsr::vision_ocv::mem::BasicVisionMiddlewareProvider` 

The [BasicVisionMiddlewareProvider](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider) class.

Klepsydra Technologies 2019-2020.

2.1.0

A safe queue provider wrapper that adds the vision factory performance tool. Its use is very simple as the following example shows: 
```cpp
//Create provider and start it;
kpsr::vision_ocv::BasicVisionMiddlewareProvider provider(nullptr, 1080, 2040, 16, "body", "raw_image", 4, 6, false);
provider.underlying->start();

//Create a publisher;
kpsr::Publisher<kpsr::vision_ocv::ImageData> * publisher = provider.underlying->getPublisher();

//Create a subscriber;
kpsr::Subscriber<kpsr::vision_ocv::ImageData> * subscriber = provider.underlying->getSubscriber();
```

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`kpsr::vision_ocv::ImageDataFactory`](api-kpsr-vision-composition.md#classkpsr_1_1vision__ocv_1_1ImageDataFactory)` * `[`_imageDataFactory`](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider_1aabfd72288c504dc29bf2f84f0f44c584) | _imageDataFactory
`public kpsr::mem::BasicMiddlewareProvider< `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` > * `[`underlying`](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider_1a74bb07e59c15f2a44dcae2f0f304b9f4) | underlying
`public  `[`BasicVisionMiddlewareProvider`](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider_1a7bc1c8ce6e393feaa49f0d6a2e251a40)`(Container * container,int rows,int cols,int type,std::string frameId,std::string eventName,int queueSize,int poolSize,bool discardItemsWhenFull)` | [BasicVisionMiddlewareProvider](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider).

## Members

#### `public `[`kpsr::vision_ocv::ImageDataFactory`](api-kpsr-vision-composition.md#classkpsr_1_1vision__ocv_1_1ImageDataFactory)` * `[`_imageDataFactory`](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider_1aabfd72288c504dc29bf2f84f0f44c584) 

_imageDataFactory

#### `public kpsr::mem::BasicMiddlewareProvider< `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` > * `[`underlying`](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider_1a74bb07e59c15f2a44dcae2f0f304b9f4) 

underlying

#### `public  `[`BasicVisionMiddlewareProvider`](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider_1a7bc1c8ce6e393feaa49f0d6a2e251a40)`(Container * container,int rows,int cols,int type,std::string frameId,std::string eventName,int queueSize,int poolSize,bool discardItemsWhenFull)` 

[BasicVisionMiddlewareProvider](#classkpsr_1_1vision__ocv_1_1mem_1_1BasicVisionMiddlewareProvider).

#### Parameters
* `container` 

* `rows` 

* `cols` 

* `type` 

* `frameId` 

* `eventName` 

* `queueSize` 

* `poolSize` 

* `discardItemsWhenFull`

# class `kpsr::vision_ocv::ImageDataFactory` 

The [ImageDataFactory](#classkpsr_1_1vision__ocv_1_1ImageDataFactory) class.

Klepsydra Robotics 2017-2018.

2.0.1

This is a vision performance facility class that has several functions that can be used in conjuntion with the disruptor and object pool classes. It handles the allocation of images, copy and resizing.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::function< std::unique_ptr< `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData) >void)`> `[`creatorFunction`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a422d5d0fb6c14c348e2caeb6a9e9fad2) | creatorFunction Function that creates new images based on the rows, cols and type members.
`public std::function< void(`[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData) &)`> `[`initializerFunction`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1ab7d2c6d1643a24c6653975d38a7d72a5) | initializerFunction Resize of the image to meet the rows, cols and type member.
`public std::function< void(const `[`kpsr::vision_ocv::ImageData](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData) &, [kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData) &)`> `[`eventClonerFunction`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a3f5c44c1b3671516067e8bf9bb8ef187) | eventClonerFunction Cloner function that does not perform any resizing.
`public  `[`ImageDataFactory`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1acd8ac51a990fdbb9e92d0364bccf90df)`(int rows,int cols,int type,std::string frameId)` | [ImageDataFactory](#classkpsr_1_1vision__ocv_1_1ImageDataFactory).
`protected std::unique_ptr< `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` > `[`creator`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a420632ee68c82405cce56711813f497b)`()` | 
`protected void `[`initializer`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a0739531febd35bbd1f8cac556a95691b)`(`[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & imageEvent)` | 
`protected void `[`eventCloner`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a6380b5297d4c427cee33eedb5667696e)`(const `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & source,`[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & target)` | 

## Members

#### `public std::function< std::unique_ptr< `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData) >void)`> `[`creatorFunction`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a422d5d0fb6c14c348e2caeb6a9e9fad2) 

creatorFunction Function that creates new images based on the rows, cols and type members.

#### `public std::function< void(`[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData) &)`> `[`initializerFunction`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1ab7d2c6d1643a24c6653975d38a7d72a5) 

initializerFunction Resize of the image to meet the rows, cols and type member.

#### `public std::function< void(const `[`kpsr::vision_ocv::ImageData](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData) &, [kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData) &)`> `[`eventClonerFunction`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a3f5c44c1b3671516067e8bf9bb8ef187) 

eventClonerFunction Cloner function that does not perform any resizing.

#### `public  `[`ImageDataFactory`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1acd8ac51a990fdbb9e92d0364bccf90df)`(int rows,int cols,int type,std::string frameId)` 

[ImageDataFactory](#classkpsr_1_1vision__ocv_1_1ImageDataFactory).

#### Parameters
* `rows` 

* `cols` 

* `type` 

* `frameId`

#### `protected std::unique_ptr< `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` > `[`creator`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a420632ee68c82405cce56711813f497b)`()` 

#### `protected void `[`initializer`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a0739531febd35bbd1f8cac556a95691b)`(`[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & imageEvent)` 

#### `protected void `[`eventCloner`](#classkpsr_1_1vision__ocv_1_1ImageDataFactory_1a6380b5297d4c427cee33eedb5667696e)`(const `[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & source,`[`kpsr::vision_ocv::ImageData`](api-kpsr-vision-application.md#structkpsr_1_1vision__ocv_1_1ImageData)` & target)` 

