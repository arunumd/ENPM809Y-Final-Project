/*!
 * \file        Target.h
 * \author      Arun Kumar Devarajulu
 * \author      Zuyang Cao
 * \author      Qidi Xu
 * \author      Hongyang Jiang
 * \date        05/07/2019
 * \brief       The file Target.h contains the header declarations for Target
 *              class. The class will be used for implementation of user interface,
 *              visualization etc in Final Project.
 * \license     This project is released under the MIT License.
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
 *\struct Location
 *\brief Define data structure that contain location (cartesian coordinates)
 *for robot and target locations
 * */
struct Location {
    int x = -1;
    int y = -1;
};

/*!
 * \class Target
 * \brief The Target class has composition of all other classes for triggering
 * the whole project. Specifically, it creates two copies of the Maze class, for
 * the two robots (Wheeled and Tracked). It then takes in user input for locations
 * of robots and targets. Later it triggers the A* algorithm from the Maze class to
 * find out the optimal paths (if they exist). If there are zero paths found, then
 * Target class will ask for fresh user inputs for alternate locations
 */
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

    /*! \brief Initialize a temporary maze*/
    Maze temp_maze_;

    /*! \brief Create a copy of Maze class for wheeled robot*/
    Maze wheeled_maze_;

    /*! \brief Create a copy of Maze class for tracked robot*/
    Maze tracked_maze_;

    /*! \brief Character literal for plate*/
    char wheeled_target_ = 'p';

    /*! \brief Character literal for bottle*/
    char tracked_target_ = 'b';

    /*! \brief Shared pointer for polymorphism of WheeledRobot*/
    std::shared_ptr<MobileRobot> wheeled_robot_in_maze_ = std::make_shared<WheeledRobot>();

    /*! \brief Shared pointer for polymorphism of TrackedRobot*/
    std::shared_ptr<MobileRobot> tracked_robot_in_maze_ = std::make_shared<TrackedRobot>();
};

#endif // ENPM809Y_PROJECT_5_TARGET_H
