<p align="right">
  <img width="25%" height="25%"src="./images/klepsydra_logo.jpg">
</p>

Build | Status
--- | ---
Minimal | [![Build Status](https://jenkins1.klepsydra.com/buildStatus/icon?job=kpsr-robotics%2Fmaster)](https://jenkins1.klepsydra.com/job/kpsr-robotics/job/master/)
ZMQ | [![Build Status](https://jenkins1.klepsydra.com/buildStatus/icon?job=kpsr-zmq-core%2Fmaster)](https://jenkins1.klepsydra.com/view/Core/job/kpsr-zmq-core/job/master/)
ROS | [![Build Status](https://jenkins1.klepsydra.com/buildStatus/icon?job=kpsr-zmq-robotics%2Fmaster)](https://jenkins1.klepsydra.com/job/kpsr-zmq-robotics/job/master/)

# Installation Instructions

## System dependencies

* Ubuntu 14.04 or above
* ConcurrentQueue (https://github.com/klepsydra-technologies/concurrentqueue)
* Cereal (https://github.com/klepsydra-technologies/cereal)
* ROS Indigo or above (optional)
* DDS (optional)
* Cmake 3.5.1 or above
* gcc for C++11 5.4.0 or above.
* Doxygen (optional)
* Moxygen (https://github.com/sourcey/moxygen) (optional)
* Open CV (Version 4.2.x) (optional)
* Ros Vision Package

## Klepsydra dependencies

* kpsr-core

## System installation

	sudo apt install build-essentials
	sudo apt install git
	sudo apt install cmake

## Installation

Given ```$KLEPSYDRA_HOME```, for example ```$HOME/klepsydra```:

```
git clone https://github.com/kpsr-devs/kpsr-robotics.git
cd kpsr-robotics
git submodule update --init
mkdir build
cd build
cmake ..
make
make test
sudo make install
```

This will install the klespydra robotics in

	/opt/klepsydra	

The cmake has the following options:
* -DKPSR_WITH_OCV=true for building the Open CV vision module
* -DKPSR_WITH_DDS=true for building the DDS binding
* -DKPSR_WITH_ZMQ=true for building the ZMQ binding
* -DKPSR_BUILD_PATH location of the ```kpsr-build``` repository
* -DKPSR_WITH_DOXYGEN to allow generation of documentation

### ROS installation

Add the Klepsydra ROS sensors project to the ROS catkin workspace that contains the Klepsydra core (ROS) projects:

```
cd YOUR_ROS_PROJECT/src
ln -s $PATH_TO_KPSR_ROBOTIVCS/vision-ocv/modules/ros_mdlw/kpsr_ros_vision_ocv
source YOUR_ROS_PROJECT/install/setup.bash
catkin_make
```

# Documentation

## Documentation generation

```
make doc
```

### Location of documentation

The last built documentation is available in [Klepsydra Robotics API DOC](./api-doc/)


#  License

&copy; Copyright 2019-2020, Klepsydra Technologies, all rights reserved. Licensed under the terms in [LICENSE.md](./LICENSE.md)

This software and documentation are Copyright 2019-2020, Klepsydra Technologies
Limited and its licensees. All rights reserved. See [license file](./LICENSE.md) for full copyright notice and license terms.

#  Contact

https://www.klepsydra.com
support@klepsydra.com
