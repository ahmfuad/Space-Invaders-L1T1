# Space Invaders

![image](https://github.com/ahmfuad/Space-Invaders-L1T1/assets/42442668/23a074b6-c928-45ec-b5ad-fedd7e0566a5)

Space Invaders is a 1978 Japanese video game. It is a fixed shooter game. There are simply three characters: Shooter, Enemy, and Boss UFO. There is only one level with a fixed number of enemies. After a certain time, the Boss enemy comes and shoots bullets. Shooter has two lives. Enemies and Boss UFO shoot bullets to destroy the earth. Shooter has to safeguard himself and kill all the enemies. Thus, the shooter will gain points.

The task is to recreate it as closely as possible.

## Features and Implementations

Game features are discussed here briefly with implementation ideas:

### Main Menu

A main menu screen loads at the very beginning. It is an image of the size of the game screen. Dimensions of the game screen are 1024 × 720. It has five sub-options.

- Start Game
- Shooter Avatar Choose
- Leaderboard
- Settings
- Exit

Implementation: This is an image of size 1024 × 720. When the user presses on a certain coordinate range, the state changes and the user enters the respective option.

### Settings

Here, the user can choose if the sound will be on or off and reset high scores. After clicking on the Settings button a new window will appear. There are two different sub-features,

#### Sound

There are two types of sound available. One is constant sound for the main menu and game pause. Another is shooting and enemy destruction sound. Players can choose the sound will be on or off.

#### Reset Scores

Scores are initially saved in a .txt file. When a user clicks on this button all the saved scores are cleared.

Implementation: A simple line of code does the work:

```
fclose(fopen("path", "w"));
```

#### Leaderboard

When a user clicks on the leaderboard, scores are fetched from the text file, and the highest five numbers are shown on the screen. If not enough data then “N/A” is shown as a placeholder.

#### Avatar

Users can choose between two types of default avatars from the main menu.

Implementation: By clicking on the image of avatars, the shooter image avatar path changes. Both shooter image paths are stored in a 2D character array. If avatar 1 is selected, 1st index of the array is used as the path, and the other one is likewise.

#### Game Play

This is the most important part of this project. Features implemented in the gameplay are, Shooter position, Shooter life, Shooter’s bullet firing and destruction of enemies, Enemy movement, Attack of the Enemies, Enemies descending after a certain time, Boss UFO appearance after a certain time, Boss UFO attack, Scoring, Game Pause, Game End.

##### Shooter

__Movement:__ Shooter moves right or left by 10 pixels per move. Users can use the Right and Left arrow keys to move the shooter.

Firing & Enemy Kill: Shooter will fire bullets (one at a time) after the user presses the SPACE button. There will be a firing sound in the background. Enemy kill-checking algorithm:

```
IF ENEMY\_X >= BULLET\_X && ENEMY\_X + ENEMY\_SIZE <= BULLET\_X:
  IF BULLET\_Y >= ENEMY\_Y && BULLET\_Y <= ENEMY\_Y + ENEMY\_HEIGHT:
    // killed
```
__Life:__ Shooter has two lives. When an enemy bullet hits the shooter, one life is used. The game will end after both of the lives are used.

##### Enemy

__Movement:__ There are 24 enemies, usually placed as a 4×6 grid. They will move horizontally together. When they touch a border they ascend a row down and move the other way.

Attack: After a random time interval, the enemy side shoots lightning. If this lightning hits the shooter, the shooter loses a life.

##### UFO

__Movement:__ This type of enemy has linear movement. It appears from the rightmost upper corner and moves horizontally leftwards.

__Implementation:__ The Whole game screen is considered as a 12 × 12 grid. First, we need to assign a direction. Then each 10 milliseconds we iterate through every cell, and check if there is an enemy in this cell, if yes then we shift this enemy to the next cell according to direction. If the enemy is in a border cell then we need to shift it one row down and change the direction of movement.

__Attack:__ If the shooter tries to come underneath and attack it, it will shoot firebombs which will destroy the shooter's spaceship.

__Health:__ This type of enemy has twice the health of usual enemies. Two bullets are needed to destroy one UFO.

##### Scoring

One bullet hit kills general enemies, and two hits kill Boss UFO. Each enemy kill is worth 10 points and each Boss kill is worth 50 points. The score is shown in the left bottom corner of the screen. It updates after every kill.

##### Pause & END

__Pause:__ The game pauses when the user presses ‘P’ and resumes when the user presses ‘R’. But in the background, it’s a lot more. All the timers running for movement and checking are paused also. Shooter movement is also turned off when the game is paused.

__END:__ The game ends in three conditions:

1. Both lives of the shooter are used
2. Any enemy touches the shooter
3. All of the enemies are killed

For 1 and 2, the ‘GAME OVER’ message appears on the screen after. For 3, the ‘Winner’ message appears on the screen.

The final score is saved in a text file when the game ends because of any three of these conditions.

##### Exit

Pressing the ‘ESC’ or Exit button on the main menu kills the entire process and closes the game window.

###  Challenges and Fixes
- Random Crash: This was my biggest struggle in the whole process. The game used to crash in random places. I checked every algorithm involved, they were okay. Then I tried changing every photo I used. Even I reinstalled the compiler. It was better than before but not fixed yet. Finally, I went through IGraphics, especially iShowBmp() implementation. There were two implementations, one of which was commented out. I uncommented it and commented on the usual one. Finally, the crashing issue was solved.
- Sound: Usually using Playsound() leads to error. It needs to be compiled with ```- lwinmm```argument in vscode and for code blocks winmm library needs to be linked from compiler linkers. Also, I was planning to play multiple sounds for the game background and bullet shooting. But later I came to know it is not possible to do so.
- Debugging Coordinates: In this project for option or screen switch, it was a necessity to know the mouse coordinates. Printing them one by one and checking them was an easy yet cumbersome task.
- Code flow: The code base is not that small so it was a little hard to recall and reorganize all the functions. And after a break, it was hard to regain the previous workflow. It was fun though!
## Additional<a name="_page5_x72.00_y468.15"></a> Works & Links
- Project Demonstration Video Link: [Click Here](https://www.youtube.com/watch?v=dQw4w9WgXcQ)
- A GitHub repository was maintained throughout the whole development process. [HERE](https://github.com/ahmfuad/Space-Invaders-L1T1)is the link to the repository. (😉)
- LATEX was used to write the project report.
