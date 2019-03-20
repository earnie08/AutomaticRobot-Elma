#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include "mapinfo.h"

using namespace std;

MapInfo::MapInfo(){
    _mapSize = 11*2+1;
    createMap(_mapSize);
    setRobotLocation(0,0);
    setChargeStation(5, 5);
}

MapInfo::MapInfo(int size, vector<int> chargeStation, vector<int> robotPosition){
    _mapSize = size*2+1;
    createMap(_mapSize);
    setRobotLocation(robotPosition[0], robotPosition[1]);
    setChargeStation(chargeStation[0], chargeStation[1]);
}

void MapInfo::setChargeStation(int x, int y){
    if(x > 0 && y > 0 && x*2-1 < _mapSize && y*2-1 < _mapSize){
        _map[x*2+1][y*2+1] = 'C';
        _pos_chargeSation = make_pair(x,y);
    }
    else{
        if((_mapSize-1)%2 == 0){
            _map[_mapSize/2-1][_mapSize/2-1] = 'C';
            _pos_chargeSation = make_pair((_mapSize/2-1)/2, (_mapSize/2-1)/2);
        }
        else {
            _map[_mapSize/2][_mapSize/2] = 'C';
            _pos_chargeSation = make_pair(_mapSize/4, _mapSize/4);
        }
    }
}

bool MapInfo::setRobotLocation(int x, int y){
    if(setPosition(x,y,'x')){
        _pos_robot = make_pair(x,y);
        return true;
    }
    else return false;
}

bool MapInfo::setIntruderLocation(int x, int y){
    if(setPosition(x,y,'I')){
        _pos_intruder = make_pair(x,y);
        return true;    
    }
    else return false;
}

bool MapInfo::setPosition(int x, int y, char symbol){
    int map_x = x*2+1;
    int map_y = y*2+1;

    if(map_x < 0 || map_x >= _mapSize || map_y >= _mapSize || map_y < 0 || _map[x*2+1][y*2+1] != ' ' )
        return false;
    else {
        _map[x*2+1][y*2+1] = symbol;
        return true;    
    }
}

void MapInfo::cleanSymbol(int x, int y){
    _map[x*2+1][y*2+1] = ' ';
}

void MapInfo::createMap(int size){
    _map.resize(size);
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
        if(i%2==0)
            _map[i].push_back('-');
        else
            if(j%2==0)
            _map[i].push_back('|');
            else _map[i].push_back(' ');
        }
    }
}

void MapInfo::cleanMap(){
    _map = vector<vector<char>>();
    createMap(_mapSize);
    setChargeStation(_pos_chargeSation.first, _pos_chargeSation.second);
}

void MapInfo::printMap(){
    for(int i=0; i<_mapSize; i++){
        for(char s : _map[i])
            cout << s;
        cout << "\n";
    }
}




