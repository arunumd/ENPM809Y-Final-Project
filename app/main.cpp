#include <iostream>
#include <stack>
#include "../include/Maze.h"
#include "../include/Target.h"
#include "../include/DownState.h"
#include "../include/UpState.h"
#include "../include/LeftState.h"
#include "../include/RightState.h"
#include "../include/RobotState.h"
#include "../include/MobileRobot.h"
#include "../include/WheeledRobot.h"
#include "../include/TrackedRobot.h"

int main() {
    int is_both_blocked = 1;
    while(is_both_blocked){
        Target missions;
        missions.SetPositions();
        missions.AssignTasks();
        int is_wheeled_blocked = missions.GoWheeled();
        int is_tracked_blocked = missions.GoTracked();
        if(is_wheeled_blocked == 0 or is_tracked_blocked == 0){
            is_both_blocked = 0;
            missions.PlotMaze();
        }
        else {
            std::cout<<"\n\nNo path for both robots, please try again.\n\n";
        }
    }
    std::cout<<"\nAt least one path has been found! \nProgram finished.\n\n";
    return 0;
}
