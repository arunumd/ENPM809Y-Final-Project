/*
 * @file        MobileRobot_FSM.cpp
 * @author      Arun Kumar Devarajulu
 * @author      Zuyang Cao
 * @author      Qidi Xu
 * @author      Hongyang Jiang
 * @date        05/10/2019
 * @brief       The file MobileRobot_FSM.cpp contains the implementation details of
 *              finite state machine
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
#include <string>
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

MobileRobot::MobileRobot(std::string RobotName) {
    name_ = std::move(RobotName);
}

void WheeledRobot::HandleInput(const std::string &input) {
    state::RobotState *state = new state::UpState();

    if (robot_stack_.empty())
        state->HandleInput(robot_stack_, input);
    else
        robot_stack_.top()->HandleInput(robot_stack_, input);
    delete state;
}

void TrackedRobot::HandleInput(const std::string &input) {
    state::RobotState *state = new state::UpState();

    if (robot_stack_.empty())
        state->HandleInput(robot_stack_, input);
    else
        robot_stack_.top()->HandleInput(robot_stack_, input);
    delete state;
}

void WheeledRobot::ShowStack() {
    auto s = robot_stack_;
    while (s.size() > 1) {
        printf("%s\n", s.top()->get_name().c_str());
        s.pop();
    }
    printf("\n");
}

void TrackedRobot::ShowStack() {
    auto s = robot_stack_;
    while (s.size() > 1) {
        printf("%s\n", s.top()->get_name().c_str());
        s.pop();
    }
    printf("\n");
}

std::string MobileRobot::get_name() {
    return name_;
}

// UpState::UpState()

void state::UpState::HandleInput(std::stack<state::RobotState *> &stack_,
                                 const std::string &input) {
    if (stack_.empty()) {
        stack_.push(this);
    }
    if (input == "UP") {
        RobotState *UP_PTR = new UpState();
        stack_.push(UP_PTR);
    }
    if (input == "DOWN") {
        RobotState *DOWN_PTR = new DownState();
        stack_.push(DOWN_PTR);
    }
    if (input == "LEFT") {
        RobotState *LEFT_PTR = new LeftState();
        stack_.push(LEFT_PTR);
    }
    if (input == "RIGHT") {
        RobotState *RIGHT_PTR = new RightState();
        stack_.push(RIGHT_PTR);
    }
}

void state::DownState::HandleInput(std::stack<state::RobotState *> &stack_,
                                   const std::string &input) {
    if (stack_.empty()) {
        stack_.push(this);
    }
    if (input == "UP") {
        RobotState *UP_PTR = new UpState();
        stack_.push(UP_PTR);
    }
    if (input == "DOWN") {
        RobotState *DOWN_PTR = new DownState();
        stack_.push(DOWN_PTR);
    }
    if (input == "LEFT") {
        RobotState *LEFT_PTR = new LeftState();
        stack_.push(LEFT_PTR);
    }
    if (input == "RIGHT") {
        RobotState *RIGHT_PTR = new RightState();
        stack_.push(RIGHT_PTR);
    }
}

void state::LeftState::HandleInput(std::stack<RobotState *> &stack_,
                                   const std::string &input) {
    if (stack_.empty()) {
        stack_.push(this);
    }
    if (input == "UP") {
        RobotState *UP_PTR = new UpState();
        stack_.push(UP_PTR);
    }
    if (input == "DOWN") {
        RobotState *DOWN_PTR = new DownState();
        stack_.push(DOWN_PTR);
    }
    if (input == "LEFT") {
        RobotState *LEFT_PTR = new LeftState();
        stack_.push(LEFT_PTR);
    }
    if (input == "RIGHT") {
        RobotState *RIGHT_PTR = new RightState();
        stack_.push(RIGHT_PTR);
    }
}

void state::RightState::HandleInput(std::stack<state::RobotState *> &stack_,
                                    const std::string &input) {
    if (stack_.empty()) {
        stack_.push(this);
    }
    if (input == "UP") {
        RobotState *UP_PTR = new UpState();
        stack_.push(UP_PTR);
    }
    if (input == "DOWN") {
        RobotState *DOWN_PTR = new DownState();
        stack_.push(DOWN_PTR);
    }
    if (input == "LEFT") {
        RobotState *LEFT_PTR = new LeftState();
        stack_.push(LEFT_PTR);
    }
    if (input == "RIGHT") {
        RobotState *RIGHT_PTR = new RightState();
        stack_.push(RIGHT_PTR);
    }
}
