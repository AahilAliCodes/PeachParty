#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class StudentWorld;

class Actor : public GraphObject {
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world)
            : GraphObject(imageID, startX, startY, startDirection, depth, size)
    {
        m_isAlive = true;
        m_world = world;
    }
    virtual void doSomething() = 0;
    bool isAlive()
    {
        return m_isAlive;
    }
    void setDead()
    {
        m_isAlive = false;
    }
    void updateDir();
private:
    bool m_isAlive;
    StudentWorld* m_world;
};

class PlayerAvatar : public Actor {
public:
    const static int WALKING = 1;
    const static int WAITING = 0;
    //const int distance = (SPRITE_HEIGHT/2) +2;
    PlayerAvatar(int ID, int startX, int startY, int playernum, StudentWorld* world)
            : Actor(ID, startX, startY, 0, 0, 1.0, world)
    {
        m_PlayerNum = playernum;
        m_numCoins = 0;
        m_ticksToMove = 0;
//        m_state = 0;
        m_numStars = 0;
        waiting = true;
        m_hasVortex = false;
        walking = false;
        m_dir_walking = right;
        m_bowserActive = false;
        m_booActive = false;
        die_roll = 0;
        m_blocksToMove = 0;
//        m_world = world;
    }
    int getWalkDirection() const
    {
        return m_dir_walking;
    }
    void setWalkDirection(int dir)
    {
        m_dir_walking = dir;
    }
    int getPlayer() const{
        return m_PlayerNum;
    }
    int getTicksLeft() const{
        return m_ticksToMove;
    }
    void setTicksLeft(int ticks){
        m_ticksToMove = ticks;
    }
    bool hasVortex(){
        return m_hasVortex;
    }
    void setVortex(bool t){
        m_hasVortex = t;
    }
    int getState() const{
        if(walking)
            return 1;
        else
            return 0;
    }
    void setState(int state)
    {
        if(state == 1){
            walking = true;}
        else {
            waiting = true;
        }
    }
    void teleport();
    bool isBowserActivated(){
        return m_bowserActive;
    }
    bool isBooActivated(){
        return m_booActive;
    }
    void setBowserActivated(){
        m_bowserActive = true;
    }
    void setBooActive(){
        m_booActive = true;
    }
    void updateDir();
    bool isFork();
    virtual void doSomething();
    //int findValidDirection(int x, int y, int dir);
    int getCoins() {return m_numCoins; }
    int getDieRoll(){
        return die_roll;
    }
    void setCoins(int coins) { m_numCoins += coins; }
    int getStars() {return m_numStars; }
    void setStars(int stars) { m_numStars = m_numStars + stars; }
    
    // implementation of the doSomething() method for PlayerAvatar class

private:
    int m_PlayerNum;
    int m_numCoins;
    int m_numStars;
    int m_ticksToMove;
//    int m_state;
    int m_dir_walking;
    bool m_bowserActive;
    bool m_booActive;
    int die_roll;
    int m_blocksToMove;
    bool waiting;
    bool walking;
    bool m_hasVortex;
//    StudentWorld* m_world;
};

class CoinSquare : public Actor {
    public:
    CoinSquare(int imageID, int startX, int startY, bool positiveCoins, StudentWorld* world)
    : Actor(imageID, startX, startY, 0, 1, 1.0, world) {
        m_positiveCoins = positiveCoins;
        m_isAlive = true;
        m_numTicks = 0;
        if(m_positiveCoins == true)
            imageID = IID_BLUE_COIN_SQUARE;
        else {
            imageID = IID_RED_COIN_SQUARE;
            m_ticksOnSquare = 0;
            m_newPlayer = nullptr;
        }
    }
    bool isPositive(){return m_positiveCoins;}
    bool getAlive(){ return m_isAlive; }
    virtual void doSomething();
    private:
        bool m_isAlive;
        bool m_positiveCoins;
        int m_numCoins;
        int m_numTicks;
    int m_ticksOnSquare;
    PlayerAvatar* m_newPlayer;
  //      StudentWorld* m_world;
    };
