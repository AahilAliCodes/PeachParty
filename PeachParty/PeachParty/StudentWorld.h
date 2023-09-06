#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Board.h"
#include <string>
#include <vector>
#include <map>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  virtual ~StudentWorld();
    void addActor(Actor* actor);
    bool getOverlapObject();
    bool checkMove(int x, int y, int dir);
    std::vector<Actor*> getActorsAt(int x, int y) const;
    PlayerAvatar* getOverlappingPlayer(const Actor* actor) const;
    PlayerAvatar* getPlayer(int playerID) const;
    PlayerAvatar* getOtherPlayer(PlayerAvatar* player);
    bool isBlueCoinSquare(int x, int y) const;
    void removeActor(int x, int y, Actor* a);
    void addDroppingSquare(int x, int y);
    void addVortex(Actor* a);
    Actor* getOverlappingBowserSquare(const Actor* actor) const;
private:
    Board* m_board;
    std::vector<Actor*> m_actors;
    Actor* peach;
    Actor* yoshi;
    
    //have to make vector of Actor objects that size is variable
};

#endif // STUDENTWORLD_H_
