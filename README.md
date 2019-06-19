# Genode CarControl

## TODO
- the `mbl_client.cc` file is missing the control of the motor (your job @dk87)

## Repository structure
```
.
+-- include
|   +-- ...
+-- run
|   +-- stuff.run          /* sample run file containing all apps and configuration parameter
+-- src
|   +-- app
|   |   +-- acc            /* the acc unit (logic) */
|   |   |   +-- ...
|   |   +-- mbl_adapter    /* adapter app for the Roboteq MBL1650C Motor Controller (converting values from the simulation for the client */
|   |   |   +-- ...
|   |   +-- mbl_client     /* client app for the Roboteq MBL1650C Motor Controller (controlling the motor) */
|   |   |   +-- ...
|   |   +-- savm           /* the savm application (communication unit between the mqtt network and the simulation) */
|   |   |   +-- ...
|   |   +-- servo_adapter  /* adapter app for the servos (converting values from the simulation for the client) */
|   |   |   +-- ...
|   |   +-- servo_client   /* client app for the servos (controlling the servos) */
|   |   |   +-- ...
```

## Prerequisites
### Build Walkthrough

1. Follow the instructions in the [documentation](https://argos-research.github.io/documentation/install.html#operating-system-on-local-machine) (skip the last step ```make jenkins_run```)

2. Clone the genode-world under genode/repos (assuming you are in the operating-system directory)
```
git clone https://github.com/argos-research/genode-world.git genode/repos/genode-world
cd genode/repos/genode-world
git checkout protobuf_3.5.0
```
2.1 Clone the pololu Servo Controller
```
git clone https://github.com/argos-research/genode-pololuServoController.git genode/repos/genode-pololuServoController
```

3. Clone this repository into genode/repos (assuming you are in the operating-system directory)
```
git clone https://github.com/dk87/genode-CarControl.git genode/repos/genode-CarControl
```

4. Create a build directory for a rpi, pbxa9 and a panda build
```
GENODE_TARGET=focnados_rpi make jenkins_build_dir
GENODE_TARGET=focnados_panda make jenkins_build_dir
GENODE_TARGET=focnados_pbxa9 make jenkins_build_dir
```

5. Edit the ```etc/build.conf``` in each build directory by adding the following lines
```
REPOSITORIES += $(GENODE_DIR)/repos/genode-world
REPOSITORIES += $(GENODE_DIR)/repos/genode-CarControl
REPOSITORIES += $(GENODE_DIR)/repos/genode-pololuServoController
```

6. Prepare the missing ports by executing (again in operating-system directory)
```
./genode/tool/ports/prepare_port libmosquitto openssl libprotobuf
```

7. Trigger the compilation

```
make -C build/genode-focnados_rpi app/servo_client app/mbl_client
make -C build/genode-focnados_panda app/servo_adapter app/mbl_adapter
make -C build/genode-focnados_pbxa9 app/savm app/acc
```

## Run-time Instructions
1. Use the `ACC` branch of speed-dreams [(ref.)](https://github.com/argos-research/speed-dreams/tree/ACC)
2. Configure a race to consist of two bots, with the ACC driver in the second position
3. Start a mosquitto server
4. Bring up all applications (`acc`, `mbl_adapter`, `mbl_client`, `servo_adapter`, `servo_client`) **except** for the `savm`
5. Start the `savm` application
6. Speed-dreams should continue loading and start the race
7. Watch the magic happen

## Flow Diagram
### General
![flow_diagram.svg](https://github.com/privatereese/genode-CarControl/raw/master/flow_diagram.svg)

### Additional information
- SpeedDreams uses the `9002` port by default and acts as a server
