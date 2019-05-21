/*!
 * \file        MobileRobot.h
 * \author      Arun Kumar Devarajulu
 * \author      Zuyang Cao
 * \author      Qidi Xu
 * \author      Hongyang Jiang
 * \date        05/10/2019
 * \brief       The file MobileRobot.h contains the header declarations for MobileRobot
 *              class. The class will be used for implementation of finite state machine
 *              in Final Project.
 * \license     This project is released under the MIT License.
 */

#ifndef ENPM809Y_PROJECT_5_MOBILEROBOT_H
#define ENPM809Y_PROJECT_5_MOBILEROBOT_H

#include <iostream>
#include <stack>
#include <string>
#include "RobotState.h"

/*!
 * \class MobileRobot
 * \brief The MobileRobot class is the base class for WheeledRobot class and
 * TrackedRobot.
 */
class MobileRobot {
public:
    /*! \brief Default constructor */
    MobileRobot() = default;

    /*! \brief Constructor with string input for the name member.
     * \param RobotName - name of the robot.
     */
    explicit MobileRobot(std::string RobotName);

    /*! \brief Default destructor.*/
    ~MobileRobot() = default;

    /*! \brief Virtual function to handle input.
     * \param input - input robot state.
     */
    virtual void HandleInput(const std::string &input) = 0;

    /*! \brief Virtual function to print the stack.*/
    virtual void ShowStack() = 0;

    /*!
     * \brief Function to get name.
     * \return name of the robot
     * */
    std::string get_name();

private:
    /*! \brief Name member for the robot.*/
    std::string name_;
};

#endif // ENPM809Y_PROJECT_5_MOBILEROBOT_H
