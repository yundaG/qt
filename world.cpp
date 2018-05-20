#include "world.h"
#include "icon.h"
#include <iostream>
#include <string>
#include <QPainter>
using namespace std;

void World::initWorld(string mapFile){
    //TODO 下面这部分逻辑应该是读入地图文件，生成地图上的对象
    this->Map.load("E:\rpgmap\timg.jpeg");
    //player 5 5
    this->_player.initObj("player");
    this->_player.setPosX(1);
    this->_player.setPosY(2);
    this->judgePlayer.initObj("player");
    this->judgePlayer.setPosX(1);
    this->judgePlayer.setPosY(2);

    RPGObj obj[81];
    for(int i=0;i<5;i++){
        obj[i].initObj("stone");
        obj[i].setPosX(4);
        obj[i].setPosY(i);
    }
    for(int i=5;i<10;i++){
        obj[i].initObj("stone");
        obj[i].setPosX(9);
        obj[i].setPosY(i-5);
    }
    for(int i=10;i<17;i++){
        obj[i].initObj("stone");
        obj[i].setPosX(i-10);
        obj[i].setPosY(10);
    }
    for(int i=17;i<24;i++){
        obj[i].initObj("stone");
        obj[i].setPosX(i-9);
        obj[i].setPosY(10);
    }
    for(int i=24;i<29;i++){
        obj[i].initObj("stone");
        obj[i].setPosX(i-24);
        obj[i].setPosY(7);
    }
    for(int i=29;i<40;i++){
        obj[i].initObj("stone");
        obj[i].setPosX(14);
        obj[i].setPosY(i-29);
    }
    for(int i=40;i<55;i++){
        obj[i].initObj("stone");
        obj[i].setPosX(i-40);
        obj[i].setPosY(0);
    }
    for(int i=55;i<57;i++){
        obj[i].initObj("stone");
        obj[i].setPosX(9);
        obj[i].setPosY(i-47);
    }
    for(int i=57;i<68;i++){
        obj[i].initObj("tree");
        obj[i].setPosX(-1);
        obj[i].setPosY(i-57);
    }

    obj[68].initObj("fruit");
    obj[68].setPosX(7);
    obj[68].setPosY(11);

    obj[69].initObj("bucket");
    obj[69].setPosX(7);
    obj[69].setPosY(12);

    obj[70].initObj("fruit");
    obj[70].setPosX(2);
    obj[70].setPosY(9);

    obj[71].initObj("fruit");
    obj[71].setPosX(7);
    obj[71].setPosY(1);

    obj[72].initObj("fruit");
    obj[72].setPosX(13);
    obj[72].setPosY(1);

    obj[73].initObj("fruit");
    obj[73].setPosX(10);
    obj[73].setPosY(9);

    obj[74].initObj("stone");
    obj[74].setPosX(6);
    obj[74].setPosY(6);

    obj[75].initObj("stone");
    obj[75].setPosX(9);
    obj[75].setPosY(7);

    obj[76].initObj("stone");
    obj[76].setPosX(2);
    obj[76].setPosY(4);

    obj[77].initObj("stone");
    obj[77].setPosX(12);
    obj[77].setPosY(5);

    obj[78].initObj("stone");
    obj[78].setPosX(6);
    obj[78].setPosY(11);

    obj[79].initObj("stone");
    obj[79].setPosX(8);
    obj[79].setPosY(11);

    for(int i=0;i<80;i++){
        this->_objs.push_back(obj[i]);
    }
}


void World::show(QPainter * painter){
    painter->drawImage(0,0,this->Map);
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        (*it).show(painter);
    }
    this->_player.show(painter);
}

void World::handlePlayerMove(int direction, int steps){

    int covercount=0,eatcount=0;
    this->judgePlayer.move(direction, steps);
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        if(!it->canCover()){
            if(judgePlayer.getPosX()==it->getPosX() && judgePlayer.getPosY()==it->getPosY()-1)
                covercount++;
        }
        if(it->canEat()){
            if(judgePlayer.getPosX()==it->getPosX() && judgePlayer.getPosY()==it->getPosY()-1){
                it->setPosX(-1);
                it->setPosY(-1);
                eatcount++;
             }
          }
    }
    if(covercount)
        this->_player.move(direction,0);
    else
        this->_player.move(direction,steps);
    if(eatcount)
        this->_player.move(direction,steps);
    this->judgePlayer.setPosX(this->_player.getPosX());
    this->judgePlayer.setPosY(this->_player.getPosY());
}

