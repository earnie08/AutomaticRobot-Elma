Security Gard Robot - Elma 
===


Project Goal :
---
A security gard robot will wandering in a 2D array map with a time period. The robot will stop and make noise after it found an intruder in its detecting area. If the intruder is too close to the robot, the robot will evade 2x times per time. 
Moreover, user can choose to set the robot by codes or write a Json file.


Project Concept:
---

- ### [Elma](https://github.com/klavinslab/elma_project):
    Elma is an event loop and process manager for embedded systems. It keeps track of processes, executes them at specified frequencies, and enables interprocess communication. It includes interprocess communications, event management, and finite state machines.
- ### Map Info:
    A 2D array map recording and showing the robot position, charge station position and intruder position.<br><br>
    <img src="2D-Array-Map.png" alt="2D array map" title="Security Gard Robot Map" width="30%"/>

- ### Battery:
    Robot's battery.<br>
    Including battery status and consuming rate.<br><br>

- ### Intruder:
    Set intruder's position on map randomly.

- ### Robot States:
    A state machine with models below([link](https://github.com/klavins/ECEP520/tree/master/week_7)):

    <img src="robot-states.png" alt="GitHub" title="GitHub,Social Coding" width="100%"/>

- ### Robot Core:
    1. Combined map info, battery and robot states.
    2. Robot will go up/down/left/right randomly.
    3. Detecting the intruder's postion.
    4. Monitoring battery's status.
    5. Show the map and status on terminal.

Milestones:
---

1. To implement an automatically wandering robot on a 2D array map and also caculate the battery consuming and charging logic into robot's core system.

2. Adding a few featurers to robot which makes some actions after randomly dropped intruder in map.

3. Completing the API documentation.

3. (TBD) Adding a function letting user can set all the robot logic in a json file and get the latest status through http protacal "GET".

4. (TBD) Add a function letting user interact with robot through http protocal "POST".

5. (TBD) Transform the robot in 2D map into graphic user interface.