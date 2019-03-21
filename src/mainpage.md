# Iteration 3 Braitenberg Vehicle Simulator

Yuanzhe Liu

### Table of Contents

[**Non-Technical User Guide**](#non-technical-user-guide)

[Introduction](#introduction)

[How to use this simulation](#how-to-use-this-simulation)

[**Developer Guide**](#developer-guide)

[Observer Pattern](#observer-pattern)

[Strategy Pattern](#strategy-pattern)

[Add New Stimuli](#add-new-stimuli)

[Add New Sensor](#add-new-sensor)


## Non-Technical User Guide

### Introduction

This program is a Braitenberg Vehicle simulator. Braitenberg vehicles use simple input to achieve complex behavior. There are four types of Braitenberg vehicles: Fear, Aggressive, Love, Explore.

+ “Fear” has positive, direct sensor-motor connections, meaning the reading from the right sensor positively (i.e. the stronger the signal, the faster the wheel moves) impacts the velocity of the right wheel, and the left sensor positively impacts the left wheel.
+ “Aggressive” has positive, cross sensor-motor connections, meaning the reading from the left sensor positively impacts the velocity of the right wheel, and the right sensor positively impacts the left wheel.

+ “Love” has negative, directly sensor-motor connections, meaning the reading from the left sensor negatively (i.e. the stronger the signal, the slower the wheel moves) impacts the velocity of the left wheel.

+ “Explore” has negative, cross sensor-motor connections.

In this simulation, each robot has four sensors: two food sensors and two light sensors. For each pair of sensors, they are in the front of the robot, 40 degrees from the robot’s heading direction on both sides. Sensor readings are directly related to wheel velocities(motors). Robot will perform "Fear" or "Explore" against light source and may perform "Love" against food according to its hungery level.  

When the food entities are turnned on (default), robot will get hungry in 30 seconds and becomes very hungry in 2 minutes unless it contact food. When robot is hungry, it will keep its own braitenberg type against lights (fear/explore), but will sense food as well (perform love against foods). When the robot is very hungry, it will only perform love against food. When a robot has not been contact any food in 2.5 minutes, it will die and the simulation will end. Robot will eat food and reset its hungerness when it is less than 5 pixels close to a food.

### How to use this simulation

Firstly, open a command window in the .../iteration3 directory. Then run the following code

```
make -C ./src
./build/bin/arenaviewer
```

This will open a window for the simulation. There is a graphic area and a Menu.

+ Graphic Arena: You can adjust graphic window for optimal experience, but the white rectangle is the arena area (all simulation will happen inside of it).

+ Menu: You can control the simulation through this menu.

**All controls other than Start/Pause/Play and New Game will take effect after clicking New Game**

|   Title  |  Type   |  Functionality   |
|   -----  |  ----   | --------------  |
| Start/Pause/Play | Button | Start a simulation / Pause the simulation/ Resume the simulation from a paused state|
| New Game | Button | Start a new simulation |
| Food On/ Food Off | Button | Turn the food entity on / off `*`|
| Number of Robots | Slider | Adjust the number of Robots in the simulation|
| Number of Lights | Slider | Adjust the number of Lights in the simulation|
| Number of Foods | Slider | Adjust the number of Foods in the simulation|
| Fear Ratio(%) | Slider | Adjust the ratio of vehicles performing fear in all robots `**`|
|Sensitivity| Slider | Adjust the sensor sensitivity [0 - 1800], larger number means more sentitive|


***

Notes:

`* : Turnning off the food entity will stop the robot from getting hungry. Keep the food entities on and change the number of foods to 0 will look like turnning off the food entity, but in this condition, robots will still get hungry over time.`

`** : This is a percentage value: 50 means 50%. The ratio mean (number of fear robots) / (number of all robots). i.e. Fear ratio(%) = 20, Number of Robots = 10 => 2 Fear robots and 8 explore robots. The actural ratio is to the cloest ratio that the slider is set to.  `



## Developer Guide

### Observer Pattern

**stimuli (observable) – robot/sensor (observer)**

The observer pattern has subjects which contains a list of its observers. Subjects will notify observers automatically of any state changes, usually by calling one of their methods. Observer pattern is mainly used to implement distributed event handling systems.  In this project, stimulus are subjects. Their positions will affect the behavior of robots.

In this pattern, stimulus are subjects and sensors are observers.

The simulation will call the UpdateEntitiesTimeStep() function in arena in order to get the information for the next time instance. This function will then call every entities’ TimestepUpdate() method. Since robot’s movement is affected by the sensor’s readings, all entities other than robots should first update their positions and notify sensors. Then robots will calculate wheel speed according to the sensor readings.

In the implementation, arena is used as a medium to forward states. Non-robot entities will first update their states. Then arena immediately call notify on all robots and send them the info of the updated stimuli.

`robot_[i]->notify_light(ent->get_pose(),ent->get_radius());`

and

`robot_[i]->notify_light(ent->get_pose(),ent->get_radius());`

Robot’s notify methods receives this info and pass them to sensors. Sensors will keep track of all these readings. When all non-robot entities have finished, robot will perform corresponding behavior according to the readings.

### Strategy Pattern

**MotionHandlerRobot as Strategy Interface**

Strategy pattern enables selecting an algorithm at runtime. Instead of implementing a single algorithm directly in the robot class, the project receives run-time instruction to determine which behavior mode a robot should use.

The project use MotionHandlerRobot as the strategy interface, as shown in the diagram. Robots’ behavior varies according to light readings. There are only two types of behavior: fear and explore. Hunger level is related as well and will change the behavior. But Fear and Explore are the types making the definitive call for what function a robot should perform. So, I integrated Aggressive behavior into Fear and Explore, based on the input hunger level(int). Robot will receive readings from all sensors and calculate wheel speed respect to the hunger condition.

### Add New Stimuli

Suppose we want to add stimuli type A.

1. In entity_type.h : add kA as type name.

2. Create A class, inherited from either ArenaMobileEntity or ArenaImmobileEntity. When creating the class, mobile entity should follow the class structure of light while immobile entity should follow the class structure of food.

+	Create a.h and a.cc.

+	Make sure include arena_mobile_entity / arena_immobile_entity.

+	Use the correct header and namespace.

+	Class declared as A::ArenaMobileEntity / A:: ArenaImmobileEntity.

3. In entity_factory.h and entity_factory.cc, add CreateA() function and modify the case in CreateEntity() function.
Add switch etype and create corresponding CreatA() function.

4. In arena.h, if A is mobile entity, add A to its attribute.

5. In arena.cc, update constructor, call the AddEntity to add A instances.

6. In arena.cc, modify UpdateEntityTimestep() to track the case of type A.

7. In arena.cc, modify IsColliding() function to make sure instances of A pass/not pass certain entities.

8. If A is mobile and want to perform different motion behavior, create a new class MotionHandlerA, which should be inherited from MotionHandler. To perform different functionality, either override the original UpdateVelocity() or create a new one. If a new one is created, it should be called in A.cc’s TimestepUpdate().

### Add New Sensor

Suppose we have created a new stimuli type A, now we want to create a new type of sensor.

1. Create Sensor_A class. If it detects ranged objects and returns readings, it should inherit from Sensor class, otherwise you should create new sensor class and skip the following step.

+ Create sensor_a.h and sensor_a.cc

+ Make sure include sensor.h

+ Use the right header and namespace

+ Class declared as Sensor_A::Sensor

2. In robot.h and robot.cc, add Sensor_A to attribute and update constructor.

3. In robot.h and robot.cc, create Notify_A() function. It should be similar to Notify_Light() function. Then modify resetsensor() function to reset Sensor_A.

4. If Sensor_A is at the same location of sensor_light, it can just use sensor_position[]. Otherwise create a new array sensor_position_A[2], and create a new function set_sensor_A_position() to calculate new sensor’s position.

5. In arena.cc, modify UpdateEntityTimestep(). After an A instance is updated, the arena should immediately call notify_A on all robots, similar to the notify_light call.

6. In a_sensor.h, there should be a function to calculate reading, similar to the one in SensorFood. It should be implemented in a_sensor.cc.  

7. Modify MotionHandlerRobot() interface to receive these readings in UpdateVelocity_Robot() function. Suggestion: add a_l and a_r to pass left and right a_sensor readings.

8. Modify MotionHandlerRotboFear and Modify MotionhandlerRobotExplore to handle these readings. If the robot performs functions similar to food, then motionhandler should handle readings similar to food sensor reading. If the robot has other functions, then you should create new MotionHandlerRobotTypeA, similar to MotionHandlerRobotFear.
