# ROS manual

This manual is about the ros1 and ros2. this is still work in progress..

## message traits

1. used to convert between the C++ types with the ros types.
2. defines all template based structures to convert the md5sum, datatypes and structs

## installing and setting up ros1

**installing the ros:**

```shell
sudo apt install ros-kitentic-desktop-full
```

**environment check:**

```shell
devnaga@Hanzo:~$ printenv | grep ROS
ROS_ROOT=/opt/ros/kinetic/share/ros
ROS_PACKAGE_PATH=/opt/ros/kinetic/share
ROS_MASTER_URI=http://localhost:11311
ROS_VERSION=1
ROSLISP_PACKAGE_DIRECTORIES=
ROS_DISTRO=kinetic
ROS_ETC_DIR=/opt/ros/kinetic/etc/ros
```

### useful commands

```shell
rospack
```

**running roscore from ros1**

`roscore` needs to be run first before running anything else in ros1.

run `roscore` simply as..

```shell
roscore
```

and it starts up this way..

```shell
devnaga@Hanzo:~/catkin_ws$ roscore
... logging to /home/devnaga/.ros/log/41e56778-821e-11e8-8596-0800270fb40c/roslaunch-Hanzo-28253.log
Checking log directory for disk usage. This may take awhile.
Press Ctrl-C to interrupt
Done checking log file disk usage. Usage is <1GB.

started roslaunch server http://Hanzo:40341/
ros_comm version 1.12.13


SUMMARY
========

PARAMETERS
 * /rosdistro: kinetic
 * /rosversion: 1.12.13

NODES

auto-starting new master
process[master]: started with pid [28265]
ROS_MASTER_URI=http://Hanzo:11311/

setting /run_id to 41e56778-821e-11e8-8596-0800270fb40c
process[rosout-1]: started with pid [28278]
started core service [/rosout]
```

this starts up one master node called `/rosout`

**running rosbag also from ros1**

first you need to run the `roscore`..

1. run the rosbag for recording:

```shell
rosbag record imu_data
```

the `imu_data` is acutally a topic that the rosbag is subscribing on to..

### running rosbag for ros2 messages

1. setup `. /opt/ros/kinetic/setup.bash`
2. run `roscore`
3. run ros1_bridge

```shell
. /opt/ros/kinetic/setup.bash
. /ros2_ws/install/setup.bash
ros2 run ros1_bridge dynamic_bridge --bridge-all-topics
```

4. run ros1 talker `rosrun rospy_tutorials talker`
5. run rosbag `rosbag record chatter`

### replay of rosbag messages

```shell
roscore
ros2 run ros1_bridge dynamic_bridge --bridge-all-topics
rosbag play bag.bag
ros2 run demo_nodes_cpp listener
```

now you should be seeing the ros1 messages on the listener


### packages

| package | description |
|---------|-------------|
| `roscpp` | cpp library for ros1 |
| `rospy` | python librray for ros1 |

**roscpp help**

```shell
rospack find roscpp
```

# ROS2

## building and installing ros2 
## prerequisites

## build setps

**link to build:**

1. https://github.com/ros2/ros2/wiki/Ament-Tutorial

**bulding ros2:**

1. go inside the ros workspace: (you should not go inside src though ..)

```shell
src/ament/ament_tools/scripts/ament.py build --symlink-install
```

2. to build package wise

**building any package in ros2 - ament approach**

```shell
ament build --only-packages <package_name> --symlink-install
```

**building any package in ros2 - colcon approach**

```shell
 colcon build --symlink-install --packages-select <package_name> --cmake-force-configure
```

