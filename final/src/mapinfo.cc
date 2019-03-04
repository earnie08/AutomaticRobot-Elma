#include <iostream>
#include <stdexcept>
#include <vector>
#include "mapinfo.h"

using namespace std;

MapInfo::MapInfo(int size): Process("Map"){
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
}

void MapInfo::init(){
    watch("Print Map", [this](Event& e) {
            printMap();
    });
    cout << "Original Map...\n";
    setRoute(0,0);
    emit(Event("Print Map"));
}

void MapInfo::update(){}

void MapInfo::printMap(){
    for(int i=0; i<map_size; i++){
        for(char s : mp[i])
        cout << s;
        cout << "\n";
    }
}

void MapInfo::setRoute(int x, int y){
    if(x < 0 || x >= map_size || y >= map_size || y < 0)
        throw range_error("Get - Out of range index in array");
    else mp[x*2+1][x*2+1] = 'x';
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
    pos_chargeSation = make_pair(center+1, center+1);
}
