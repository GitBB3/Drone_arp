## Frontend ARP drone simulation project

# Open the similation

1) Clone the repository https://github.com/GitBB3/Drone_arp.git
2) Compile the repository: make
3) Execute the simulation: ./bin/drone_arp

# Inspection window

You can see the inspection window on the right side.
It shows you what keys to use to command the drone and what is the current position of the drone and what forces are imposed on it (Fx/Fy is the command force imposed by you on the keyboard, Fr_x/Fr_y is the repulsive force caused by the obstacles).

# Environment of the drone
The left window is the environment where the drone will evolve.
- "+" is your drone
- "o" are obstacles, appearing in random places for a random time. They create a repulsive force. You should avoid them.
- "_number_" are targets, appearing in random places. Try to reach them in the order of their number. They don't move until you reach them and then disappear, while a new one is spawned randomly in the environment.

# Command the simulation
Several commands enable you to command the simulation:
- Press "F" to FREEZE/UNFREEZE the simulation. You should unfreeze at the beginning of the simulation. When you freeze the environment, time stops and nothing moves anymore. Note that forces and positions will be exactly the same at the moment you freeze and at the moment you unfreeze.
- Press "ESC" to END the simulation. Windows are closed and you go back to the terminal.

# Command the drone
Once unfreezed, you can use the keys to move the drone:
- Use the square e/r/t/g/b/v/c/d to move up-left/up/up-right/right/down-right/down/down-left/left
- Press "S" to STOP the command: it puts the command forces to 0. However, inertia and repulsion might still make the drone move.

# Parameters
Feel free to change some parameters of the simulation in the code of "src/main.c":
- nb_obs: number of obstacles present in the environment at the same time
- nb_tar: number of targets present in the environment at the same time
- M: mass of the drone
- K: friction factor
- T: integration interval
- lifetime_interval (max and min): min and max time that an obstacle can leave
- repulsion_param
- detection_threshold: maximu distance at which the drone detect an obstacle
- dist_threshold: distance between the drone and an obstacle/target under which we consider that the obstacle/target is reached
