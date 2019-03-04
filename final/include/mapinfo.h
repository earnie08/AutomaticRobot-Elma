#ifndef _MAPINFO_H
#define _MAPINFO_H

#include <iostream>
#include <vector>
#include "elma.h"
using namespace elma;
using namespace std;

class MapInfo : public Process {
    public:
    //! Default construct
    MapInfo() { MapInfo(11); }

    //! Contruct with map size
    MapInfo(int size);

    //! Overwrite process interface
    void init();
    void start(){}
    void update();
    void stop(){}

    //! Set the ruote path.
    //! \param x The x-axis position of robot in map
    //! \param y The y-axis position of robot in map 
    void setRoute(int x, int y);

    //! Print 2D array map.
    void printMap();

    private:
    int map_size;
    pair<int, int> pos_chargeSation;
    vector<vector<string>> mp;

    //! Create a 2D array map.
    //! \param size The n*n map size
    void createMap(int size);

    //! Set the charge station at the center of map as 'C'
    //! \param center The position of charge station
    void setChargeStation(int center);

};

#endif

