/*
 * @file        RobotState.h
 * @author      Arun Kumar Devarajulu
 * @author      Zuyang Cao
 * @author      Qidi Xu
 * @author      Hongyang Jiang
 * @date        05/10/2019
 * @brief       The file RobotState.h contains the header declarations for RobotState
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
#ifndef ENPM809Y_PROJECT_5_ROBOTSTATE_H
#define ENPM809Y_PROJECT_5_ROBOTSTATE_H

#include <iostream>
#include <stack>
#include <string>

/*
 * @brief The RobotState class is the base class for the later UpState, DownState,
 * LeftState and RightState. It contains a virtual function for handling state input
 * and a member to store the name of the state.
 */
namespace state {
    class RobotState {
    public:
        /*
        @brief Process input and move the robot to the next node according to the given RobotState
        class
        @param string - sequence of move instruction
        @param stack - address of stack to gain access to the value while out of scope
        */
        virtual void HandleInput(std::stack<RobotState *> &, const std::string &) = 0;

        /*
         * @brief Default constructor for RobotState class
         * @param name_ - name of RobotState
         * @param stack - address of stack to gain access to the value while out of scope
         * */
        explicit RobotState(std::string name = "RobotState") : name_{std::move(name)} {}

        /* @brief Define default destructor */
        virtual ~RobotState() = default;

        /*
         * @brief Get name value as string
         * @param name of RobotState
         * @return name of RobotState as string
         * */
        std::string get_name() { return name_; }

    private:
        /* @brief Define the storage for name of RobotState */
        std::string name_;
    };
}

#endif // ENPM809Y_PROJECT_5_ROBOTSTATE_H
