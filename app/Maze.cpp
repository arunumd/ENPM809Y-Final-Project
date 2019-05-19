/*
 * @file        Maze.cpp
 * @author      Arun Kumar Devarajulu
 * @author      Zuyang Cao
 * @author      Qidi Xu
 * @author      Hongyang Jiang
 * @date        05/10/2019
 * @brief       The file Maze.cpp contains the definitions for Maze class
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
#include <stack>
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

int Maze::GetLength() const {
    return length;
}

int Maze::GetWidth() const {
    return width;
}

void Maze::ModifyMazePosition(int x, int y, char c) {
    if (grid_[y][x] == '#') {
        std::cout << "Modify maze failed, position blocked!" << std::endl;
        return;
    }
    grid_[y][x] = c;
}

char Maze::GetMazePosition(int x, int y) const {
    return char(grid_[y][x]);
}

void Maze::SetStartGoal(const int &start_x, const int &start_y,
                         const int &goal_x, const int &goal_y) {
    start_ = std::make_pair(start_x, start_y);
    goal_ = std::make_pair(goal_x, goal_y);
}

void Maze::ShowMaze() const {
    std::cout << "\n\n\n";
    for (int i = width - 1; i >= 0; i--) {
        if (i >= 10)
            std::cout << i << " ";
        else
            std::cout << i << "  ";
        for (int j = 0; j < length; j++) {
            std::cout << grid_[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "   ";
    for (int k = 0; k <= 9; k++) {
        std::cout << k << " ";
    }
    for (int l = 10; l < length; l++) {
        std::cout << l << "";
    }
    std::cout << std::endl;
    std::cout << "\n\n\n";
}

std::pair<int, int> Maze::North(const std::pair<int, int> &node) const {
    return std::make_pair(node.first, node.second - 1);
}

std::pair<int, int> Maze::East(const std::pair<int, int> &node) const {
    return std::make_pair(node.first + 1, node.second);
}

std::pair<int, int> Maze::West(const std::pair<int, int> &node) const {
    return std::make_pair(node.first - 1, node.second);
}

std::pair<int, int> Maze::South(const std::pair<int, int> &node) const {
    return std::make_pair(node.first, node.second + 1);
}

const double Maze::CalculateDistance(const std::pair<int, int> &current_node) const {
    return std::sqrt(std::pow(current_node.first - goal_.first, 2) +
                     std::pow(current_node.second - goal_.second, 2));
}

bool Maze::IsNotObstacle(const std::pair<int, int> &node) const {
    return grid_[node.second][node.first] != '#' &&
           grid_[node.second][node.first] != 'p' &&
           grid_[node.second][node.first] != 'b' &&
           grid_[node.second][node.first] != 'w' &&
           grid_[node.second][node.first] != 't';
}

bool Maze::IsWithinRegion(const std::pair<int, int> &node) const {
    return node.first >= 0 && node.first <= 45 &&
           node.second >= 0 && node.second <= 30;
}

const int Maze::TakeDecision1(const std::pair<int, int> &new_node,
                               const double &cost_g,
                               ListInfo &info,
                               const std::pair<int, int> &parent_node) {
    if (IsWithinRegion(new_node) && IsNotObstacle(new_node)) {
        info.cost_h = CalculateDistance(new_node);
        info.cost_g = cost_g + 1;
        info.total_cost = info.cost_g + info.cost_h;
        info.node = new_node;
        info.parent = parent_node;
        priority_list_.insert(std::pair<double, ListInfo>(info.total_cost, info));
        open_list_[info.node] = info;
        if (new_node == goal_) {
            closed_list_[new_node] = info;
            return 1;
        } else
            return -1;
    } else
        return -1;
}

const int Maze::TakeDecision2(const std::pair<int, int> &new_node,
                               const double &cost_g,
                               ListInfo &info,
                               const std::pair<int, int> &parent_node) {
    //< If the node is already there in closed list, then skip
    if (closed_list_.find(new_node) != closed_list_.end()) {
        if (new_node == goal_)
            return 1;
        else
            return -1;
    }
        //< If the new node is already there in open and priority lists
    else if (IsWithinRegion(new_node) && IsNotObstacle(new_node)) {
        if (open_list_.find(new_node) != open_list_.end()) {
            info.cost_h = CalculateDistance(new_node);
            info.cost_g = cost_g + 1;
            info.total_cost = info.cost_g + info.cost_h;
            info.node = new_node;
            info.parent = parent_node;
            ListInfo value = open_list_.find(new_node)->second;
            if (value.cost_g > info.cost_g) {
                open_list_.find(new_node)->second.cost_g = info.cost_g;
                open_list_.find(new_node)->second.cost_h = info.cost_h;
                open_list_.find(new_node)->second.total_cost = info.total_cost;
                open_list_.find(new_node)->second.parent = info.parent;
                auto it_range = priority_list_.equal_range(value.total_cost);
                for (auto itr = it_range.first; itr != it_range.second; ++itr) {
                    if (itr->second.node == new_node) {
                        itr->second.cost_g = info.cost_g;
                        itr->second.cost_h = info.cost_h;
                        itr->second.total_cost = info.total_cost;
                        itr->second.parent = info.parent;
                        break;
                    }
                }
            }
            return -1;
        } else { // If key could not be found in open list, then do the following --
            // Note: Even though priority list does not have key, it may have the same
            // cost f for a different key
            info.cost_h = CalculateDistance(new_node);
            info.cost_g = cost_g + 1;
            info.total_cost = info.cost_g + info.cost_h;
            info.node = new_node;
            info.parent = parent_node;
            if (new_node == goal_) {
                closed_list_[new_node] = info;
                return 1;
            } else {
                priority_list_.insert(std::pair<double, ListInfo>(info.total_cost, info));
                open_list_[info.node] = info;
                return -1;
            }
        }
    }
    return -1;
}

int Maze::Action() {
    // Initialize cost g, cost h, total cost, node no and parent no for root node
    double cost_h;
    double cost_g = 0;
    std::pair<int, int> parent_node{start_};
    std::pair<int, int> current_node{start_};
    cost_h = CalculateDistance(current_node);
    ListInfo info;
    info.cost_g = cost_g;
    info.cost_h = cost_h;
    info.total_cost = cost_g + cost_h;
    info.parent = current_node;
    info.node = current_node;
    // Assume that first node was pushed and popped from priority and open lists
    // Then add it to closed list
    closed_list_[current_node] = info;
    auto north_move = North(current_node);
    const int decision_north1 = TakeDecision1(north_move, cost_g, info, parent_node);
    if (decision_north1 == 1)
        return 1;
    auto south_move = South(current_node);
    const int decision_south1 = TakeDecision1(south_move, cost_g, info, parent_node);
    if (decision_south1 == 1)
        return 1;
    auto east_move = East(current_node);
    const int decision_east1 = TakeDecision1(east_move, cost_g, info, parent_node);
    if (decision_east1 == 1)
        return 1;
    auto west_move = West(current_node);
    const int decision_west1 = TakeDecision1(west_move, cost_g, info, parent_node);
    if (decision_west1 == 1)
        return 1; // Everything fine until here
    while (true) {
        // Pop the top element from priority list  <---- If priority list empty, then break while loop
        if (priority_list_.empty() && closed_list_.find(goal_) == closed_list_.end()) {
            return -1; // Goal node not in closed list and priority list is also empty
        } else if (priority_list_.empty() && closed_list_.find(goal_) != closed_list_.end()) {
            return 1; // Goal node is found in closed list and priority list is empty
        } else {
            auto low_cost_info = priority_list_.begin()->second;
            priority_list_.erase(priority_list_.begin());
            auto low_cost_node = low_cost_info.node;
            // Remove the same node from open list
            open_list_.erase(low_cost_node);
            closed_list_[low_cost_node] = low_cost_info;
            current_node = low_cost_node;
            parent_node = low_cost_node;
            cost_g = low_cost_info.cost_g;
            north_move = North(current_node);
            const int decision_north2 = TakeDecision2(north_move, cost_g, info, parent_node);
            if (decision_north2 == 1) {
                break;
            }
            south_move = South(current_node);
            const int decision_south2 = TakeDecision2(south_move, cost_g, info, parent_node);
            if (decision_south2 == 1) {
                break;
            }
            east_move = East(current_node);
            const int decision_east2 = TakeDecision2(east_move, cost_g, info, parent_node);
            if (decision_east2 == 1) {
                break;
            }
            west_move = West(current_node);
            const int decision_west2 = TakeDecision2(west_move, cost_g, info, parent_node);
            if (decision_west2 == 1) {
                break;
            }
        }
    }
    return 1;
}

int Maze::PlotTrajectory(const char &path_icon) {
    int status = Action();
    if (status == 1) {
        std::pair<int, int> node = goal_;
        std::pair<int, int> parent = closed_list_.find(node)->second.parent;
        while (parent != node) {
            if (node != goal_ || node != start_) {
                grid_[node.second][node.first] = path_icon;
            }
            node = closed_list_.find(parent)->second.node;
            parent = closed_list_.find(parent)->second.parent;
        }
    return 0; // Return 0 for a path exists.
    } else {
        return 1; // Return 1 for no path exists.
    }
}

void Maze::BuildStack(const std::shared_ptr<MobileRobot> &robot_in_maze) {
    int status = Action();
    if (status == 1) {
        std::pair<int, int> node = goal_;
        std::pair<int, int> parent = closed_list_.find(node)->second.parent;
        while (parent != node) {
            if (node != goal_ || node != start_) {
                if (parent.first - node.first == 1) {
                    robot_in_maze->HandleInput("LEFT");
                }
                if (parent.first - node.first == -1) {
                    robot_in_maze->HandleInput("RIGHT");
                }
                if (parent.second - node.second == 1) {
                    robot_in_maze->HandleInput("DOWN");
                }
                if (parent.second - node.second == -1) {
                    robot_in_maze->HandleInput("UP");
                }
                node = closed_list_.find(parent)->second.node;
                parent = closed_list_.find(parent)->second.parent;
            }
        }
    } else {
        std::cout << "No path for " << robot_in_maze->GetName() << std::endl;
    }
}