class Bowser : public Actor {
    public:
    const int WALKING = 1;
    const int PAUSED = 0;
    Bowser(int ID, int startX, int startY, StudentWorld* world)
            : Actor(ID, startX, startY, 0, 0, 1.0, world)
    {
                m_dir_walking = right;
                m_distance = 0;
                m_pauseCounter = 180;
                m_ticksToMove = 0;
                paused = true;
                walking = false;
            }
    int getWalkDirection()
    {
        return m_dir_walking;
    }
    void setWalkDirection(int dir)
    {
        m_dir_walking = dir;
    }
    int getDistance(){
        return m_distance;
    }
    int getState(){
        if(walking)
            return 1;
        else
            return 0;
    }
    void setState(int state)
    {
        if(state == 1){
            walking = true;}
        else {
            paused = true;
        }
    }
    bool isImpactedByVortex(){ return true;}
    void updateDir();
    int getTicksToMove(){
        return m_ticksToMove;
    }
    virtual void doSomething();
    private:
        int m_dir_walking;
        int m_distance;
        int m_pauseCounter;
        int m_ticksToMove;
    bool paused;
    bool walking;
};
class Boo : public Actor {
    public:
    const int WALKING = 1;
    const int PAUSED = 0;
    Boo(int ID, int startX, int startY, StudentWorld* world)
            : Actor(ID, startX, startY, 0, 0, 1.0, world)
    {
        paused = true;
        walking = false;
                m_dir_walking = right;
                m_distance = 0;
                m_pauseCounter = 180;
        m_ticksToMove = 0;
    }
    int getWalkDirection()
    {
        return m_dir_walking;
    }
    void setWalkDirection(int dir)
    {
        m_dir_walking = dir;
    }
    int getDistance(){
        return m_distance;
    }
    bool isImpactedByVortex(){ return true;}
    int getState(){
        if(walking)
            return 1;
        else
            return 0;
    }
    void setState(int state)
    {
        if(state == 1){
            walking = true;}
        else {
            paused = true;
        }
    }
    int getTicksToMove(){
        return m_ticksToMove;
    }
    void updateDir();
    virtual void doSomething();
    private:
        int m_dir_walking;
        int m_distance;
        int m_pauseCounter;
    bool paused;
    bool walking;
        int m_ticksToMove;
};
class StarSquare : public Actor {
    public:
    StarSquare(int imageID, int startX, int startY, StudentWorld* world)
    : Actor(imageID, startX, startY, 0, 1, 1.0, world)
    {
        m_newPlayer = nullptr;
        m_ticksOnSquare = 0;
    }
    virtual void doSomething();
    private:
    int m_ticksOnSquare;
    PlayerAvatar* m_newPlayer;
};
class DirectionalSquare : public Actor {
    public:
    DirectionalSquare(int imageID, int startX, int startY, int dir, StudentWorld* world)
    : Actor(imageID, startX, startY, 0, 1, 1.0, world)
    {
        m_forceDir = dir;
        setDirection(m_forceDir);
    }
    virtual void doSomething();
    private:
        int m_forceDir;
};
class BankSquare : public Actor {
    public:
    BankSquare(int imageID, int startX, int startY, StudentWorld* world)
    : Actor(imageID, startX, startY, 0, 1, 1.0, world)
    {
        m_bankBalance = 0;
        m_ticksOnSquare = 0;
        m_newPlayer = nullptr;
    }
    
    virtual void doSomething();
    int getBankBalance() {return m_bankBalance; }
    void setBankBalance(int bal) { m_bankBalance = m_bankBalance + bal; }
    private:
    int m_ticksOnSquare;
    PlayerAvatar* m_newPlayer;
    int m_bankBalance;
};
class EventSquare : public Actor {
    public:
    EventSquare(int imageID, int startX, int startY, StudentWorld* world)
    : Actor(imageID, startX, startY, 0, 1, 1.0, world)
    {
        m_ticksOnSquare = 0;
        m_newPlayer = nullptr;
    }
    virtual void doSomething();
    private:
    int m_ticksOnSquare;
    PlayerAvatar* m_newPlayer;
};
class DroppingSquare : public Actor {
    public: //A DroppingSquare object must have its (x, y) location specified for it by Bowser when they create the new Vortex.
    DroppingSquare(int imageID, int startX, int startY, StudentWorld* world)
    : Actor(imageID, startX, startY, 0, 1, 1.0, world)
    {
        m_ticksOnSquare = 0;
        m_newPlayer = nullptr;
    }
    virtual void doSomething();
    private:
    int m_ticksOnSquare;
    PlayerAvatar* m_newPlayer;
};
class Vortex : public Actor {
    public: //A Vortex object must have its (x, y) location specified for it by Peach or Yoshi when they create the new Vortex.
    Vortex(int imageID, int startX, int startY, StudentWorld* world)
    : Actor(imageID, startX, startY, 0, 1, 1.0, world)
    {
        m_isActive = true;
    }
    virtual void doSomething();
    private:
        bool m_isActive;
};


#endif // ACTOR_H_
