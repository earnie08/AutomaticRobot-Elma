#ifndef _MAPINFO_H
#define _MAPINFO_H

#include <iostream>
#include <vector>
using namespace std;

class MapInfo {
    public:
    //! Default construct
    MapInfo();

    //! Contruct with map size
    //! \param size The map size
    //! \parram chargeStation The position of charge station
    //! \parram robotPosition The position of robot
    MapInfo(int size, vector<int> chargeStation, vector<int> robotPosition);

    //! Set the charge station at the center of map as 'C'
    //! \param x The x-axis position of charge station in map
    //! \param x The y-axis position of charge station in map
    void setChargeStation(int x, int y);

    //! Set the robot location in map as 'x'
    //! \param x The x-axis position of robot in map
    //! \param y The y-axis position of robot in map
    bool setRobotLocation(int x, int y);

    //! Set the intruder location in map as 'I'
    //! \param x The x-axis position of robot in map
    //! \param y The y-axis position of robot in map
    bool setIntruderLocation(int x, int y);

    //! Add symbol in map.
    //! \param x The x-axis position of the symbol in map
    //! \param y The y-axis position of the symbol in map 
    //! \param symbol The symbol to draw on map
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
    //! \return robot position [x,y]
    inline pair<int, int> getRobotPosition() { return _pos_robot; }

    //! Return current position in map.
    //! \return intruder position [x,y]
    inline pair<int, int> getIntruderPosition() { return _pos_intruder; }

    //! Return charge station position in map.
    //! \return charge station position [x,y]
    inline pair<int, int> getChargeStation() { return _pos_chargeSation; }

    //! Return map
    //! \return 2D map
    inline vector<vector<char>> getMap() { return _map; }
    
    //! Return map size
    //! \return The map size
    inline int getMapSize() { return _mapSize; }
    
    private:
    int _mapSize;
    pair<int, int> _pos_chargeSation;
    pair<int, int> _pos_robot;
    pair<int, int> _pos_intruder = make_pair(-99,-99);
    vector<vector<char>> _map;
};

#endif

