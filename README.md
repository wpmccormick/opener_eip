# ROS Ethernet/IP Device
[![support level: community](https://img.shields.io/badge/support%20level-community-lightgray.png)](http://rosindustrial.org/news/2016/10/7/better-supporting-a-growing-ros-industrial-software-platform)
## Overview
## Requirements
## Dependencies
## Installation
### ROS Installation
```
cd ~/catkin_ws/src
catkin init
git clone --recursive git@github.com:wpmccormick/eip_device.git
catkin build
ldconfig ../devel/lib/eip_device
```
### PLC (Logix5000) Installation
1. Copy eip_device/data
## Usage
### ROS Usage
#### Launch
#### Message Topics
##### Input Assembly Data
##### Output Assembly Data
##### Config Assembly Data
##### Explicit Assembly Data
### PLC Usage
#### Configuration Array
#### Input Array
#### Output Array
#### Explicit MSG Instruction
