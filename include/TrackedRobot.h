/*!
 * \file        TrackedRobot.h
 * \author      Arun Kumar Devarajulu
 * \author      Zuyang Cao
 * \author      Qidi Xu
 * \author      Hongyang Jiang
 * \date        05/10/2019
 * \brief       The file TrackedRobot.h contains the header declarations for TrackedRobot
 *              class. The class will be used for implementation of finite state machine
 *              in Final Project.
 * \license     This project is released under the MIT License.
 */

#ifndef ENPM809Y_PROJECT_5_TRACKEDROBOT_H
#define ENPM809Y_PROJECT_5_TRACKEDROBOT_H

#include <iostream>
#include <stack>
#include <string>
#include "MobileRobot.h"
#include "RobotState.h"

/*!
 * \class TrackedRobot
 * \brief The TrackedRobot class handles state inputs and stores state stack
 * for the pushdown automata.
 * */
class TrackedRobot : public MobileRobot {
public:
    /*! \brief Constructor to initialize the name as "Tracked Robot". */
    TrackedRobot() : MobileRobot("Tracked Robot") {};

    /*! \brief Default destructor*/
    ~TrackedRobot() = default;

    /*!
     * \brief Virtual function to handle input.
     * \param input - input robot state.
     * */
    void HandleInput(const std::string &input) override;

    /*! \brief Function to print the stack.*/
    void ShowStack() override;

private:
    /*! \brief Stack to store robot states for the
     * pushdown automata.
     * */
    std::stack<state::RobotState *> robot_stack_;
};

#endif // ENPM809Y_PROJECT_5_TRACKEDROBOT_H
