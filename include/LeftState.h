/*!
 * \file        LeftState.h
 * \author      Arun Kumar Devarajulu
 * \author      Zuyang Cao
 * \author      Qidi Xu
 * \author      Hongyang Jiang
 * \date        05/10/2019
 * \brief       The file LeftState contains the header declarations for LeftState
 *              class. The class will be used for implementation of finite state machine
 *              in Final Project.
 * \license     This project is released under the MIT License.
 */

#ifndef ENPM809Y_PROJECT_5_LEFTSTATE_H
#define ENPM809Y_PROJECT_5_LEFTSTATE_H

#include <iostream>
#include <stack>
#include <string>
#include "../include/RobotState.h"

/*!
 * \class LeftState
 * \brief The LeftState class is part of the finite state machine. It has its own 
 * HandleInput function realization. Although in this program, the HandleInput  
 * function is always the same for each state, but for further implementation, 
 * it can be modified here.
 * */

namespace state {
    class LeftState : public RobotState {
    public:
        /*! \brief Inheritance LeftState from RobotState */
        LeftState() : RobotState("Left") {}

        /*! \brief Push current node location into stack while update the new node
         * according to the previous move
         * */
        void HandleInput(std::stack<RobotState *> &, const std::string &) override;

        /*! \brief Default destructor */
        ~LeftState() override = default;
    };
}

#endif // ENPM809Y_PROJECT_5_LEFTSTATE_H
