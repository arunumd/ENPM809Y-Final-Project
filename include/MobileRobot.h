/*
 * @file        MobileRobot.h
 * @author      Arun Kumar Devarajulu
 * @author      Zuyang Cao
 * @author      Qidi Xu
 * @author      Hongyang Jiang
 * @date        05/10/2019
 * @brief       The file MobileRobot.h contains the header declarations for MobileRobot
 *              class. The class will be used for implementation of finite state machine
 *              in Final Project
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

#ifndef ENPM809Y_PROJECT_5_MOBILEROBOT_H
#define ENPM809Y_PROJECT_5_MOBILEROBOT_H

#include <iostream>
#include <stack>
#include <string>
#include "RobotState.h"

/*
 * @brief The MobileRobot class is the base class for WheeledRobot class and
 * TrackedRobot.
 */
class MobileRobot {
public:
    /* @brief Default constructor */
    MobileRobot() = default;

    /* @brief Constructor with string input for the name member.
     * @param RobotName - name of the robot.
     */
    explicit MobileRobot(std::string RobotName);

    /* @brief Default destructor.*/
    ~MobileRobot() = default;

    /* @brief Virtual function to handle input.
     * @param input - input robot state.
     */
    virtual void HandleInput(const std::string &input) = 0;

    /* @brief Virtual function to print the stack.*/
    virtual void ShowStack() = 0;

    /*
     * @brief Function to get name.
     * @return name of the robot
     * */
    std::string get_name();

private:
    /* @brief Name member for the robot.*/
    std::string name_;
};

#endif // ENPM809Y_PROJECT_5_MOBILEROBOT_H
