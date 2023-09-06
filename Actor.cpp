#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
using namespace std;

void DroppingSquare::doSomething() {
    // Check if a player has landed on the square
    PlayerAvatar* player = getWorld()->getOverlappingPlayer(this);
    // If a new player has been on the square for one tick, activate the square
    if (player != nullptr) {
        // Pick a random action to perform
        int action = randInt(1, 2);
        switch (action) {
            case 1: // Deduct 10 coins from the player
                player->setCoins(-min(player->getCoins(), 10));
                break;
            case 2: // Deduct one star from the player
                if (player->getStars() > 0) {
                    player->setStars(-1);
                }
                else {
                    player->setCoins(-min(player->getCoins(), 10));
                }
                break;
        }
        
        // Play the sound effect
        getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
    }
}
void Bowser::updateDir(){
    if (getWalkDirection() == right || getWalkDirection() == left) {
        int tempDir = up;
        int newX = getX(), newY = getY(); // what do i inititalize to?
        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
        if (getWorld()->checkMove(newX, newY, up)) {
            setWalkDirection(up);
        }
        tempDir = down;
        newX = getX();
        newY = getY();
        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
        if (getWorld()->checkMove(newX, newY, down)) {
            setWalkDirection(down);
        }
    }
    else if (getWalkDirection() == up || getWalkDirection() == down) {
        int tempDir = right;
        int newX = getX(), newY = getY(); // what do i inititalize to?
        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);// up or down{ // up or down
        if (getWorld()->checkMove(newX, newY, right)) {
            setWalkDirection(right);
        }
        tempDir = left;
        newX = getX();
        newY = getY();
        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
        if (getWorld()->checkMove(newX, newY, left)) {
            setWalkDirection(left);
        }
    }
    // Update the sprite direction based on the walk direction
    if (getWalkDirection() == left) {
    setDirection(180);
    }
    else {
    setDirection(0);
    }
}

void Boo::updateDir(){
    if (getWalkDirection() == right || getWalkDirection() == left) {
        int tempDir = up;
        int newX = getX(), newY = getY(); // what do i inititalize to?
        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
        if (getWorld()->checkMove(newX, newY, up)) {
            setWalkDirection(up);
        }
        tempDir = down;
        newX = getX();
        newY = getY();
        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
        if (getWorld()->checkMove(newX, newY, down)) {
            setWalkDirection(down);
        }
    }
    else if (getWalkDirection() == up || getWalkDirection() == down) {
        int tempDir = right;
        int newX = getX(), newY = getY(); // what do i inititalize to?
        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);// up or down{ // up or down
        if (getWorld()->checkMove(newX, newY, right)) {
            setWalkDirection(right);
        }
        tempDir = left;
        newX = getX();
        newY = getY();
        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
        if (getWorld()->checkMove(newX, newY, left)) {
            setWalkDirection(left);
        }
    }
    // Update the sprite direction based on the walk direction
    if (getWalkDirection() == left) {
    setDirection(180);
    }
    else {
    setDirection(0);
    }
}
void Bowser::doSomething() {
    if (paused) {
        // Check if Bowser is on the same square as a waiting player avatar
        PlayerAvatar* player = getWorld()->getOverlappingPlayer(this);
        if (player != nullptr) {
            // There is a waiting player avatar on the same square
//            if (!player->isBowserActivated()) {
                // Bowser hasn't activated on this player avatar yet
                int chance = rand() % 2;
                if (chance == 0) {
                    // Bowser will activate
                    getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
                    int coins = player->getCoins();
                    int stars = player->getStars();
                    player->setCoins(-coins);
                    player->setStars(-stars);
                    player->setBowserActivated();
                }
            }
//        }
        m_pauseCounter--;
        if (m_pauseCounter <= 0) {
    
            int squares_to_move = randInt(1, 10);
            m_ticksToMove = squares_to_move * 8;
            int x, y;
            getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, x, y);
            if (!getWorld()->checkMove(x, y, getWalkDirection())) {
                // Avatar can't continue moving in current direction, so update the walk direction
                if (getWalkDirection() == right || getWalkDirection() == left) {
                    if (getWorld()->checkMove(x, y, up)) {
                        setWalkDirection(up);
                    }
                    else if (getWorld()->checkMove(x, y, down)) {
                        setWalkDirection(down);
                    }
                }
                else if (getWalkDirection() == up || getWalkDirection() == down) {
                    if (getWorld()->checkMove(x, y, right)) {
                        setWalkDirection(right);
                    }
                    else if (getWorld()->checkMove(x, y, left)) {
                        setWalkDirection(left);
                    }
                }
            }
            setDirection(getWalkDirection() == left ? 180 : 0);
            paused = false;
            walking = true;
        }
    }
    else if (getState() == WALKING) {
        int x, y;
        getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, x, y);
        if (getWorld()->checkMove(x, y, getWalkDirection())) {
            // Move two pixels in the walk direction
            moveAtAngle(getWalkDirection(), 2);
            m_ticksToMove--;
        }
        else {
            updateDir();
        }
            if (m_ticksToMove == 0) {
                paused = true;
                walking = false;
                m_pauseCounter = 180;
                int chance = randInt(1, 4); // generate random number between 1 and 4

                if (chance == 1) {
                    
//                    int x = getX();
//                    int y = getY();
//                    Actor* actor = getWorld()->getOverlappingBowserSquare(this);
//                        getWorld()->removeActor(x, y, actor);
//                        getWorld()->addDroppingSquare(x, y);
                    
                    // play the SOUND_DROPPING_SQUARE_CREATED sound
                    getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
                }
            }
        }
    }
