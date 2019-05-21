/*!
 * \file       Maze.h
 * \author     Arun Kumar Devarajulu
 * \author     Zuyang Cao
 * \author     Qidi Xu
 * \author     Hongyang Jiang
 * \date       04/27/2019
 * \brief      The file Maze.h contains the header declarations for Maze
 *             class. The class will be used for implementation of A-Star
 *             Algorithm in Final Project
 * \license    MIT License
 *             Permission is hereby granted, free of charge, to any person obtaining a copy
 *             of this software and associated documentation files (the "Software"), to deal
 *             in the Software without restriction, including without limitation the rights
 *             to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *             copies of the Software, and to permit persons to whom the Software is
 *             furnished to do so, subject to the following conditions:
 *
 *             The above copyright notice and this permission notice shall be included in all
 *             copies or substantial portions of the Software.
 *
 *             THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *             IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *             FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 *             AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *             LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *             OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *             SOFTWARE.
 */

#ifndef ENPM809Y_PROJECT_5_A_STAR_H
#define ENPM809Y_PROJECT_5_A_STAR_H

#include <iostream>
#include <utility>
#include <array>
#include <map>
#include <stack>
#include <memory>
#include "MobileRobot.h"

/*!
 * \brief  Define data structure that contain information for each nodes
 * such as cost to go, distance to target, current node location and parent
 * node location
 * */
struct ListInfo {
    double cost_g = 0;
    double cost_h = -10;
    double total_cost = -10;
    std::pair<int, int> node{std::make_pair(-100, -100)};
    std::pair<int, int> parent{std::make_pair(-100, -100)};
};

/*!
 * \brief The Maze class contains the search based A* navigation algorithm
 * for solving our path finding problem. The algorithm accepts a start position
 * and goal position and finds a shortest path. The complexity of our algorithm
 * is O(log n) because we use only one for loop to iterate through entries of
 * priority list_. The algorithm finds the shortest path very quick
 */
class Maze {
public:
    /*! \brief  Default constructor  */
    Maze() : grid_{{"######################  ######################",
                           "#        #           #  #                    #",
                           "#  ####  #  #######  #  ##########  #######  #",
                           "#  #     #  #        #        #     #     #  #",
                           "#  ####  #  ################  #  #######  #  #",
                           "#     #  #                 #  #  #        #  #",
                           "#  #  #  #  #############  #  #  #  ####  #  #",
                           "#  #  #  #  #           #  #  #  #  #  #  #  #",
                           "#  #  #  #  #  #######  #  #  #  #  #  #  #  #",
                           "#  #  #  #  #  #     #  #  #  #  #  #     #  #",
                           "#  #  #  #  #  #######  #  #  #  #  #######  #",
                           "#  #  #  #  #  #        #  #  #  #           #",
                           "####  #  #  ##########  #  #  #  #############",
                           "#     #  #              #  #  #              #",
                           "#  #  #  #######  ####  #  #  #  ##########  #",
                           "#  #  #     #     #     #  #  #     #     #  #",
                           "#  #  ####  #############  #  ####  #  #  #  #",
                           "#  #  #                    #     #     #  #  #",
                           "####  #  ######################  ##########  #",
                           "#     #  #                    #              #",
                           "#  ####  #  ################  #############  #",
                           "#  #     #  #              #           #  #  #",
                           "#  #  ####  #  ##########  #  #  ####  #  #  #",
                           "#  #  #  #  #  #  #     #  #  #  #        #  #",
                           "#  #  #  #  #  #  #######  #  #############  #",
                           "#  #     #  #           #  #                 #",
                           "#  #######  #############  ###################",
                           "#           #                 #        #     #",
                           "#  ##########  #############  #######  ####  #",
                           "#              #                             #",
                           "##############################################"}},
             start_{std::make_pair(-1, -1)}, goal_{std::make_pair(-1, -1)} {}

    /*! \brief Default destructor*/
    ~Maze() = default;

    /*!
     * \brief Visualizes the Maze by printing it out to the console
     * */
    void ShowMaze() const;

    /*!
     * \brief Retrieves the char value stored in maze at given coordinate (x,y)
     * \param x - x coordinate of node
     * \param y - y coordinate of node
     * \return stored char value in location (x,y)
     * */
    char GetMazePosition(const int &x, const int &y) const;

    /*!
     * \brief Modifies the char value stored to given char
     * value c in maze at given coordinate (x,y)
     * \param x - x coordinate of node
     * \param y - y coordinate of node
     * \param c - the char value user wish to modified to
     * */
    void ModifyMazePosition(const int &x, const int &y, const char &c);

    /*!
     * \brief Sets the start and goal locations
     * \param start_x - x coordinate of start node
     * \param start_y - y coordinate of start node
     * \param goal_x - x coordinate of goal node
     * \param goal_y - y coordinate of goal node
     * */
    void SetStartGoal(const int &, const int &, const int &, const int &);

    /*!
     * \brief build stack of moving sequence
     * \param robot_in_maze - pointer of robot object, polymorphism takes place
     * inside this function.
     * */
    void BuildStack(const std::shared_ptr<MobileRobot> &robot_in_maze);

