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

## Instructions
1. Use the `ACC` branch of speed-dreams [(ref.)](https://github.com/argos-research/speed-dreams/tree/ACC)
2. Configure a race to consist of two bots, with the ACC driver in the second position
3. Start a mosquitto server
4. Bring up all applications (`acc`, `mbl_adapter`, `mbl_client`, `servo_adapter`, `servo_client`) **except** for the `savm`
5. Start the `savm` application
6. Speed-dreams should continue loading and start the race
7. Watch the magic happen

## Flow Diagram
### General
![flow_diagram.png](https://github.com/irgendwie/genode-CarControl/raw/master/flow_diagram.png)

### Additional information
- SpeedDreams uses the `9002` port by default and acts as a server
