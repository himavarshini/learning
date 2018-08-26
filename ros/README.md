# ROS

ROS is a robot operating system -middleware.

## intro

### install ros

### how to run ros - commands

1. running `roscore` base service

```bash
. /opt/ros/kinetic/setup.bash

roscore
```

creates a master ros server

1. to proxy information between the nodes
2. to provide information about each node

without master server, the ros communication between the nodes is not possible.



2. running `rosnode`

```bash
rosnode list
rosnode list rosout
rosrun turtlesim turtlesim_node
```

3. running `rqt`

```bash
rosrun rqt_graph rqt_graph
```

runs the rqt graph to display about the list of nodes and the topics available.

4. rostopic

```bash
rostopic echo /rosout
```
