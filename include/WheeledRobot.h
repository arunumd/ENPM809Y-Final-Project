/*!
 * @file        WheeledRobot.h
 * @author      Arun Kumar Devarajulu
 * @author      Zuyang Cao
 * @author      Qidi Xu
 * @author      Hongyang Jiang
 * @date        05/10/2019
 * @brief       The file WheeledRobot.h contains the header declarations for WheeledRobot
 *              class. The class will be used for implementation of finite state machine
 *              in Final Project.
 * @license     This project is released under the MIT License.
 */

#ifndef ENPM809Y_PROJECT_5_WHEELEDROBOT_H
#define ENPM809Y_PROJECT_5_WHEELEDROBOT_H

#include <iostream>
#include <stack>
#include <string>
#include "MobileRobot.h"
#include "RobotState.h"

/*!
 * @class WheeledRobot
 * @brief The WheeledRobot class handles state inputs and stores state stack 
 * for the pushdown automata.
 * */
class WheeledRobot : public MobileRobot {
public:
    /*! @brief Constructor to initialize the name as "Wheeled Robot". */
    WheeledRobot() : MobileRobot("Wheeled Robot") {};

    /*! @brief Default destructor*/
    ~WheeledRobot() = default;

    /*!
     * @brief Virtual function to handle input.
     * @param input - input robot state.
     * */
    void HandleInput(const std::string &input) override;

    /*! @brief Function to print the stack.*/
    void ShowStack() override;

private:
    /*!
     * @brief Stack to store robot states for the
     * pushdown automata.
     * */
    std::stack<state::RobotState *> robot_stack_;
};

#endif // ENPM809Y_PROJECT_5_WHEELEDROBOT_H
