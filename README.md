<p align="right">
  <img width="25%" height="25%"src="./images/klepsydra_logo.jpg">
</p>

[![Build](https://github.com/klepsydra-technologies/kpsr-robotics/actions/workflows/push.yml/badge.svg)](https://github.com/klepsydra-technologies/kpsr-robotics/actions/workflows/push.yml) [![codecov](https://codecov.io/gh/klepsydra-technologies/kpsr-robotics/branch/main/graph/badge.svg?token=PDALQNPJRD)](https://codecov.io/gh/klepsydra-technologies/kpsr-robotics)

- [Installation instructions](#installation-instructions)
    - [System dependencies](#system-dependencies)
    - [Klepsydra dependencies](#klepsydra-dependencies)
    - [System installation](#system-installation)
    - [Installation](#installation)
        - [ROS installation](#ros-installation)
- [Documentation](#documentation)
    - [Location of documentation](#location-of-documentation)
    - [Documentation generation](#documentation-generation)
- [License](#license)
- [Contact](#contact)

# Installation instructions

## System dependencies

- Ubuntu 18.04 or above
- ConcurrentQueue (<https://github.com/klepsydra-technologies/concurrentqueue>)
- Cereal (<https://github.com/klepsydra-technologies/cereal>)
- ZMQ 3 or above (optional)
- CMake 3.12 or above
- gcc for C++11 5.4.0 or above
- Doxygen (optional)
- Moxygen (<https://github.com/sourcey/moxygen>) (optional)
- OpenCV 3.4.x or above (optional)

## Klepsydra dependencies

- kpsr-core

## System installation

```bash
sudo apt install build-essential git cmake
```

## Installation

Given `$KLEPSYDRA_HOME`, for example `$HOME/klepsydra`:

```bash
git clone https://github.com/klepsydra-technologies/kpsr-robotics.git
cd kpsr-robotics/
git submodule update --init
mkdir build && cd build/
cmake .. -DKPSR_WITH_OCV=true -DKPSR_WITH_ZMQ=true
make -j$(nproc)
make -j$(nproc) test
sudo make install
```

The cmake has the following options:

- `-DCMAKE_INSTALL_PREFIX=<path>` for specifying the Klepsydra robotics installation location (`/opt/klepsydra` by default)
- `-DCMAKE_PREFIX_PATH=<path>` Klepsydra SDK installation location (`/usr/local` by default), same as `-DCMAKE_INSTALL_PREFIX` when building kpsr-core
- `-DKPSR_WITH_OCV=true` for building the OpenCV module (default false)
- `-DKPSR_WITH_ZMQ=true` for building the ZMQ binding (default false)
- `-DKPSR_WITH_DOXYGEN=true` to allow generation of documentation
- `-DKPSR_ENABLE_TESTS=false` (default true)

# Documentation

## Location of documentation

The last built documentation is available in [Klepsydra Robotics API DOC](./api-doc/)

## Documentation generation

```bash
make doc
```

# License

&copy; 2023 Klepsydra Technologies AG, all rights reserved. Licensed under the terms in [LICENSE.md](./LICENSE.md)

This software and documentation are 2023 Klepsydra Technologies AG
Limited and its licensees. All rights reserved. See [license file](./LICENSE.md) for full copyright notice and license terms.

# Contact

<https://www.klepsydra.com>
support@klepsydra.com
