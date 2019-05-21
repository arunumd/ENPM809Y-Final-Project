/*!
 * \file        RobotState.h
 * \author      Arun Kumar Devarajulu
 * \author      Zuyang Cao
 * \author      Qidi Xu
 * \author      Hongyang Jiang
 * \date        05/10/2019
 * \brief       The file RobotState.h contains the header declarations for RobotState
 *              class. The class will be used for implementation of finite state machine
 *              in Final Project.
 * \license     This project is released under the MIT License.
 */
#ifndef ENPM809Y_PROJECT_5_ROBOTSTATE_H
#define ENPM809Y_PROJECT_5_ROBOTSTATE_H

#include <iostream>
#include <stack>
#include <string>

/*!
 * \class RobotState
 * \brief The RobotState class is the base class for the later UpState, DownState,
 * LeftState and RightState. It contains a virtual function for handling state input
 * and a member to store the name of the state.
 */
namespace state {
    class RobotState {
    public:
        /*!
        \brief Process input and move the robot to the next node according to the given RobotState
        class
        \param string - sequence of move instruction
        \param stack - address of stack to gain access to the value while out of scope
        */
        virtual void HandleInput(std::stack<RobotState *> &, const std::string &) = 0;

        /*!
         * \brief Default constructor for RobotState class
         * \param name_ - name of RobotState
         * \param stack - address of stack to gain access to the value while out of scope
         * */
        explicit RobotState(std::string name = "RobotState") : name_{std::move(name)} {}

        /*! \brief Define default destructor */
        virtual ~RobotState() = default;

        /*!
         * \brief Get name value as string
         * \param name of RobotState
         * \return name of RobotState as string
         * */
        std::string get_name() { return name_; }

    private:
        /*! \brief Define the storage for name of RobotState */
        std::string name_;
    };
}

#endif // ENPM809Y_PROJECT_5_ROBOTSTATE_H