void Boo::doSomething() {
    if (paused) {
        // Check if Boo is on the same square as a waiting player avatar
        PlayerAvatar* player = getWorld()->getOverlappingPlayer(this);
        if (player != nullptr) {
            int chance = rand() % 2;
            PlayerAvatar* otherPlayer = getWorld()->getOtherPlayer(player);
            if (otherPlayer != nullptr){
                if (chance == 0) {
                    int temp = otherPlayer->getCoins();
                    otherPlayer->setCoins(player->getCoins());
                    player->setCoins(temp);
                }
                else if(chance == 1){
                    int temp = otherPlayer->getStars();
                    otherPlayer->setStars(player->getStars());
                    player->setStars(temp);
                }
                getWorld()->playSound(SOUND_BOO_ACTIVATE);
            }
        }
        m_pauseCounter--;
        if (m_pauseCounter <= 0) {
            // Boo has finished pausing
            int squares_to_move = randInt(1, 10);
            m_ticksToMove = squares_to_move * 8;
            int x, y;
            getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, x, y);
            if (!getWorld()->checkMove(x, y, getWalkDirection())) {
                // Avatar can't continue moving in current direction, so update the walk direction
                if (getWalkDirection() == right || getWalkDirection() == left) {
                    if (getWorld()->checkMove(x, y, up)) {
                        setWalkDirection(up);
                    }
                    else if (getWorld()->checkMove(x, y, down)) {
                        setWalkDirection(down);
                    }
                }
                else if (getWalkDirection() == up || getWalkDirection() == down) {
                    if (getWorld()->checkMove(x, y, right)) {
                        setWalkDirection(right);
                    }
                    else if (getWorld()->checkMove(x, y, left)) {
                        setWalkDirection(left);
                    }
                }
            }
            setDirection(getWalkDirection() == left ? 180 : 0);
            paused = false;
            walking = true;
        }
    }
    else if (getState() == WALKING) {
        int x, y;
        getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, x, y);
        if (getWorld()->checkMove(x, y, getWalkDirection())) {
            // Move two pixels in the walk direction
            moveAtAngle(getWalkDirection(), 2);
            m_ticksToMove--;
        }
        else {
            updateDir();
        }
            if (m_ticksToMove == 0) {
                paused = true;
                walking = false;
                m_pauseCounter = 180;
            }
        }
    }

