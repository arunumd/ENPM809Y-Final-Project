cmake_minimum_required(VERSION 3.13)
project(Final_Version_809Y_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Final_Version_809Y_Project app/main.cpp app/Maze.cpp app/MobileRobot_FSM.cpp app/Target.cpp
        include/DownState.h include/LeftState.h include/Maze.h include/MobileRobot.h include/RightState.h
        include/RobotState.h include/Target.h include/TrackedRobot.h include/UpState.h include/WheeledRobot.h)