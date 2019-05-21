/*
 * @file        Target.cpp
 * @author      Arun Kumar Devarajulu
 * @author      Zuyang Cao
 * @author      Qidi Xu
 * @author      Hongyang Jiang
 * @date        05/10/2019
 * @brief       The file Target.cpp contains the definitions for the target class
 * @license     MIT License
 *              Permission is hereby granted, free of charge, to any person obtaining a copy
 *              of this software and associated documentation files (the "Software"), to deal
 *              in the Software without restriction, including without limitation the rights
 *              to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *              copies of the Software, and to permit persons to whom the Software is
 *              furnished to do so, subject to the following conditions:
 *
 *              The above copyright notice and this permission notice shall be included in all
 *              copies or substantial portions of the Software.
 *
 *              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *              IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *              FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 *              AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *              LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *              OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *              SOFTWARE.
 */

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
        std::cin >> palette[index]->x;
        if (std::cin.fail()) {
            std::cout << "Invalid x coordinate. "
                         "Please enter x and y in space "
                         "separated format again" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin >> palette[index]->y;
        if (std::cin.fail()) {
            std::cout << "Invalid y coordinate. "
                         "Please enter x and y in space "
                         "separated format again" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (palette[index]->x >= l || palette[index]->x < 0 ||
            palette[index]->y >= w || palette[index]->y < 0) {
            std::cout << "Position out of maze, "
                         "Please enter x and y in space "
                         "separated format again" << std::endl;
            palette[index]->x = -10;
            palette[index]->y = -10;
            continue;
        } else if (temp_maze_.IsNotObstacle(std::make_pair(palette[index]->x,
                                                           palette[index]->y)))
            break;
        else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Position is blocked, "
                         "Please enter x and y in space "
                         "separated format again" << std::endl;
            palette[index]->x = -10;
            palette[index]->y = -10;
            continue;
        }
    }
}

void Target::SetPositions() {
    int length = temp_maze_.get_length();
    int width = temp_maze_.get_width();
    temp_maze_.ShowMaze();
    std::array<Location *, 4> palette{&wheeled_, &tracked_, &bottle_, &plate_};
    for (std::size_t i = 0; i <= 3; i++) {
        if (i == 0) {
            std::cout << "\n\nPlease enter starting point for wheeled "
                         "robot: x y" << std::endl;
            AssignLocations(palette, i, length, width);
            temp_maze_.ModifyMazePosition(wheeled_.x, wheeled_.y, 'w');
        } else if (i == 1) {
            std::cout << "\n\nPlease enter starting point for tracked "
                         "robot: x y" << std::endl;
            AssignLocations(palette, i, length, width);
            temp_maze_.ModifyMazePosition(tracked_.x, tracked_.y, 't');
        } else if (i == 2) {
            std::cout << "\n\nPlease enter location for bottle: "
                         "x y" << std::endl;
            AssignLocations(palette, i, length, width);
            temp_maze_.ModifyMazePosition(bottle_.x, bottle_.y, 'b');
        } else {
            std::cout << "\n\nPlease enter location for plate: "
                         "x y" << std::endl;
            AssignLocations(palette, i, length, width);
            temp_maze_.ModifyMazePosition(plate_.x, plate_.y, 'p');
        }
    }
    temp_maze_.ShowMaze();
}

void Target::AssignTasks() {
    while (true) {
        std::cout << "\nPlease choose target for wheeled robot, "
                     "plate or the bottle: p/b\n" << std::endl;
        std::cin >> wheeled_target_;
        if (wheeled_target_ == 'P') {
            wheeled_target_ = 'p';
        }
        if (wheeled_target_ == 'B') {
            wheeled_target_ = 'b';
        }
        if (wheeled_target_ == 'p' or wheeled_target_ == 'b') {
            break;
        } else {
            std::cout << "Invalid input, please try again.";
            continue;
        }
    }
    if (wheeled_target_ == 'p') {
        tracked_target_ = 'b';
    } else {
        tracked_target_ = 'p';
    }
}

int Target::GoWheeled() {
    if (wheeled_target_ == 'p') {
        wheeled_maze_.SetStartGoal(wheeled_.x, wheeled_.y, plate_.x, plate_.y);
    } else {
        wheeled_maze_.SetStartGoal(wheeled_.x, wheeled_.y, bottle_.x, bottle_.y);
    }
    wheeled_maze_.Action();
    int is_blocked = wheeled_maze_.PlotTrajectory('|');
    wheeled_maze_.ModifyMazePosition(wheeled_.x, wheeled_.y, 'w');
    if (wheeled_target_ == 'p') {
        wheeled_maze_.ModifyMazePosition(plate_.x, plate_.y, 'p');
    } else {
        wheeled_maze_.ModifyMazePosition(bottle_.x, bottle_.y, 'b');
    }
    wheeled_maze_.ShowMaze();
    wheeled_maze_.BuildStack(wheeled_robot_in_maze_);
    wheeled_robot_in_maze_->ShowStack();
    return is_blocked;
}

int Target::GoTracked() {
    if (tracked_target_ == 'p') {
        tracked_maze_.SetStartGoal(tracked_.x, tracked_.y, plate_.x, plate_.y);
    } else {
        tracked_maze_.SetStartGoal(tracked_.x, tracked_.y, bottle_.x, bottle_.y);
    }
    tracked_maze_.Action();
    int is_blocked = tracked_maze_.PlotTrajectory('-');
    tracked_maze_.ModifyMazePosition(tracked_.x, tracked_.y, 't');
    if (tracked_target_ == 'p') {
        tracked_maze_.ModifyMazePosition(plate_.x, plate_.y, 'p');
    } else {
        tracked_maze_.ModifyMazePosition(bottle_.x, bottle_.y, 'b');
    }
    tracked_maze_.ShowMaze();
    tracked_maze_.BuildStack(tracked_robot_in_maze_);
    tracked_robot_in_maze_->ShowStack();
    return is_blocked;
}

void Target::PlotMaze() {
    for (int j = temp_maze_.get_width() - 1; j >= 0; j--) {
        for (int i = 0; i < temp_maze_.get_length(); i++) {
            if (wheeled_maze_.GetMazePosition(i, j) == '|' and
                tracked_maze_.GetMazePosition(i, j) == '-') {
                temp_maze_.ModifyMazePosition(i, j, '+');
            } else if (wheeled_maze_.GetMazePosition(i, j) == '|') {
                temp_maze_.ModifyMazePosition(i, j, '|');
            } else if (tracked_maze_.GetMazePosition(i, j) == '-') {
                temp_maze_.ModifyMazePosition(i, j, '-');
            }
        }
    }
    temp_maze_.ModifyMazePosition(bottle_.x, bottle_.y, 'b');
    temp_maze_.ModifyMazePosition(plate_.x, plate_.y, 'p');
    temp_maze_.ModifyMazePosition(wheeled_.x, wheeled_.y, 'w');
    temp_maze_.ModifyMazePosition(tracked_.x, tracked_.y, 't');
    temp_maze_.ShowMaze();
    std::cout << std::endl;
}
