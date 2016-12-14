# Alljoyn

All alljoyn-related source code.

## 1. ControlPanelSample.

### 1.1 Build

Before building this ControlPanel sample, you need to build the alljoyn core and two base services: control panel and notification.

(1) Windows: 

Open the solution file ControlPanelSample.sln in Visual Studio 2012 and later, and then build the two projects ControlPanelControllee and ControlPanelController.

Or use scons to build the code.

```
$ scons OS=win7 CPU=x86_64 MSVC_VERSION=11.0 WS=off VARIANT=debug AJ_VER=1504
$ scons OS=win7 CPU=x86_64 MSVC_VERSION=11.0 WS=off VARIANT=release AJ_VER=1504
```

Note that since the AllJoyn core version is 15.04, we need to define the environment variable "ALLJOYN_SRC_1504_HOME" as the path of the AllJoyn core source code before running the scons command.

(2) Linux (e.g., Ubuntu):

First set up the alljoyn version and path.

```bash
$ cd ControlPanelSample
$ source environment-setup-linux
```

Then use scons to build the code.

```bash
$ scons OS=linux CPU=x86_64 VARIANT=debug
$ scons OS=linux CPU=x86_64 VARIANT=release
```

### 1.2 Run the controllee and controller.

The two executables ControlPanelControllee(.exe) and ControlPanelController(.exe) will be generated in ControlPanelSample/build/${OS}/${CPU}/${VARIANT}/dist/cpp/bin. Note that by default Linux won't search the current directory for the shared libraries which will be loaded by the two executables, on Linux, we need to define the environment variable "LD_LIBRARY_PATH" as the current directory "." before running the two executables.

```bash
$ export LD_LIBRARY_PATH=.
```

## 2. CommonDeviceModel.

### 2.1 Build

Before building the Common Device Model (CDM) sample code, you need to build the alljoyn CDM service framework. Note that since the alljoyn CDM service framework depends on the alljoyn core, the alljoyn core will be built first when the alljoyn CDM service framework is built. The CDM build is supported only on Linux (e.g., Ubuntu):

```bash
$ cd CommonDeviceModel
$ source environment-setup-linux
```

Then use scons to build the code.

```bash
$ scons OS=linux CPU=x86_64 VARIANT=debug
$ scons OS=linux CPU=x86_64 VARIANT=release
```

### 2.2 Run the controllee and controller.

The two executables BingoControllee and BingoController will be generated in CommonDeviceModel/build/${OS}/${CPU}/${VARIANT}/dist/cpp/bin. Note that by default Linux won't search the current directory for the shared libraries which will be loaded by the two executables, on Linux, we need to define the environment variable "LD_LIBRARY_PATH" as the current directory "." before running the two executables.

```bash
$ export LD_LIBRARY_PATH=.
```