#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
        m_board = new Board;
    startCountdownTimer(99);
        string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt";
        Board::LoadResult result = m_board->loadBoard(board_file);
        if (result == Board::load_fail_file_not_found)
            cerr << "Could not find board01.txt data file\n";
        else if (result == Board::load_fail_bad_format)
            cerr << "Your board was improperly formatted\n";
        else if (result == Board::load_success)
            cerr << "Successfully loaded board\n";
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT; y++)
        {
            Board::GridEntry curr = m_board->getContentsOf(x, y);
            if (curr == Board::empty)
                continue;
            if (curr == Board::player)
            {
            peach = new PlayerAvatar(IID_PEACH, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, 1, this);
                m_actors.push_back(peach);
            Actor* blueCoinSquare = new CoinSquare(IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, true, this);
                m_actors.push_back(blueCoinSquare);
            yoshi = new PlayerAvatar(IID_YOSHI, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, 2, this);
               m_actors.push_back(yoshi);
            }
            if (curr == Board::blue_coin_square)
            {
                Actor* blueCoinSquare = new CoinSquare(IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, true, this);
                m_actors.push_back(blueCoinSquare);
            }
            if (curr == Board::red_coin_square)
            {
                Actor* redCoinSquare = new CoinSquare(IID_RED_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, false, this);
                 m_actors.push_back(redCoinSquare);
            }
            if (curr == Board::bowser)
            {
                Actor* Bowser = new class Bowser(IID_BOWSER, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                 m_actors.push_back(Bowser);
                Actor* blueCoinSquare = new CoinSquare(IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, true, this);
                m_actors.push_back(blueCoinSquare);
            }
            if (curr == Board::boo)
            {
                Actor* Boo = new class Boo(IID_BOO, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                 m_actors.push_back(Boo);
                Actor* blueCoinSquare = new CoinSquare(IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, true, this);
                m_actors.push_back(blueCoinSquare);
            }
            if (curr == Board::star_square)
            {
                Actor* StarSquare = new class StarSquare(IID_STAR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                 m_actors.push_back(StarSquare);
            }
            if (curr == Board::bank_square)
            {
                Actor* BankSquare = new class BankSquare(IID_BANK_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                 m_actors.push_back(BankSquare);
            }
            if (curr == Board::event_square)
            {
                Actor* EventSquare = new class EventSquare(IID_EVENT_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                 m_actors.push_back(EventSquare);
            }
            if (curr == Board::right_dir_square)
            {
                Actor* R_DirectionalSquare = new class DirectionalSquare(IID_DIR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, Actor::right, this);
                 m_actors.push_back(R_DirectionalSquare);
            }
            if (curr == Board::left_dir_square)
            {
                Actor* L_DirectionalSquare = new class DirectionalSquare(IID_DIR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, Actor::left, this);
                 m_actors.push_back(L_DirectionalSquare);
            }
            if (curr == Board::up_dir_square)
            {
                Actor* U_DirectionalSquare = new class DirectionalSquare(IID_DIR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, Actor::up, this);
                 m_actors.push_back(U_DirectionalSquare);
            }
            if (curr == Board::down_dir_square)
            {
                Actor* D_DirectionalSquare = new class DirectionalSquare(IID_DIR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, Actor::down, this);
                 m_actors.push_back(D_DirectionalSquare);
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    std::ostringstream game_stat_text;
    int bank = 20;
    game_stat_text << "P1 Roll: " << dynamic_cast<PlayerAvatar*>(peach)->getDieRoll() << " Stars: " << dynamic_cast<PlayerAvatar*>(peach)->getStars() << " $$: " << dynamic_cast<PlayerAvatar*>(peach)->getCoins() << " VOR"
    << " | Time: " << timeRemaining() << " | Bank: " << bank << " | P2 Roll: "
    << dynamic_cast<PlayerAvatar*>(yoshi)->getDieRoll() << " Stars: " << dynamic_cast<PlayerAvatar*>(yoshi)->getStars() << " $$: " << dynamic_cast<PlayerAvatar*>(yoshi)->getCoins() << " VOR";
    string s = game_stat_text.str();
    setGameStatText(s);
    if(timeRemaining() <= 0){
        if(dynamic_cast<PlayerAvatar*>(peach)->getStars() > dynamic_cast<PlayerAvatar*>(yoshi)->getStars()){
            setFinalScore(dynamic_cast<PlayerAvatar*>(peach)->getStars(), dynamic_cast<PlayerAvatar*>(peach)->getCoins());
            return GWSTATUS_PEACH_WON;
        }
        if(dynamic_cast<PlayerAvatar*>(yoshi)->getStars() > dynamic_cast<PlayerAvatar*>(peach)->getStars()){
            setFinalScore(dynamic_cast<PlayerAvatar*>(yoshi)->getStars(), dynamic_cast<PlayerAvatar*>(yoshi)->getCoins());
            return GWSTATUS_YOSHI_WON;
        }
        else if(dynamic_cast<PlayerAvatar*>(yoshi)->getCoins() > dynamic_cast<PlayerAvatar*>(peach)->getCoins()){
            setFinalScore(dynamic_cast<PlayerAvatar*>(yoshi)->getStars(), dynamic_cast<PlayerAvatar*>(yoshi)->getCoins());
            return GWSTATUS_YOSHI_WON;;
        }
        else if(dynamic_cast<PlayerAvatar*>(peach)->getCoins() > dynamic_cast<PlayerAvatar*>(yoshi)->getCoins()){
            setFinalScore(dynamic_cast<PlayerAvatar*>(peach)->getStars(), dynamic_cast<PlayerAvatar*>(peach)->getCoins());
            return GWSTATUS_PEACH_WON;;
        }
        else if(dynamic_cast<PlayerAvatar*>(peach)->getCoins() == dynamic_cast<PlayerAvatar*>(yoshi)->getCoins() && dynamic_cast<PlayerAvatar*>(peach)->getStars() == dynamic_cast<PlayerAvatar*>(yoshi)->getStars()){
            int rand = randInt(1, 2);
            if(rand == 1){
                setFinalScore(dynamic_cast<PlayerAvatar*>(peach)->getStars(), dynamic_cast<PlayerAvatar*>(peach)->getCoins());
                return GWSTATUS_PEACH_WON;
            }
            else if(rand == 2){
                setFinalScore(dynamic_cast<PlayerAvatar*>(yoshi)->getStars(), dynamic_cast<PlayerAvatar*>(yoshi)->getCoins());
                return GWSTATUS_YOSHI_WON;
            }
        }
    }
    else{
        if(m_actors.size() == 0)
            return GWSTATUS_NOT_IMPLEMENTED;
        vector<Actor*>::iterator x;
        for(x = m_actors.begin(); x != m_actors.end(); x++){
            if((*x)->isAlive()){
                (*x)->doSomething();
            }
            if (!(*x)->isAlive()) {
                delete *x;
                x = m_actors.erase(x) - 1;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    if(m_actors.size() == 0)
        return;

    vector<Actor*>::iterator x;
    for(x = m_actors.begin(); x != m_actors.end(); x++){
        delete *x;
    }
    m_actors.clear();
}
bool StudentWorld::checkMove(int x, int y, int dir){
    if(x%16 > 0 && dir == Actor::left){
        if (m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::blue_coin_square || m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::red_coin_square || m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::left_dir_square || m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::right_dir_square || m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::up_dir_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::down_dir_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::event_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::bank_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::star_square || m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::bowser || m_board->getContentsOf(x/SPRITE_WIDTH + 1, y/SPRITE_HEIGHT) == Board::boo){
            return true;
        }
        else{
            return false;
        }
    }
    else if(y%16 > 0 && dir == Actor::down){
        if (m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::blue_coin_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::red_coin_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::left_dir_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::right_dir_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::up_dir_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::down_dir_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::event_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::bank_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT + 1) == Board::star_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT +1) == Board::bowser || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT +1) == Board::boo){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if (m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::blue_coin_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::red_coin_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::left_dir_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::right_dir_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::up_dir_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::down_dir_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::event_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::bank_square ||
            m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::star_square || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::bowser || m_board->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::boo){
            return true;
        }
        else{
            return false;
        }
    }
}
vector<Actor*> StudentWorld::getActorsAt(int x, int y) const
{
    vector<Actor*> actors;
    
    // iterate through all actors and add any that are at (x, y) to the vector
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            actors.push_back(m_actors[i]);
        }
    }
    
    return actors;
}
bool StudentWorld::isBlueCoinSquare(int x, int y) const {
    vector<Actor*> actors = getActorsAt(x, y);
    for (Actor* actor : actors) {
        CoinSquare* coinSquare = dynamic_cast<CoinSquare*>(actor);
        if (coinSquare != nullptr && coinSquare->isPositive()) {
            return true;
        }
    }
    return false;
}
void StudentWorld::removeActor(int x, int y, Actor* a) {
    for (auto it = m_actors.begin(); it != m_actors.end(); it++) {
        if ((*it)->getX() == x && (*it)->getY() == y) {
            delete *it;
            if(*it == a){
                m_actors.erase(it);
                break;
            }
        }
    }
}

void StudentWorld::addActor(Actor* actor) {
    m_actors.push_back(actor);
}

void StudentWorld::addDroppingSquare(int x, int y) {
    DroppingSquare* newDroppingSquare = new DroppingSquare(IID_DROPPING_SQUARE, x, y, this);
    addActor(newDroppingSquare);
}
void StudentWorld::addVortex(Actor* a) {
   int x = a->getX();
    int y = a->getY();
    Vortex* newVortex = new Vortex(IID_VORTEX, x, y, this);
    addActor(newVortex);
}

PlayerAvatar* StudentWorld::getOverlappingPlayer(const Actor* actor) const {
    // iterate over all actors in the same location as the provided actor
    for (Actor* a : m_actors) {
        if (a != actor && a->isAlive() && a->getX() == actor->getX() && a->getY() == actor->getY()) {
            // check if the actor is a PlayerAvatar
            PlayerAvatar* player = dynamic_cast<PlayerAvatar*>(a);
            if (player != nullptr) {
                // check if the player has just landed on the provided actor
                if (player->getState() == PlayerAvatar::WALKING) {
                   // cerr << "overlapping" << endl;
                    player->setState(0);
                    return player; // return the player
                }
            }
        }
    }
    // no player found
    return nullptr;
}
Actor* StudentWorld::getOverlappingBowserSquare(const Actor* actor) const {
    // iterate over all actors in the same location as the provided actor
    for (Actor* a : m_actors) {
        if (a != actor && a->isAlive() && a->getX() == actor->getX() && a->getY() == actor->getY()) {
            Actor* square = a;
            if (square != nullptr) {
                    return square; // return the player
                }
            }
        }
    // no player found
    return nullptr;
}

PlayerAvatar* StudentWorld::getPlayer(int playerID) const {
    if (playerID == 1) {
        return dynamic_cast<PlayerAvatar*>(peach);
    } else if (playerID == 2) {
        return dynamic_cast<PlayerAvatar*>(yoshi);
    } else {
        return nullptr;
    }
}
PlayerAvatar* StudentWorld::getOtherPlayer(PlayerAvatar* player) {
    if (player == nullptr) {
        return nullptr;
    }
   if(player->getPlayer() == 1)
       return getPlayer(2);
   else{
       return getPlayer(1);
   }
}
