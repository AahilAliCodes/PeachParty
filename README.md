# PeachParty

## About the Game
- Peach Party is a two-player game set in a world that resembles a traditional board game. The players must direct their avatars, Peach and Yoshi, along the squares on the game board collecting coins and stars, while trying to avoid baddies like Bowser and Boo who cause all sorts of trouble. When the game starts, the players may choose what board they want to play by pressing a key from 1 to 9; each board has a different layout and set of challenges. The winner of the game is the player who has collected the most stars and coins during 99 seconds of game play. If both players have collected the same number of stars, then the number of coins is used as a tie-breaker. If both players have the same number of stars and coins, then a winner is randomly picked.

- Like a board game, Peach Party requires the players to roll a (virtual) 10-sided die to decide how far they can move along the board during their next turn. To roll a virtual die, each player hits a key (more details below). After rolling, the player that rolled then travels along the board's squares in their current direction until they've moved the appropriate number of squares, at which time they "land" on a square. Then they get to roll the die again. If a player hits a fork on the board where they could move in more than one direction, they may select one of the paths to take (e.g., up vs. down vs. left) using the keyboard, and then they will continue passing over squares until they exhaust their die roll.

## How to run the game:
The game can be run on Xcode for MacOS and Vscode for Windows. Simply put the files in the IDE

### Notes for Visual C++ users:

- If the Windows skeleton doesn't build for you, you probably need to ensure that your project is using Windows SDK Version 10.0.19041.0 or 10.18362.0 or 10.0.17763.0 (or possibly 10.0.22000.0). To do this:
Launch the Visual Studio Installer, find your version of Visual Studio, and select Modify. In the list on the right side of optional packages, make sure SDK 10.0.19041.0 or 10.18362.0 or 10.0.17763.0 (or possibly 10.0.22000.0) is selected.
After modifying your Visual Studio installation, open the project in Visual Studio and right-click on Solution 'PeachParty' above the list of source files. Select Retarget Solution and choose the newly installed version of the SDK.
Build the project.
- Also, if the skeleton crashes after 1 to 30 seconds with a dialog box showing an error code 0xc0000022, try disabling your antivirus software and building the executable.

### Notes for Xcode users (MacOS):

- You might get a message at startup relating to the Assets directory. If you want to fix the issue just for this project, select File / Project Settings... and for Derived Data Location, select Project-relative Location. If instead you want to fix it for every project you create with Xcode, select Xcode / Preferences... and for the Derived Data, select Relative. Alternatively, you could simply change the assetDirectory string literal in main.cpp to be a full path name to wherever you choose to put the Assets directory.

- If you build and run your program from within Xcode, the Assets directory should be in
the directory yourProjectDir/DerivedData/yourProjectName/Build/Products/Debug (e.g.,
/Users/ethel/CS32Project3/DerivedData/PeachParty/Build/Products/Debug). On the
other hand, if you launch the program by double-clicking on the executable file, the
Assets directory should be in your home directory (e.g., /Users/ethel).