    /*!
     * \brief Get next node location given current node location when going up
     * \param node - coordinate of current node
     * \return next node location
     * */
    std::pair<int, int> North(const std::pair<int, int> &node) const;

    /*!
     * \brief Get next node location given current node location when going right
     * \param node - coordinate of current node
     * \return next node location
     * */
    std::pair<int, int> East(const std::pair<int, int> &node) const;

    /*!
     * \brief Get next node location given current node location when going left
     * \param node - coordinate of current node
     * \return next node location
     * */
    std::pair<int, int> West(const std::pair<int, int> &node) const;

    /*!
     * \brief Get next node location given current node location when going down
     * \param node - coordinate of current node
     * \return next node location
     * */
    std::pair<int, int> South(const std::pair<int, int> &node) const;

    /*!
     * \brief When the A* algorithm begins for the first time, there is no possibility
     * that any of the generated nodes (four nodes from North, East, West and South movements)
     * will be present in the closed_list_ or the priority_list_. Hence if the new nodes are
     * valid nodes (they do not fall in obstacle space and they are within the scope of the
     * environment, we just add them to the priority_list_.
     * \param new_node - coordinate of new node
     * \param cost_g - cost to go so far
     * \param ListInfo - information on current node including cost to go, distance
     * to target, current node location and parent node location
     * \param parent_node - coordinate of parent node
     * \return 1 if the move is better and -1 if else
     * */
    const int TakeDecision1(const std::pair<int, int> &new_node, const double &cost_g,
                            ListInfo &info, const std::pair<int, int> &parent_node);

    /*!
     * \brief When the A* algorithm goes beyond the first generation of nodes, there are already
     * some nodes which have been added to the priority_list_ and the closed_list_. Hence, for
     * all new to-be-generated nodes, we have to do a variety of checks which include the following :
     *    - The newly generated node is not present in the closed_list_;
     *    - The newly generated node is not in obstacle space3;
     *    - The newly generated node is not outside the region of the maze;
     *    - The newly generated node is not already present in the priority_list_. If it is
     *    already present, then its cost g, cost h and cost f should be lesser than the currently
     *    generated node. If not, then all its information (cost g, cost h, cost f and parent node)
     *    must be reassigned with the information from the currently generated node
     * \param new_node - coordinate of new node
     * \param cost_g - cost to go so far
     * \param ListInfo - information on current node including cost to go, distance
     * to target, current node location and parent node location
     * \parent_node - coordinate of parent node
     * \return 1 if the move is better and -1 if else
     * */
    const int TakeDecision2(const std::pair<int, int> &new_node, const double &cost_g,
                            ListInfo &info, const std::pair<int, int> &parent_node);

    /*!
     * \brief The Action method triggers the entire A* algorithm. The method initially
     * assumes the start node as the current node and then generates four daughters using the
     * helper functions (North, East, West and South). The generated daughters are checked if
     * they can be valid next states and then pushed to priority_list_ and open_list_. Next,
     * the member with lowest cost f is popped from the priority_list_ and open_list_; added
     * to closed_list_; and again four new daughters are generated. This process repeats
     * cyclically until the algorithm finds a generated node is the goal node or until the
     * priority_list_ becomes empty, whichever occurs first.
     * \param cost_g - cost to go
     * \param cost_h - cost to come
     * \param total_cost - total cost estimation
     * \param node - current node location
     * \param parent - parent node location
     * \return 1 if the path is found and -1 if else
     * */
    int Action();

    /*!
     * \brief Computes the euclidean distance between given current node and goal node
     * \param current_node - coordinate of current node
     * \return the euclidean distance between given current node and goal node
     * */
    const double CalculateDistance(const std::pair<int, int> &current_node) const;

    /*!
     * \brief Checks if given node is not an obstacle
     * \param node - coordinate of node to be checked
     * \return false if the node is a wall, true if else
     * */
    bool IsNotObstacle(const std::pair<int, int> &node) const;

    /*!
     * \brief Checks if given node is within the maze
     * \param node - coordinate of node to be checked
     * \return false if the node is within the maze, true if else
     * */
    bool IsWithinRegion(const std::pair<int, int> &node) const;

    /*!
     * \brief Plots the path yield by the A* algorithm
     * \param path_icon - - or + for tracked or wheeled robots
     * */
    int PlotTrajectory(const char &path_icon);

    /*!
     * \brief Gets the length of the maze.
     * \return length of the maze
     * */
    int get_length() const;

    /*!
     * \brief Gets the width of the maze.
     * \return width of the maze
     * */
    int get_width() const;

private:
    /*! \brief Pre-define width as 31 due to the fact the maze is given */
    const int width_ = 31;

    /*! \brief Pre-define length as 46 due to the fact the maze is given */
    const int length_ = 46;

    /*! \brief Our maze representation*/
    std::array<std::string, 31> grid_;

    /*! \brief Our start and goal nodes*/
    std::pair<int, int> start_, goal_;

    /*! \brief C++ STL data structure to store priority list*/
    std::multimap<double, ListInfo> priority_list_;

    /*! \brief  C++ STL data structure to store open and closed lists*/
    std::map<std::pair<int, int>, ListInfo> open_list_, closed_list_;
};

#endif //ENPM809Y_PROJECT_5_A_STAR_H