void DirectionalSquare::doSomething(){
    PlayerAvatar* player = getWorld()->getOverlappingPlayer(this);
    if (player != nullptr){
        player->setWalkDirection(m_forceDir);
    }
}
void BankSquare::doSomething() {
    PlayerAvatar* player = getWorld()->getOverlappingPlayer(this);
    if (player != nullptr && player->getState() == PlayerAvatar::WAITING) {
        // Give the player all the coins from the bank account
        int coinsToGive = getBankBalance();
        player->setCoins(coinsToGive);

        // Reset the bank account balance
        setBankBalance(-coinsToGive);

        getWorld()->playSound(SOUND_WITHDRAW_BANK);
    }

    // Check if a player has moved onto the square
    if (player != nullptr) {
        // Deduct 5 coins from the player (or as many as they have)
        int coinsToDeduct = min(player->getCoins(), 5);
        player->setCoins(-coinsToDeduct);

        // Add the coins to the bank account
        setBankBalance(coinsToDeduct);

        getWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
}
void StarSquare::doSomething() {
    // Check if a new player has landed on or moved onto the square
    PlayerAvatar* player = getWorld()->getOverlappingPlayer(this);
    // If a new player has landed on or moved onto the square
    if (player != nullptr) {
        // Check if the player has enough coins
        if (player->getCoins() < 20) {
            return;
        }

        // Deduct coins from the player and give a star
        player->setStars(1);
        player->setCoins(-20);

        // Play sound
        getWorld()->playSound(SOUND_GIVE_STAR);

        // Reset state
//        m_newPlayer = nullptr;
//        m_ticksOnSquare = 0;
    }
}
void EventSquare::doSomething() {
    // Check if a player has landed upon the square
    PlayerAvatar* player = getWorld()->getOverlappingPlayer(this);
    if (player != nullptr) {
        // Choose a random action
        int action = randInt(1, 3);
        switch (action) {
            case 1:
                
                player->teleport();
                break;
                            case 2:
                                
                                {
                                    // Find the other player
                                    PlayerAvatar* otherPlayer = getWorld()->getOtherPlayer(player);
                                    if (otherPlayer != nullptr) {
                                        // Swap state
                                        int tempX = player->getX();
                                        int tempY = player->getY();
                                        int tempTicks = player->getTicksLeft();
                                        int tempWalkDir = player->getWalkDirection();
                                        int tempSpriteDir = player->getDirection();
                                        int tempState = player->getState();
                                        
                                        player->moveTo(otherPlayer->getX(), otherPlayer->getY());
                                        player->setTicksLeft(otherPlayer->getTicksLeft());
                                        player->setWalkDirection(otherPlayer->getWalkDirection());
                                        player->setDirection(otherPlayer->getDirection());
                                        player->setState(otherPlayer->getState());
                                        
                                        otherPlayer->moveTo(tempX, tempY);
                                        otherPlayer->setTicksLeft(tempTicks);
                                        otherPlayer->setWalkDirection(tempWalkDir);
                                        otherPlayer->setDirection(tempSpriteDir);
                                        otherPlayer->setState(tempState);
                                    
                
                                        getWorld()->playSound(SOUND_PLAYER_TELEPORT);
                                    }
                                }
                                break;
                            case 3:
                                // Give player a Vortex projectile
                                if (player->hasVortex()) {
                                    player->setVortex(true);
                                    getWorld()->playSound(SOUND_GIVE_VORTEX);
                                }
                                break;
            default:{
                break; }
                        }
        }
    }
void Vortex::doSomething(){
    

}
bool PlayerAvatar::isFork(){
    int numdir = 0;
    for(int i = 1; i <= 4; i++){
        int x = getX(), y = getY();
        if(i == 1){
            getPositionInThisDirection(right, SPRITE_WIDTH, x, y); //sets x and y
            if(getWorld()->checkMove(x, y, right))
                numdir++;
        }
        if(i == 2){
            getPositionInThisDirection(left, SPRITE_WIDTH, x, y); //sets x and y
            if(getWorld()->checkMove(x, y, left))
                numdir++;
        }
        if(i == 3){
            getPositionInThisDirection(up, SPRITE_WIDTH, x, y); //sets x and y
            if(getWorld()->checkMove(x, y, up))
                numdir++;
        }
        if(i == 4){
            getPositionInThisDirection(down, SPRITE_WIDTH, x, y); //sets x and y
            if(getWorld()->checkMove(x, y, down))
                numdir++;
        }
        
    }
    return numdir > 2;
}

void PlayerAvatar::doSomething() {
    StudentWorld* world = getWorld();
    if (!world) {
        return;
    }
    if (waiting) { // if player is waiting
        int x = getX(), y = getY();
        getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, x, y); //sets x and y
        if(getWorld()->checkMove(x, y, getWalkDirection()) == false) {
            // Avatar got teleported, so update the walk direction
            updateDir();
        }
        x = getX();
        y = getY();
        // Get the player ID
        int playerID = getPlayer();
        // Get the action for the player
        int action = world->getAction(playerID);
        switch(action){
            case ACTION_ROLL: {
                die_roll = randInt(1, 10);
                setTicksLeft(die_roll * 8);
//                setState(1);
                waiting = false;
                walking = true;
                break;
            }
            case ACTION_FIRE: {
                //cout << "fire" << endl;
                break;
            }
            case ACTION_NONE: {
                break;
            }
            default: {
                return;
            }
        }
    }
        if (walking) { //if player is walking
            int x = getX(), y = getY();
            // Get the player ID
            int playerID = getPlayer();
            getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, x, y);
            if(isFork()){
                int action = world->getAction(playerID);
                switch(action){
                    case ACTION_LEFT: {
                        int tempDir = left;
                        int newX = getX(), newY = getY();
                        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
                        if (getWorld()->checkMove(newX, newY, left)) {
                            setWalkDirection(left);
                        }
                        break;
                    }
                    case ACTION_RIGHT: {
                        int tempDir = right;
                        int newX = getX(), newY = getY();
                        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
                        if (getWorld()->checkMove(newX, newY, right)) {
                            setWalkDirection(right);
                        }
                        break;
                    }
                    case ACTION_UP: {
                        int tempDir = up;
                        int newX = getX(), newY = getY();
                        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
                        if (getWorld()->checkMove(newX, newY, up)) {
                            setWalkDirection(up);
                        }
                        break;
                    }
                    case ACTION_DOWN: {
                        int tempDir = down;
                        int newX = getX(), newY = getY();
                        getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
                        if (getWorld()->checkMove(newX, newY, down)) {
                            setWalkDirection(down);
                        }
                        break;
                    }
                    case ACTION_NONE: {
                        break;
                    }
                    default: {
                        return;
                    }
                }
                if (getWalkDirection() == left) {
                    setDirection(180);
                }
                else {
                    setDirection(0);
                }
            }
//            getPositionInThisDirection(getWalkDirection(), SPRITE_WIDTH, x, y);
           else if(getWorld()->checkMove(x, y, getWalkDirection()) == false) {
                // Avatar can't continue moving in current direction, so update the walk direction
                updateDir();
            }
            // Move two pixels in the walk direction and decrement the ticks_to_move count
            //cerr << "ticks:" << " " << m_ticksToMove << endl;
                moveAtAngle(getWalkDirection(), 2);
                m_ticksToMove --;
//            cerr << die_roll << endl;
            
            if (m_ticksToMove <= 0) {
                //cerr << "Got here" << endl;
                // Change the Avatar's state to the waiting to roll state
                walking = false;
                waiting = true;
            }
        }
    }