with colcon [here](https://github.com/ros2/ros2/wiki/Colcon-Tutorial)


1. while building the ros2 you would require an active internet connectivity.. it downloads so many other files and dependencies for compilation


## installing drivecore

1. installing .. there is no installing .. we just source the bin paths and lib paths into our working dir by doing this so that we can simply run the examples from here itself..


2. see for install directory and do the below

```shell
. install/local_setup.bash
```


## running after installing

1. help

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 -h
usage: ros2 [-h] Call `ros2 <command> -h` for more detailed usage. ...

ros2 is an extensible command-line tool for ROS 2.

optional arguments:
  -h, --help            show this help message and exit

Commands:
  daemon    Various daemon related sub-commands
  msg       Various msg related sub-commands
  node      Various node related sub-commands
  pkg       Various package related sub-commands
  run       Run a package specific executable
  security  Various security related sub-commands
  service   Various service related sub-commands
  srv       Various srv related sub-commands
  topic     Various topic related sub-commands

  Call `ros2 <command> -h` for more detailed usage.
devnaga@Hanzo:~/ros2_ws$ 
```

## topics to cover

1. Fast-RTPS
2. DDS
    1. static discovery
    2. logging
    3. SHM
3. DDS interfacing layer
4. rmw
5. rcl
    1. critical msg
    2. intra process
    3. Fast-RTPS control
    4. heartbeat monitoring
6. rclcpp
7. rmw - 3 interfaces 
8. SOME / IP should we cover ?
9. E2E and SecOC
10. shared memory IPC communication via PCIe or local communication
11. ros1_bridge

## Fast-RTPS

### building eprosima fastrtps

1. download the fastrtps code from here: https://github.com/eProsima/Fast-RTPS.git
2. install java, ant, gradle:

```shell
sudo apt install default-jdk
sudo apt install default-jre

## set java path: link here: https://www.digitalocean.com/community/tutorials/how-to-install-java-with-apt-get-on-ubuntu-16-04

sudo update-alternatives --config java

# edit /etc/environment

sudo vim /etc/environment

# add the below line in there

JAVA_HOME="/usr/lib/jvm/java-8-openjdk-amd64"

source /etc/enviornment

sudo apt install ant gradle
```

3. building fastrtps .. # steps here: https://github.com/eProsima/Fast-RTPS

```shell

git clone https://github.com/eProsima/Fast-RTPS
cd Fast-RTPS
mkdir build
cd build

cmake -DTHIRDPARTY=ON -DBUILD_JAVA=ON .. # bulding the fastrtpsgen: http://eprosima-fast-rtps.readthedocs.io/en/latest/geninfo.html
make
sudo make install
```

### Explanation of Fast RTPS

1. DDS is Data Distribution Service. DDS provides the communication layer abstration:
    1. automatic discovery:
        In DDS you just publish/subscribe to topic names. You never have to provide IP addresses, computer names, or ports. It is all handled by the builtin discovery. And it does it automatically without additional services. This means that applications can be re-deployed and integrated without recompilation or reconfiguration.

2. Requires IDL before communication:

    IDL: http://eprosima-fast-rtps.readthedocs.io/en/latest/genuse.html#idl-types

    |IDL data type example | C++-11 Data type |
    |----------------------|------------------|
    | `char`       | `char` |
    | `octet`      | `uint8_t` |
    | `short`      | `int16_t` |
    | `unsigned short` | `uint16_t` |
    | `long` | `long` or `int32_t` |
    | `long long` | `int64_t` |
    | `unsigned long long` | `uint64_t` |
    | `float` | `float` |
    | `double` | `double` |
    | `long double` | `long double` |
    | `boolean` | `bool` |
    | `string` | `std::string` |
    | `char a[5]` | `std::array<char, 5> a` |
    | `octet a[5]` | `std::array<uint8_t, 5> a` |
    | `struct` | `struct` |
    | `union` | `union` |
    | `sequence<char>` | `std::vector <char>` | 

3. interface structures: (as defined in the `fastrtpsgen` site here: http://docs.eprosima.com/en/v1.6.0/genuse.html)

    ```cpp
    struct Structure
    {
        octet octet_val;
        long long_val;
        string string_val;
    };
    ```

4. generating the source code via `fastrtpsgen`:

    define a message called `request_msg` in a `request_msg.idl` file like below:

    **FILE: request_msg.idl**

    ```cpp
    struct request_msg {
        string name;
        long sequence_no;
    };
    ```

    run the `fastrtpsgen` on the file as below..

    ```shell
    fastrtpsgen request_msg.idl
    ```

    it then generates a list of `.h` and `.cxx` files.

    to generate sample code for compiling and run use `-example x64Linux2.6gcc` option with `fastrtpsgen`


Links:

1. https://stackoverflow.com/questions/27768443/why-when-using-rather-dds-instead-of-zeromq

## RMW (ros middleware)

1. rmw has 3 interfaces -> connext, eProsima and opensplice
2. eProsima is preferred (code path: rmw_fastrtps/rmw_fastrtps_cpp)
3. a publish call from rclcpp():
```cpp
    rclcpp->publish(): (rclcpp/include/rclcpp/publisher.hpp)
        rcl_publish():
            rmw_publish(): (fastrtps client)
                fastrtps->publisher->write(): eProsima write
```

## RCLCPP

Each node in the drivecore runtime API (based on ROS) will have a set of publisher and subscribers.

1. Node is in `rclcpp::Node`.
2. Publisher is in `rclcpp::Publisher`.
3. Subscriber is in `rclcpp::Subscriber`.
4. Server is in `rclcpp::Service`.
5. Client is in `rclcpp::Client`.
6. Timer is in `rclcpp::TimerBase` and `rclcpp::WallTimer`.

5. Header files to include:

    1. `<rclcpp/rclcpp.h>`

2. classes 

|  API NAME | Description |
|-----------|-------------|
|rclcpp::Node | single point of entry for creating the node (A node will have a set of publisher and subscribers) |
|rclcpp::Publisher | publisher class |
|

1. rclcpp interfacing API (utility interface)

| API NAME | Description |
|----------|-------------|
| rclcpp::init | initialise the commnnication via the rmw interface and setup global signal handlers for SIGINT |
| rclcpp::ok | this function is a boolean return that say if there is a signal, return true otherwise false |
| rclcpp::shutdown | shutdown the rclcpp and notifies the signal handler and rmw |
| rclcpp::on_shutdown | this API allows to register a callback that gets called by the rclcpp::shutdown |
| rclcpp::sleep_for | sleep for some period of time .. unit is in nano seconds |
| rclcpp::spin | create a default single threaded executor and spin the specified node |


minimal API layout / call of the rclcpp:: utility interface looks below.

**Example:**

```cpp
class publisher : public rclcpp::Node {
  // publisher code here..
...
};

int main()
{
    rclcpp::init(argc, argv); //init the rmw interfaces communicaton

    // spin the node that's inherited from the rclcpp::Node
    rclcpp::spin(std::make_shared<rclcpp::Node>());
    rclcpp::shutdown();
}
```

## Rosbag file record and replay

Link here for ros2bag2 design [here](https://github.com/ros2/design/blob/f69fbbd11848e3dd6866b71a158a1902e31e92f1/articles/rosbags.md)

rosbag direct write: [here](https://github.com/osrf/rosbag_direct_write)

## diving into drivecore

## Nodes

1. node is the starting point for creating publishers and subscribers

```cpp
class Node: public std:enable_shared_from_this<Node>
```

2. any further publisher or subscriber can inherit this class and become child class.

## std_msgs

1. This one has the standard ros interface messages. the below types are possible

**string**

generally use

```cpp
std_msgs::msg::String::SharedPtr msg;

msg->data # contains the actual string value
```
## subscriber node

```cpp
rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
```

create a subscirber node on the same topic name and it require a callback.

create a callback with the same name

the `create_subscription` has some default values .. so allwe need to set is topic name and callback.

## pubsub

<type-name> is acutally one of the ros interface types.

### publisher

1. initialise with `rclcpp::init`
2. create node ->  `rclcpp::Node::make_shared("node_name");`
3. create topic -> `std::string("topic_name")`
4. create publsiher -> `node->create_publisher<type-name>(topic);`
5. copy the content into the data of type-name
6. keep publishing -> `publisher->publish(<msg_of_type-name>);`
7. use one of the spins -> `rclcpp::spin_some(node)`

### subscriber

1. initialise with `rclcpp::init`
2. create node ->   `rclcpp::Node::make_shared("node_name");`
3. create topic ->  `std::string("topic_name");` # one of publisher nodes
4. create subscriber -> `node->create_subscription<type-name>(topic, callback);`
   where `type-name` is generally the iunterface type that is being used in callback
5. spin the unit `rclcpp::spin(node);`
6. spining will wait for the caller.. the spinner will call the callback

callback
---------

callback type-name is same as that of the interface type being used.

```cpp
void callback(type-name data) {
}
```

the data is then can be processed the way the subscriber want

## rosidl

1. interface definition language for the ros2 and this message gets serialised when publishing and deserialised when received at subscriber


below are the supported types in rosidl

| type | description |
|------|-------------|
|`bool` | boolean type can have two values `true` or `false` |
|`byte` | unsigned integer value with range from 0 to 255 |
|`char` | character with range -128 to 127 |
|`float32` | 32 bit floating point number |
|`float64` | 64 bit floating point number |
|`int8` | 8 bit integer |
|`int16` | 16 bit integer |


### rosidl messaging rules

1. there shouldn't be any upper case letters
2. constant names must be in upper case with `_` for separation of words

### rosidl service definition

more about rosidl is [here](http://design.ros2.org/articles/interface_definition.html)

## ros1_bridge

`ros1_bridge` translates the information from ros1 to ros2.

### building ros1_bridge from the source

**bridge ros1 and ros2**

cloning: `git clone https://github.com/ros2/ros1_bridge/blob/master/README.md`

```shell
 colcon build --symlink-install --packages-select ros1_bridge --cmake-force-configure
```

1. first ros1 to be installed.
2. run the setup `. /opt/ros/kinetic/setup.bash` to setup the ros1
3. compile the ros1_bridge (basically ros1 to be there to compile this)

```shell
ros2 run ros1_bridge dynamic_bridge --bridge-all-topics
```

4. run the example talker in the ros1

```shell
rosrun rospy_tutorials talker
```

5. run the listener node on ros2

```shell
ros2 run demo_nodes_cpp listener
```

now you should be seeing some messages fromr ros1 on the listener


## Rosbag

1. a logger lib and there is a player and recorder
2. stores content from all the topic by subscribing to all topics (querying the master regularly for new topics or may be only node or a topic list)
3. the recorder, records the messages in rosbag format .. right now its v2.
4. compression, encryption are some of the features..
    1. compression may involve bzip or lz4 techniques.
    2. encryption may involve AES cbc modes
5. recording happens in chunks or into the RAM when in snapshot mode (and then flushed to the disk once node is completed)
6. rosbag is implemented in two packages .. one is rosbag_storage (storage handling and logging) another is rosbag (this contain the recorder and player)
7. there is no `rosbag` in ros2 but the ros1's rosbag can be run and the messages can be bridged via `ros1_bridge`

**must haves**

1. rosbag filtering and rate to reduce the storage size and maintanence

## running ros1_bridge and recoding with `rosbag`

**NOTE: Need to have first ros1 installed on the system**

1. setup `. /opt/ros/kinetic/setup.bash`
2. run `roscore`
3. run ros1_bridge

```shell
. /opt/ros/kinetic/setup.bash
. /ros2_ws/install/setup.bash
ros2 run ros1_bridge dynamic_bridge --bridge-all-topics
```

4. run ros1 talker `rosrun rospy_tutorials talker`
5. run rosbag `rosbag record chatter`

## replaying the rosbag

1. follow the above steps till 3
2. run the ros2 subscriber `ros2 run demo_nodes_cpp listener`
3. run the rosbag player as 

```shell
rosbag play bag.bag  # bag.bag is the bag file
```

now the listener should be seeing the messages

## rosbag_storage

1. have file class that has methods to do compress, encrypt
    1. compress has the nocompress, bzip or lz4
    2. each record has an md5sum to verify its a proper record
    3. each record can be encrypted in AES Cbc mode
    4. at the end of the day its all fwrite and fread on the files


## rosbag file format

**Pseudo code on rosbag file format .. only for learning purposes**

```c
typedef enum {
    ROSBAG_OP_BAG_MESSAGE_DATA = 0x02,
    ROSBAG_OP_BAG_HEADER = 0x03,
    ROSBAG_OP_BAG_INDEX = 0x04,
    ROSBAG_OP_BAG_CHUNK = 0x05,
    ROSBAG_OP_BAG_CONNECTION = 0x07,
} rosbag_opcodes_t;

struct rosbag_name_val_pair {
    int field_length;
    char *field_name;
    uint8_t *field_value;
    struct rosbag_name_val_pair *next;
};

struct rosbag_header {
    struct rosbag_name_val_pair *name_val_pair;
};

struct rosbag_bagheader {
    int index_pos;
    int conn_count;
    int chunk_count;
};

struct rosbag_chunk {
    int compression;
    int size;
};

struct rosbag_connid {
    char *topic;
    int type;
    uint8_t md5sum[8];
    int message_definition;
    int callerid; // optional
    int latching; // optional
};

struct rosbag_connection {
    struct rosbag_connid conn_id;
    char *topic;
};

struct rosbag_time {
    uint32_t tv_sec;
    uint32_t tv_nsec;
};

struct rosbag_message_data {
    int connid;
    struct rosbag_time time;
    uint8_t *serialised_data;
};

struct rosbag_index_data_chunk_list {
    struct rosbag_time timestamp;
    loff_t offset;
    struct rosbag_index_data_chunk_list *next;
};

struct rosbag_index_data {
    int version;
    int conn;
    int count;
    struct rosbag_index_data_chunk_list *chunk_list;
};

struct rosbag_chunk_info {
    int version;
    loff_t chunk_pos;
    struct rosbag_time start_time;
    struct rosbag_time end_time;
    int count;
};

struct rosbag_record {
    int                     header_len;
    struct rosbag_header    header;
    int                     rec_data_len;

    // data portions of the rosbag
    rosbag_opcodes_t        opcode;

    // one or more of the below elements are valid based on the opcode
    struct rosbag_bagheader bag_header;
    struct rosbag_chunk chunk_header;
    struct rosbag_connection connection_header;
    struct rosbag_message_data *rec_data;
    struct rosbag_record    *next;
};

struct rosbag {
    char *version;
    struct rosbag_record *record_list;
};
```

## rosbuild/srv - message communication for ros


1. link [here](http://wiki.ros.org/srv)

# command line examples

2. help / command line example:

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 srv -h
usage: ros2 srv [-h] Call `ros2 srv <command> -h` for more detailed usage. ...

Various srv related sub-commands

optional arguments:
  -h, --help            show this help message and exit

Commands:
  list      Output a list of available service types
  package   Output a list of available service types within one package
  packages  Output a list of packages which contain services
  show      Output the service definition

  Call `ros2 srv <command> -h` for more detailed usage.
```

3. list of services implemented:

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 srv list 
composition/LoadNode
diagnostic_msgs/AddDiagnostics
diagnostic_msgs/SelfTest
example_interfaces/AddTwoInts
lifecycle_msgs/ChangeState
lifecycle_msgs/GetAvailableStates
lifecycle_msgs/GetAvailableTransitions
lifecycle_msgs/GetState
logging_demo/ConfigLogger
nav_msgs/GetMap
nav_msgs/GetPlan
nav_msgs/SetMap
rcl_interfaces/DescribeParameters
rcl_interfaces/GetParameterTypes
rcl_interfaces/GetParameters
rcl_interfaces/ListParameters
rcl_interfaces/SetParameters
rcl_interfaces/SetParametersAtomically
sensor_msgs/SetCameraInfo
std_srvs/Empty
std_srvs/SetBool
std_srvs/Trigger
test_msgs/Empty
test_msgs/Primitives
tf2_msgs/FrameGraph
```

4. list of packages that contain the services:

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 srv packages
composition
diagnostic_msgs
example_interfaces
lifecycle_msgs
logging_demo
nav_msgs
rcl_interfaces
sensor_msgs
std_srvs
test_msgs
tf2_msgs
```

5. list available services with in the package

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 srv package composition
composition/LoadNode
```

6. show the service definition (interface)

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 srv show nav_msgs/GetMap
# Get the map as a nav_msgs/OccupancyGrid
---
OccupancyGrid map
```

## ros2topic (command is ros2 topic)

1. help / command line examples:

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 topic -h
usage: ros2 topic [-h] [--include-hidden-topics]
                  Call `ros2 topic <command> -h` for more detailed usage. ...

Various topic related sub-commands

optional arguments:
  -h, --help            show this help message and exit
  --include-hidden-topics
                        Consider hidden topics as well

Commands:
  echo  Output messages from a topic
  list  Output a list of available topics
  pub   Publish a message to a topic

  Call `ros2 topic <command> -h` for more detailed usage.
```

2. list all topics

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 topic list
```

3. demo of topic:

    1. let's run an example

    ```shell
    devnaga@Hanzo:~/ros2_ws$ ros2 run demo_nodes_cpp talker
    ```

    2. list the topics

    ```shell
    devnaga@Hanzo:~/ros2_ws$ ros2 topic list
    /chatter
    /clock
    /parameter_events
    ```

    3. echo the output from the topic `/chatter`.

    ```shell
    devnaga@Hanzo:~/ros2_ws$ ros2 topic echo /chatter
    data: 'Hello World: 46'

    data: 'Hello World: 47'

    data: 'Hello World: 48'
    ```

    4. lets run the listener

    ```shell
    devnaga@Hanzo:~/ros2_ws$ ros2 run demo_nodes_cpp listener 
    ```

    5. lets run the list of topics again

    ```shell
    devnaga@Hanzo:~/ros2_ws$ ros2 topic list
    /chatter
    /clock
    /parameter_events
    ```

    6. lets publish a message on that topic

    using `pub` with the `ros2 topic`:

    ```shell
    devnaga@Hanzo:~/ros2_ws$ ros2 topic pub -h
    usage: ros2 topic pub [-h] [-r N] [-1] topic_name message_type [values]

    Publish a message to a topic

    positional arguments:
      topic_name      Name of the ROS topic to publish to (e.g. '/chatter')
      message_type    Type of the ROS message (e.g. 'std_msgs/String')
      values          Values to fill the message with in YAML format (e.g. "data:
                      Hello World"), otherwise the message will be published with
                      default values

    optional arguments:
      -h, --help      show this help message and exit
      -r N, --rate N  Publishing rate in Hz (default: 1)
      -1, --once      Publish one message and exit
    ```

    ```shell
    devnaga@Hanzo:~/ros2_ws$ ros2 topic pub /chatter std_msgs/String "data: Hello Dev"
    ```

    let's check on the listener now:

    ```shell
    devnaga@Hanzo:~/ros2_ws$ ros2 run demo_nodes_cpp listener
    [INFO] [listener]: I heard: [Hello Dev]
    [INFO] [listener]: I heard: [Hello Dev]
    [INFO] [listener]: I heard: [Hello Dev]
    [INFO] [listener]: I heard: [Hello Dev]
    [INFO] [listener]: I heard: [Hello Dev]
    ```

## ros2msg (command ros2 msg)

1. help

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 msg -h
usage: ros2 msg [-h] Call `ros2 msg <command> -h` for more detailed usage. ...

Various msg related sub-commands

optional arguments:
  -h, --help            show this help message and exit

Commands:
  list      Output a list of available message types
  package   Output a list of available message types within one package
  packages  Output a list of packages which contain messages
  show      Output the message definition

  Call `ros2 msg <command> -h` for more detailed usage.
```

2. list of supported messages:

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 msg list
actionlib_msgs/GoalID
actionlib_msgs/GoalStatus
actionlib_msgs/GoalStatusArray
builtin_interfaces/Duration
builtin_interfaces/Time
diagnostic_msgs/DiagnosticArray
diagnostic_msgs/DiagnosticStatus
diagnostic_msgs/KeyValue
geometry_msgs/Accel
geometry_msgs/AccelStamped
geometry_msgs/AccelWithCovariance
geometry_msgs/AccelWithCovarianceStamped
geometry_msgs/Inertia
geometry_msgs/InertiaStamped
geometry_msgs/Point
geometry_msgs/Point32
geometry_msgs/PointStamped
geometry_msgs/Polygon
geometry_msgs/PolygonStamped
geometry_msgs/Pose
geometry_msgs/Pose2D
geometry_msgs/PoseArray
geometry_msgs/PoseStamped
geometry_msgs/PoseWithCovariance
geometry_msgs/PoseWithCovarianceStamped
geometry_msgs/Quaternion
geometry_msgs/QuaternionStamped
geometry_msgs/Transform
geometry_msgs/TransformStamped
geometry_msgs/Twist
geometry_msgs/TwistStamped
geometry_msgs/TwistWithCovariance
geometry_msgs/TwistWithCovarianceStamped
geometry_msgs/Vector3
geometry_msgs/Vector3Stamped
geometry_msgs/Wrench
geometry_msgs/WrenchStamped
lifecycle_msgs/State
lifecycle_msgs/Transition
lifecycle_msgs/TransitionDescription
lifecycle_msgs/TransitionEvent
nav_msgs/GridCells
nav_msgs/MapMetaData
nav_msgs/OccupancyGrid
nav_msgs/Odometry
nav_msgs/Path
pendulum_msgs/JointCommand
pendulum_msgs/JointState
pendulum_msgs/RttestResults
rcl_interfaces/IntraProcessMessage
rcl_interfaces/ListParametersResult
rcl_interfaces/Parameter
rcl_interfaces/ParameterDescriptor
rcl_interfaces/ParameterEvent
rcl_interfaces/ParameterEventDescriptors
rcl_interfaces/ParameterType
rcl_interfaces/ParameterValue
rcl_interfaces/SetParametersResult
sensor_msgs/BatteryState
sensor_msgs/CameraInfo
sensor_msgs/ChannelFloat32
sensor_msgs/CompressedImage
sensor_msgs/FluidPressure
sensor_msgs/Illuminance
sensor_msgs/Image
sensor_msgs/Imu
sensor_msgs/JointState
sensor_msgs/Joy
sensor_msgs/JoyFeedback
sensor_msgs/JoyFeedbackArray
sensor_msgs/LaserEcho
sensor_msgs/LaserScan
sensor_msgs/MagneticField
sensor_msgs/MultiDOFJointState
sensor_msgs/MultiEchoLaserScan
sensor_msgs/NavSatFix
sensor_msgs/NavSatStatus
sensor_msgs/PointCloud
sensor_msgs/PointCloud2
sensor_msgs/PointField
sensor_msgs/Range
sensor_msgs/RegionOfInterest
sensor_msgs/RelativeHumidity
sensor_msgs/Temperature
sensor_msgs/TimeReference
shape_msgs/Mesh
shape_msgs/MeshTriangle
shape_msgs/Plane
shape_msgs/SolidPrimitive
std_msgs/Bool
std_msgs/Byte
std_msgs/ByteMultiArray
std_msgs/Char
std_msgs/ColorRGBA
std_msgs/Empty
std_msgs/Float32
std_msgs/Float32MultiArray
std_msgs/Float64
std_msgs/Float64MultiArray
std_msgs/Header
std_msgs/Int16
std_msgs/Int16MultiArray
std_msgs/Int32
std_msgs/Int32MultiArray
std_msgs/Int64
std_msgs/Int64MultiArray
std_msgs/Int8
std_msgs/Int8MultiArray
std_msgs/MultiArrayDimension
std_msgs/MultiArrayLayout
std_msgs/String
std_msgs/UInt16
std_msgs/UInt16MultiArray
std_msgs/UInt32
std_msgs/UInt32MultiArray
std_msgs/UInt64
std_msgs/UInt64MultiArray
std_msgs/UInt8
std_msgs/UInt8MultiArray
stereo_msgs/DisparityImage
test_msgs/BoundedArrayNested
test_msgs/BoundedArrayPrimitives
test_msgs/Builtins
test_msgs/DynamicArrayNested
test_msgs/DynamicArrayPrimitives
test_msgs/DynamicArrayPrimitivesNested
test_msgs/Empty
test_msgs/Nested
test_msgs/Primitives
test_msgs/StaticArrayNested
test_msgs/StaticArrayPrimitives
tf2_msgs/TF2Error
tf2_msgs/TFMessage
trajectory_msgs/JointTrajectory
trajectory_msgs/JointTrajectoryPoint
trajectory_msgs/MultiDOFJointTrajectory
trajectory_msgs/MultiDOFJointTrajectoryPoint
visualization_msgs/ImageMarker
visualization_msgs/InteractiveMarker
visualization_msgs/InteractiveMarkerControl
visualization_msgs/InteractiveMarkerFeedback
visualization_msgs/InteractiveMarkerInit
visualization_msgs/InteractiveMarkerPose
visualization_msgs/InteractiveMarkerUpdate
visualization_msgs/Marker
visualization_msgs/MarkerArray
visualization_msgs/MenuEntry
```

3. list of supported packages

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 msg packages
actionlib_msgs
builtin_interfaces
diagnostic_msgs
geometry_msgs
lifecycle_msgs
nav_msgs
pendulum_msgs
rcl_interfaces
sensor_msgs
shape_msgs
std_msgs
stereo_msgs
test_msgs
tf2_msgs
trajectory_msgs
visualization_msgs
```

4. list of supported message with in one package

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 msg package sensor_msgs
sensor_msgs/BatteryState
sensor_msgs/CameraInfo
sensor_msgs/ChannelFloat32
sensor_msgs/CompressedImage
sensor_msgs/FluidPressure
sensor_msgs/Illuminance
sensor_msgs/Image
sensor_msgs/Imu
sensor_msgs/JointState
sensor_msgs/Joy
sensor_msgs/JoyFeedback
sensor_msgs/JoyFeedbackArray
sensor_msgs/LaserEcho
sensor_msgs/LaserScan
sensor_msgs/MagneticField
sensor_msgs/MultiDOFJointState
sensor_msgs/MultiEchoLaserScan
sensor_msgs/NavSatFix
sensor_msgs/NavSatStatus
sensor_msgs/PointCloud
sensor_msgs/PointCloud2
sensor_msgs/PointField
sensor_msgs/Range
sensor_msgs/RegionOfInterest
sensor_msgs/RelativeHumidity
sensor_msgs/Temperature
sensor_msgs/TimeReference
```

5. display the messge format

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 msg show sensor_msgs/Image
# This message contains an uncompressed image
# (0, 0) is at top-left corner of image

std_msgs/Header header # Header timestamp should be acquisition time of image
                             # Header frame_id should be optical frame of camera
                             # origin of frame should be optical center of cameara
                             # +x should point to the right in the image
                             # +y should point down in the image
                             # +z should point into to plane of the image
                             # If the frame_id here and the frame_id of the CameraInfo
                             # message associated with the image conflict
                             # the behavior is undefined

uint32 height                # image height, that is, number of rows
uint32 width                 # image width, that is, number of columns

# The legal values for encoding are in file src/image_encodings.cpp
# If you want to standardize a new string format, join
# ros-users@lists.ros.org and send an email proposing a new encoding.

string encoding       # Encoding of pixels -- channel meaning, ordering, size
                      # taken from the list of strings in include/sensor_msgs/image_encodings.h

uint8 is_bigendian    # is this data bigendian?
uint32 step           # Full row length in bytes
uint8[] data          # actual matrix data, size is (step * rows)
```

## ros2 node

1. help

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 node -h
usage: ros2 node [-h]
                 Call `ros2 node <command> -h` for more detailed usage. ...

Various node related sub-commands

optional arguments:
  -h, --help            show this help message and exit

Commands:
  list  Output a list of available nodes

  Call `ros2 node <command> -h` for more detailed usage.
```

2. list avilble nodes

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 node list 
```

### demo (visualising the nodes)

1. lets run the talker and listener

```shell
ros2 run demo_nodes_cpp talker
ros2 run demo_nodes_cpp listener
```

2. lets run the list of nodes

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 node list 
listener
talker
```

## ros2 pkg

1. help

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 pkg -h
usage: ros2 pkg [-h] Call `ros2 pkg <command> -h` for more detailed usage. ...

Various package related sub-commands

optional arguments:
  -h, --help            show this help message and exit

Commands:
  executables  Output a list of package specific executables
  list         Output a list of available packages
  prefix       Output the prefix path of a package

  Call `ros2 pkg <command> -h` for more detailed usage.
```

2. output a list of executables:

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 pkg executables
composition api_composition
composition api_composition_cli
composition dlopen_composition
composition linktime_composition
composition manual_composition
demo_nodes_cpp add_two_ints_client
demo_nodes_cpp add_two_ints_client_async
demo_nodes_cpp add_two_ints_server
demo_nodes_cpp allocator_tutorial
demo_nodes_cpp imu_listener
demo_nodes_cpp list_parameters
demo_nodes_cpp list_parameters_async
demo_nodes_cpp listener
demo_nodes_cpp listener_best_effort
demo_nodes_cpp one_off_timer
demo_nodes_cpp parameter_events
demo_nodes_cpp parameter_events_async
demo_nodes_cpp parameter_node
demo_nodes_cpp reuse_timer
demo_nodes_cpp ros2param
demo_nodes_cpp set_and_get_parameters
demo_nodes_cpp set_and_get_parameters_async
demo_nodes_cpp talker
demo_nodes_cpp_native talker
demo_nodes_py add_two_ints_client
demo_nodes_py add_two_ints_client_async
demo_nodes_py add_two_ints_server
demo_nodes_py listener
demo_nodes_py listener_qos
demo_nodes_py talker
demo_nodes_py talker_qos
dummy_map_server dummy_map_server
dummy_sensors dummy_joint_states
dummy_sensors dummy_laser
examples_rclcpp_minimal_client client_main
examples_rclcpp_minimal_composition composition_composed
examples_rclcpp_minimal_composition composition_publisher
examples_rclcpp_minimal_composition composition_subscriber
examples_rclcpp_minimal_publisher publisher_lambda
examples_rclcpp_minimal_publisher publisher_member_function
examples_rclcpp_minimal_publisher publisher_not_composable
examples_rclcpp_minimal_service service_main
examples_rclcpp_minimal_subscriber subscriber_lambda
examples_rclcpp_minimal_subscriber subscriber_member_function
examples_rclcpp_minimal_subscriber subscriber_not_composable
examples_rclcpp_minimal_timer timer_lambda
examples_rclcpp_minimal_timer timer_member_function
examples_rclpy_executors callback_group
examples_rclpy_executors composed
examples_rclpy_executors custom_callback_group
examples_rclpy_executors custom_executor
examples_rclpy_executors listener
examples_rclpy_executors talker
examples_rclpy_minimal_client client
examples_rclpy_minimal_client client_async
examples_rclpy_minimal_client client_async_member_function
examples_rclpy_minimal_publisher publisher_local_function
examples_rclpy_minimal_publisher publisher_member_function
examples_rclpy_minimal_publisher publisher_old_school
examples_rclpy_minimal_service service
examples_rclpy_minimal_service service_member_function
examples_rclpy_minimal_subscriber subscriber_lambda
examples_rclpy_minimal_subscriber subscriber_member_function
examples_rclpy_minimal_subscriber subscriber_old_school
image_tools cam2image
image_tools showimage
intra_process_demo camera_node
intra_process_demo cyclic_pipeline
intra_process_demo image_pipeline_all_in_one
intra_process_demo image_pipeline_with_two_image_view
intra_process_demo image_view_node
intra_process_demo two_node_pipeline
intra_process_demo watermark_node
lifecycle lifecycle_listener
lifecycle lifecycle_service_client
lifecycle lifecycle_service_client_py.py
lifecycle lifecycle_talker
logging_demo logging_demo_main
robot_state_publisher robot_state_publisher
rosidl_generator_c rosidl_generator_c
rosidl_generator_cpp rosidl_generator_cpp
rosidl_generator_dds_idl rosidl_generator_dds_idl
rosidl_generator_py rosidl_generator_py
rosidl_typesupport_introspection_c rosidl_typesupport_introspection_c
rosidl_typesupport_introspection_cpp rosidl_typesupport_introspection_cpp
rviz2 rviz2
tf2_ros static_transform_publisher
tf2_ros tf2_echo
tf2_ros tf2_monitor
topic_monitor data_publisher
topic_monitor launch_depth_demo
topic_monitor launch_fragmentation_demo
topic_monitor launch_reliability_demo
topic_monitor topic_monitor
```

3. list available packages

```shell
devnaga@Hanzo:~/ros2_ws$ ros2 pkg list
actionlib_msgs
ament_clang_format
ament_cmake
ament_cmake_auto
ament_cmake_clang_format
ament_cmake_copyright
ament_cmake_core
ament_cmake_cppcheck
ament_cmake_cpplint
ament_cmake_export_definitions
ament_cmake_export_dependencies
ament_cmake_export_include_directories
ament_cmake_export_interfaces
ament_cmake_export_libraries
ament_cmake_export_link_flags
ament_cmake_flake8
ament_cmake_gmock
ament_cmake_gtest
ament_cmake_include_directories
ament_cmake_libraries
ament_cmake_lint_cmake
ament_cmake_nose
ament_cmake_pep257
ament_cmake_pep8
ament_cmake_pyflakes
ament_cmake_pytest
ament_cmake_python
ament_cmake_ros
ament_cmake_target_dependencies
ament_cmake_test
ament_cmake_uncrustify
ament_copyright
ament_cppcheck
ament_cpplint
ament_flake8
ament_index_cpp
ament_index_python
ament_lint_auto
ament_lint_cmake
ament_lint_common
ament_package
ament_pep257
ament_pep8
ament_pyflakes
ament_tools
ament_uncrustify
builtin_interfaces
class_loader
common_interfaces
composition
connext_cmake_module
demo_nodes_cpp
demo_nodes_cpp_native
demo_nodes_py
diagnostic_msgs
dummy_map_server
dummy_robot_bringup
dummy_sensors
example_interfaces
examples_rclcpp_minimal_client
examples_rclcpp_minimal_composition
examples_rclcpp_minimal_publisher
examples_rclcpp_minimal_service
examples_rclcpp_minimal_subscriber
examples_rclcpp_minimal_timer
examples_rclpy_executors
examples_rclpy_minimal_client
examples_rclpy_minimal_publisher
examples_rclpy_minimal_service
examples_rclpy_minimal_subscriber
fastrtps_cmake_module
geometry_msgs
image_tools
intra_process_demo
kdl_parser
launch
launch_testing
libcurl_vendor
lifecycle
lifecycle_msgs
logging_demo
nav_msgs
opensplice_cmake_module
osrf_pycommon
pendulum_control
pendulum_msgs
pluginlib
python_cmake_module
rcl
rcl_interfaces
rcl_lifecycle
rclcpp
rclcpp_lifecycle
rclpy
rcutils
resource_retriever
rmw
rmw_connext_cpp
rmw_connext_shared_cpp
rmw_fastrtps_cpp
rmw_implementation
rmw_implementation_cmake
rmw_opensplice_cpp
robot_state_publisher
ros1_bridge
ros2cli
ros2msg
ros2node
ros2pkg
ros2run
ros2service
ros2srv
ros2topic
ros_environment
rosidl_cmake
rosidl_default_generators
rosidl_default_runtime
rosidl_generator_c
rosidl_generator_cpp
rosidl_generator_dds_idl
rosidl_generator_py
rosidl_parser
rosidl_typesupport_c
rosidl_typesupport_connext_c
rosidl_typesupport_connext_cpp
rosidl_typesupport_cpp
rosidl_typesupport_interface
rosidl_typesupport_introspection_c
rosidl_typesupport_introspection_cpp
rosidl_typesupport_opensplice_c
rosidl_typesupport_opensplice_cpp
rttest
rviz2
rviz_assimp_vendor
rviz_common
rviz_default_plugins
rviz_ogre_vendor
rviz_rendering
rviz_rendering_tests
rviz_yaml_cpp_vendor
sensor_msgs
shape_msgs
sros2
std_msgs
std_srvs
stereo_msgs
test_communication
test_msgs
test_rclcpp
test_security
tf2
tf2_eigen
tf2_geometry_msgs
tf2_msgs
tf2_ros
tlsf
tlsf_cpp
topic_monitor
trajectory_msgs
uncrustify
urdf
visualization_msgs
```


