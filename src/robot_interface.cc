#include <unistd.h>
#include "robot.h"

using namespace robot;

RobotInterface::RobotInterface(Robot& robot, MapInfo& mp, vector<string> customize) : Process("user input"), _robot(robot), _mapinfo(mp), _customize(customize) {
    initscr();   // Start ncurses
    timeout(1);  // Timeout for waiting for user input
    noecho();    // Do not echo user input to the screen
    curs_set(0); // Do not show the cursor
};

void RobotInterface::update() {
    int c = getch();

    switch ( c ) {            
        case 's':
            emit(Event("start/stop"));
            break;
        case 'q':
            std::cout << "halting\n";
            halt();
            break;
    }
    clear();
    showIntro();
    showUI();
}

void RobotInterface::showIntro(){
    mvprintw(0,70, "Security Robot - Elma");
    mvprintw(1,10, "Introduction");
    mvprintw(2,10, "R: robot position");
    mvprintw(3,10, "C: charge station");
    mvprintw(4,10, "I: intruder position");

    if(_customize.size() > 0){
        for(int i = 0; i < _customize.size(); i++){
            mvprintw(i+8,10, "%s", _customize[i].c_str());
        }
    }
}

void RobotInterface::showUI(){
    vector<vector<char>> mp = _mapinfo.getMap();
    for(int i = 0; i < mp.size(); i++){
        for(int j = 0; j < mp[0].size(); j++)
            mvprintw(i+1,70+j, "%c", mp[i][j]);
    }

    for(int i = 0; i< _robot.getStatus().size(); i++ ){
        mvprintw(i+1+mp.size()/2,10, "%s", _robot.getStatus()[i].c_str());
    }

    mvprintw(mp.size()-1,10, "start/stop(s), quit(q)");
}