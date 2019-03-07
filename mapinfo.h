#ifndef _MAPINFO_H
#define _MAPINFO_H

#include <iostream>
using namespace std;

class MapInfo {
    public:
    //! Default construct
    MapInfo() {}

    //! Contruct with map size
    MapInfo(int size);

    //! Set the ruote path.
    //! \param x The x-axis position of robot in map
    //! \param y The y-axis position of robot in map 
    bool setRoute(int x, int y);

    //! Clean previous route =
    //! \param x The x-axis position of robot in map
    //! \param y The y-axis position of robot in map 
    void cleanRoute(int x, int y);

    //! Set the charge station at the center of map as 'C'
    //! \param center The position of charge station
    void setChargeStation(int center);

    //! Print 2D array map.
    void printMap();

    //! Create a 2D array map.
    //! \param size The n*n map size
    void createMap(int size);

    //! Return current position in map.
    inline pair<int, int> getPosition() { return current_position; }

    //! Return charge station position in map.
    inline pair<int, int> getChargeStation() { return pos_chargeSation; }

    private:
    int map_size;
    pair<int, int> pos_chargeSation;
    pair<int, int> current_position;
    vector<vector<char>> mp;
};

#endif

