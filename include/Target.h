/*!
 * \file        Target.h
 * \author      Arun Kumar Devarajulu
 * \author      Zuyang Cao
 * \author      Qidi Xu
 * \author      Hongyang Jiang
 * \date        05/07/2019
 * \brief       The file Target.h contains the header declarations for Target
 *              class. The class will be used for implementation of user interface,
 *              visualization etc in Final Project
 * \license     MIT License
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

#ifndef ENPM809Y_PROJECT_5_TARGET_H
#define ENPM809Y_PROJECT_5_TARGET_H

#include <iostream>
#include <utility>
#include <memory>
#include <array>
#include <map>
#include "Maze.h"
#include "MobileRobot.h"
#include "WheeledRobot.h"
#include "TrackedRobot.h"

/*!
 *\brief Define data structure that contain location (cartesian coordinates)
 *for robot and target locations
 * */
struct Location {
    int x = -1;
    int y = -1;
};

class Target {
public:
    /*! \brief  Define default constructor */
    Target() = default;

    /*! \brief  Define default destructor */
    ~Target() = default;

    /*!
     * \brief Asks user for tracked, wheeled robot starting point
     * and plate, bottle goal point. Input check will be conducted
     * to see if the given node is out of maze or blocked
     * */
    void SetPositions();

    /*!
     * \brief Assign task for tracked and wheeled robot to pick up
     * plant and bottle
     * */
    void AssignTasks();

    /*! \brief Initiates A* algorithm for wheeled robot and show the result */
    int GoWheeled();

    /*! \brief Initiates A* algorithm for wheeled robot and show the result */
    int GoTracked();

    /*! \brief Plot maze with two paths found */
    void PlotMaze();

    /*! \brief Helper function to assign target locations and robot locations */
    void AssignLocations(std::array<Location *, 4> &, const int &, const int &, const int &);

private:
    /*! \brief Creates object wheeled for Location class */
    Location wheeled_;

    /*! \brief Creates object tracked for Location class */
    Location tracked_;

    /*! \brief Creates object plate for Location class */
    Location plate_;

    /*! \brief Creates object bottle for Location class */
    Location bottle_;

    /* Initialize a temporary maze*/
    Maze temp_maze_;

    /* Create a copy of Maze class for wheeled robot*/
    Maze wheeled_maze_;

    /* Create a copy of Maze class for tracked robot*/
    Maze tracked_maze_;

    /* Character literal for plate*/
    char wheeled_target_ = 'p';

    /* Character literal for bottle*/
    char tracked_target_ = 'b';

    /* Shared pointer for polymorphism of WheeledRobot*/
    std::shared_ptr<MobileRobot> wheeled_robot_in_maze_ = std::make_shared<WheeledRobot>();

    /* Shared pointer for polymorphism of TrackedRobot*/
    std::shared_ptr<MobileRobot> tracked_robot_in_maze_ = std::make_shared<TrackedRobot>();
};

#endif // ENPM809Y_PROJECT_5_TARGET_H
