#ifndef _MAPINFO_H
#define _MAPINFO_H

#include <iostream>
#include <vector>
using namespace std;

class MapInfo {
    public:
    //! Default construct
    MapInfo() {}

    //! Contruct with map size
    MapInfo(int size);

    //! Set the charge station at the center of map as 'C'
    void setChargeStation();

    //! Set the robot location in map
    //! \param x The x-axis position of robot in map
    //! \param y The y-axis position of robot in map
    bool setRobotLocation(int x, int y);

    //! Set the intruder location in map
    //! \param x The x-axis position of robot in map
    //! \param y The y-axis position of robot in map
    bool setIntruderLocation(int x, int y);

    //! Add symbol in map.
    //! \param x The x-axis position of the symbol in map
    //! \param y The y-axis position of the symbol in map 
    bool setPosition(int x, int y, char symbol);

    //! Clean previous route
    //! \param x The x-axis position of robot in map
    //! \param y The y-axis position of robot in map 
    void cleanSymbol(int x, int y);

    //! Create a 2D array map.
    //! \param size The n*n map size
    void createMap(int size);

    //! Clean map to initial map (only have charge station).
    void cleanMap();

    //! Print 2D array map.
    void printMap();

    //! Return current position in map.
    inline pair<int, int> getRobotPosition() { return pos_robot; }

    //! Return current position in map.
    inline pair<int, int> getIntruderPosition() { return pos_intruder; }

    //! Return charge station position in map.
    inline pair<int, int> getChargeStation() { return pos_chargeSation; }

    //! Return map 
    inline vector<vector<char>> getMap() { return mp; }
    
    //! Return map size
    inline int getMapSize() { return map_size; }
    
    private:
    int map_size;
    pair<int, int> pos_chargeSation;
    pair<int, int> pos_robot;
    pair<int, int> pos_intruder = make_pair(-99,-99);
    vector<vector<char>> mp;
};

#endif

