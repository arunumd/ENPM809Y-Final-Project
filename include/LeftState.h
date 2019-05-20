/*
 * @file        LeftState.h
 * @author      Arun Kumar Devarajulu
 * @author      Zuyang Cao
 * @author      Qidi Xu
 * @author      Hongyang Jiang
 * @date        05/10/2019
 * @brief       The file LeftState contains the header declarations for LeftState
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

#ifndef ENPM809Y_PROJECT_5_LEFTSTATE_H
#define ENPM809Y_PROJECT_5_LEFTSTATE_H

#include <iostream>
#include <stack>
#include <string>
#include "../include/RobotState.h"

/*
 * @brief The LeftState class is part of the finite state machine. It has its own 
 * HandleInput function realization. Although in this program, the HandleInput  
 * function is always the same for each state, but for further implementation, 
 * it can be modified here.
 * */

namespace state {
    class LeftState : public RobotState {
    public:
        /* @brief Inheritance LeftState from RobotState */
        LeftState() : RobotState("Left") {}

        /* @brief Push current node location into stack while update the new node
         * according to the previous move
         * */
        void HandleInput(std::stack<RobotState *> &, const std::string &) override;

        /* @brief Default destructor */
        ~LeftState() override = default;
    };
}

#endif // ENPM809Y_PROJECT_5_LEFTSTATE_H
