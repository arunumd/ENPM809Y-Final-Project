/*
 * @file        main.cpp
 * @author      Arun Kumar Devarajulu
 * @author      Zuyang Cao
 * @author      Qidi Xu
 * @author      Hongyang Jiang
 * @date        05/10/2019
 * @brief       The file main.cpp contains the final implementation for ENPM809Y final project
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

#include <iostream>
#include <stack>
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

int main() {
    int is_both_blocked = 1;
    while(is_both_blocked){
        Target missions;
        missions.SetPositions();
        missions.AssignTasks();
        int is_wheeled_blocked = missions.GoWheeled();
        int is_tracked_blocked = missions.GoTracked();
        if(is_wheeled_blocked == 0 or is_tracked_blocked == 0){
            is_both_blocked = 0;
            missions.PlotMaze();
        }
        else {
            std::cout<<"\n\nNo path for both robots, please try again.\n\n";
        }
    }
    std::cout<<"\nAt least one path has been found! \nProgram finished.\n\n";
    return 0;
}
