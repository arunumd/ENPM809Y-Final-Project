// Classes Target and Maze Start
#include <array>
#include <cmath>
#include <iostream>
#include <utility>
#include <memory>
#include "../include/Maze.h"
#include "../include/Target.h"
#include "../include/DownState.h"
#include "../include/UpState.h"
#include "../include/LeftState.h"
#include "../include/RightState.h"
#include "../include/RobotState.h"
#include "../include/MobileRobot.h"
#include "../include/WheeledRobot.h"
#include "../include/TrackedRobot.h"

void Target::AssignLocations(std::array<Location *, 4> &palette,
                             const int &index, const int &l, const int &w) {
    while (true) {
        std::cin >> palette[index]->x >> palette[index]->y;
        if (palette[index]->x >= l || palette[index]->x < 0 ||
            palette[index]->y >= w || palette[index]->y < 0) {
            std::cout << "Position out of maze, please try again." << std::endl;
            continue;
        } else if (tempMaze.IsNotObstacle(std::make_pair(palette[index]->x, palette[index]->y)))
            break;
        else {
            std::cout << "Position is blocked, please try again." << std::endl;
            continue;
        }
    }
}

void Target::SetPositions() {
    int length = tempMaze.GetLength();
    int width = tempMaze.GetWidth();
    tempMaze.ShowMaze();
    std::array<Location *, 4> palette{&wheeled, &tracked, &bottle, &plate};
    for (std::size_t i = 0; i <= 3; i++) {
        if (i == 0) {
            std::cout << "\n\nPlease enter starting point for wheeled "
                         "robot: x y" << std::endl;
            AssignLocations(palette, i, length, width);
            tempMaze.ModifyMazePosition(wheeled.x, wheeled.y, 'w');
        } else if (i == 1) {
            std::cout << "\n\nPlease enter starting point for tracked "
                         "robot: x y" << std::endl;
            AssignLocations(palette, i, length, width);
            tempMaze.ModifyMazePosition(tracked.x, tracked.y, 't');
        } else if (i == 2) {
            std::cout << "\n\nPlease enter location for bottle: "
                         "x y" << std::endl;
            AssignLocations(palette, i, length, width);
            tempMaze.ModifyMazePosition(bottle.x, bottle.y, 'b');
        } else {
            std::cout << "\n\nPlease enter location for plate: "
                         "x y" << std::endl;
            AssignLocations(palette, i, length, width);
            tempMaze.ModifyMazePosition(plate.x, plate.y, 'p');
        }
    }
    tempMaze.ShowMaze();
}

void Target::AssignTasks() {
    while (true) {
        std::cout << "\nPlease choose target for wheeled robot, "
                     "plate or the bottle: p/b\n" << std::endl;
        std::cin >> wheeled_target;
        if (wheeled_target == 'P') {
            wheeled_target = 'p';
        }
        if (wheeled_target == 'B') {
            wheeled_target = 'b';
        }
        if (wheeled_target == 'p' or wheeled_target == 'b') {
            break;
        } else {
            std::cout << "Invalid input, please try again.";
            continue;
        }
    }
    if (wheeled_target == 'p') {
        tracked_target = 'b';
    } else {
        tracked_target = 'p';
    }
}

int Target::GoWheeled() {
    if (wheeled_target == 'p') {
        wheeledMaze.SetStartGoal(wheeled.x, wheeled.y, plate.x, plate.y);
    } else {
        wheeledMaze.SetStartGoal(wheeled.x, wheeled.y, bottle.x, bottle.y);
    }
    wheeledMaze.Action();
    int is_blocked = wheeledMaze.PlotTrajectory('|');
    wheeledMaze.ModifyMazePosition(wheeled.x, wheeled.y, 'w');
    if (wheeled_target == 'p') {
        wheeledMaze.ModifyMazePosition(plate.x, plate.y, 'p');
    } else {
        wheeledMaze.ModifyMazePosition(bottle.x, bottle.y, 'b');
    }
    wheeledMaze.ShowMaze();
    wheeledMaze.BuildStack(wheeledRobotInMaze);
    wheeledRobotInMaze->ShowStack();
    return is_blocked;
}

int Target::GoTracked() {
    if (tracked_target == 'p') {
        trackedMaze.SetStartGoal(tracked.x, tracked.y, plate.x, plate.y);
    } else {
        trackedMaze.SetStartGoal(tracked.x, tracked.y, bottle.x, bottle.y);
    }
    trackedMaze.Action();
    int is_blocked = trackedMaze.PlotTrajectory('-');
    trackedMaze.ModifyMazePosition(tracked.x, tracked.y, 't');
    if (tracked_target == 'p') {
        trackedMaze.ModifyMazePosition(plate.x, plate.y, 'p');
    } else {
        trackedMaze.ModifyMazePosition(bottle.x, bottle.y, 'b');
    }
    trackedMaze.ShowMaze();
    trackedMaze.BuildStack(trackedRobotInMaze);
    trackedRobotInMaze->ShowStack();
    return is_blocked;
}

void Target::PlotMaze() {
    for (int j = tempMaze.GetWidth() - 1; j >= 0; j--) {
        for (int i = 0; i < tempMaze.GetLength(); i++) {
            if (wheeledMaze.GetMazePosition(i, j) == '|' and
                trackedMaze.GetMazePosition(i, j) == '-') {
                tempMaze.ModifyMazePosition(i, j, '+');
            } else if (wheeledMaze.GetMazePosition(i, j) == '|') {
                tempMaze.ModifyMazePosition(i, j, '|');
            } else if (trackedMaze.GetMazePosition(i, j) == '-') {
                tempMaze.ModifyMazePosition(i, j, '-');
            }
        }
    }
    tempMaze.ModifyMazePosition(bottle.x, bottle.y, 'b');
    tempMaze.ModifyMazePosition(plate.x, plate.y, 'p');
    tempMaze.ModifyMazePosition(wheeled.x, wheeled.y, 'w');
    tempMaze.ModifyMazePosition(tracked.x, tracked.y, 't');
    tempMaze.ShowMaze();
    std::cout << std::endl;
}
