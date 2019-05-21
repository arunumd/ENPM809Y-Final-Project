/*!
 * \file        UpState.h
 * \author      Arun Kumar Devarajulu
 * \author      Zuyang Cao
 * \author      Qidi Xu
 * \author      Hongyang Jiang
 * \date        05/10/2019
 * \brief       The file UpState.h contains the header declarations for UpState
 *              class. The class will be used for implementation of finite state machine
 *              in Final Project.
 * \license     This project is released under the MIT License.
 */

#ifndef ENPM809Y_PROJECT_5_UPSTATE_H
#define ENPM809Y_PROJECT_5_UPSTATE_H

#include <iostream>
#include <stack>
#include <string>
#include "RobotState.h"

/*!
 * \class UpState
 * \brief The UpState class is part of the finite state machine. It has its own 
 * HandleInput function realization. Although in this program, the HandleInput  
 * function is always the same for each state, but for further implementation, 
 * it can be modified here.
 * */
namespace state {
    class UpState : public RobotState {
    public:
        /*! \brief Inheritance UpState from RobotState */
        UpState() : RobotState("Up") {}

        /*!
         * \brief Push current node location into stack while update the new node
         * according to the previous move
         * */
        void HandleInput(std::stack<RobotState *> &, const std::string &) override;

        /*! \brief Default destructor */
        ~UpState() override = default;
    };
}

#endif // ENPM809Y_PROJECT_5_UPSTATE_H