void CoinSquare::doSomething() {
    if(!getAlive()) {
        return;
    }
    PlayerAvatar* player = getWorld()->getOverlappingPlayer(this);
    if (player != nullptr) {
        // Set the state of the player to WAITING
        //cerr << "coin square" << endl;
            if(m_positiveCoins) {
                player->setCoins(3);
                getWorld()->playSound(SOUND_GIVE_COIN);
            }
            else {
                int numCoins = player->getCoins();
                // Deduct the coins from the player
                if(numCoins >= 3) {
                    player->setCoins(-3);
                }
                else {
                    player->setCoins(-numCoins);
                }
                // Play the SOUND_TAKE_COIN sound
                getWorld()->playSound(SOUND_TAKE_COIN);
            }

        }
}
void PlayerAvatar::teleport() {
    StudentWorld* world = getWorld();
    int x, y;

    // Keep generating random coordinates until we find a blue coin square
    do {
        x = rand() % VIEW_WIDTH;
        y = rand() % VIEW_HEIGHT;
    } while (!world->isBlueCoinSquare(x, y));

    // Move player to random coordinates
    moveTo(x, y);

    // Play teleport sound
    world->playSound(SOUND_PLAYER_TELEPORT);
}
void PlayerAvatar::updateDir(){
if (getWalkDirection() == right || getWalkDirection() == left) {
    int tempDir = up;
    int newX = getX(), newY = getY(); // what do i inititalize to?
    getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
    if (getWorld()->checkMove(newX, newY, up)) {
        setWalkDirection(up);
    }
    tempDir = down;
    newX = getX();
    newY = getY();
    getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
    if (getWorld()->checkMove(newX, newY, down)) {
        setWalkDirection(down);
    }
}
else if (getWalkDirection() == up || getWalkDirection() == down) {
    int tempDir = right;
    int newX = getX(), newY = getY(); // what do i inititalize to?
    getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);// up or down{ // up or down
    if (getWorld()->checkMove(newX, newY, right)) {
        setWalkDirection(right);
    }
    tempDir = left;
    newX = getX();
    newY = getY();
    getPositionInThisDirection(tempDir, SPRITE_WIDTH, newX, newY);
    if (getWorld()->checkMove(newX, newY, left)) {
        setWalkDirection(left);
    }
}
// Update the sprite direction based on the walk direction
if (getWalkDirection() == left) {
setDirection(180);
}
else {
setDirection(0);
}
}
