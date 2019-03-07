#include <iostream>
#include <stdexcept>
#include <vector>
#include "mapinfo.h"

using namespace std;

MapInfo::MapInfo(int size){
    if(size < 10){
        cout << "Reset the map size to minimum size 10x10.\n";
        size = 10;
    }
    cout << "Creating map...\n"; 
    map_size = size*2+1;
    createMap(map_size);

    if(size%2 == 0)
        setChargeStation(size-1);
    else setChargeStation(size);

    setRoute(0,0);
    cout << "Original Map...\n";
    printMap();
    cout << "\n\n\n\n";
}

void MapInfo::printMap(){
    for(int i=0; i<map_size; i++){
        for(char s : mp[i])
        cout << s;
        cout << "\n";
    }
}

bool MapInfo::setRoute(int x, int y){
    int pos_x = x*2+1;
    int pos_y = y*2+1;
    if( pos_x < 0 || pos_x >= map_size || pos_y >= map_size || pos_y < 0)
        return false;
    else {
        mp[x*2+1][y*2+1] = 'x';
        current_position = make_pair(x,y);
        return true;    
    }
}

void MapInfo::cleanRoute(int x, int y){
    mp[x*2+1][y*2+1] = ' ';
}

void MapInfo::createMap(int size){
    mp.resize(size);
    mp[0].resize(size);
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
        if(i%2==0)
            mp[i].push_back('-');
        else
            if(j%2==0)
            mp[i].push_back('|');
            else mp[i].push_back(' ');
        }
    }
}

void MapInfo::setChargeStation(int center){
    mp[center][center] = 'C';
    cout << "Charge Station: " << center/2 << "\n";
    pos_chargeSation = make_pair(center/2, center/2);
}


