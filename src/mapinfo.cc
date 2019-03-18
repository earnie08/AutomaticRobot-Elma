#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include "mapinfo.h"

using namespace std;

MapInfo::MapInfo(){
    //cout << "Creating map...\n"; 
    map_size = 11*2+1;
    createMap(map_size);
    setRobotLocation(0,0);
    setChargeStation(5, 5);
}

MapInfo::MapInfo(int size, vector<int> chargeStation){
    if(size < 10){
        //cout << "Reset the map size to minimum size 10x10.\n";
        size = 10;
    }
    //cout << "Creating map...\n"; 
    map_size = size*2+1;
    createMap(map_size);
    setChargeStation(chargeStation[0], chargeStation[1]);
}

void MapInfo::setChargeStation(int x, int y){
    if(x > 0 && y > 0 && x*2-1 < map_size && y*2-1 < map_size){
        mp[x*2+1][y*2+1] = 'C';
        pos_chargeSation = make_pair(x,y);
        //cout << "Charge Station: " << pos_chargeSation.first << "," << pos_chargeSation.second << "\n";
    }
    else{
        if((map_size-1)%2 == 0){
            mp[map_size/2-1][map_size/2-1] = 'C';
            pos_chargeSation = make_pair((map_size/2-1)/2, (map_size/2-1)/2);
        }
        else {
            mp[map_size/2][map_size/2] = 'C';
            pos_chargeSation = make_pair(map_size/4, map_size/4);
        }
        //cout << "Charge Station is not in the map.\nReset Charge Station: " << pos_chargeSation.first << "," << pos_chargeSation.second << "\n";
    }
}

bool MapInfo::setRobotLocation(int x, int y){
    if(setPosition(x,y,'x')){
        pos_robot = make_pair(x,y);
        return true;
    }
    else return false;
}

bool MapInfo::setIntruderLocation(int x, int y){
    if(setPosition(x,y,'I')){
        pos_intruder = make_pair(x,y);
        return true;    
    }
    else return false;
}

bool MapInfo::setPosition(int x, int y, char symbol){
    int map_x = x*2+1;
    int map_y = y*2+1;

    if(map_x < 0 || map_x >= map_size || map_y >= map_size || map_y < 0 || mp[x*2+1][y*2+1] != ' ' )
        return false;
    else {
        mp[x*2+1][y*2+1] = symbol;
        return true;    
    }
}

void MapInfo::cleanSymbol(int x, int y){
    mp[x*2+1][y*2+1] = ' ';
}

void MapInfo::createMap(int size){
    mp.resize(size);
    //mp[0].resize(size);
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

void MapInfo::cleanMap(){
    mp = vector<vector<char>>();
    createMap(map_size);
    setChargeStation(pos_chargeSation.first, pos_chargeSation.second);
}

void MapInfo::printMap(){
    for(int i=0; i<map_size; i++){
        for(char s : mp[i])
            cout << s;
        cout << "\n";
    }
}




