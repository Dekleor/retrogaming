#include <Gamebuino-Meta.h>

// score
int score;
int finalScore;
int highScore = 0;
bool gameOver = false;
bool menu = true;

//player
int playerX;
int playerY;
const int PLAYER_WIDTH = 4;
const int PLAYER_HEIGHT = 4;

//Flies
int numberOfFlies = 0;
int swarmOfFlies [100][7];
const Color flyColor[8] = {GRAY, PURPLE, RED, YELLOW, DARKGRAY, BEIGE, DARKBLUE, BROWN};

void setup() {
    gb.begin();
}

void loop() {
    while (!gb.update());
    // INPUTS //
    inputs();

    // LOGIC //
    update();

    // DRAW //
    draw();
}


void inputs() {
    if (gb.buttons.repeat(BUTTON_LEFT, 1) && playerX > 0) {
        playerX -= 3;
    }
    else if (gb.buttons.repeat(BUTTON_RIGHT, 1) && playerX < gb.display.width() - PLAYER_WIDTH) {
        playerX += 3;
    }
    else if (gb.buttons.repeat(BUTTON_UP, 1) && playerY > 0) {
        playerY -= 3;
    }
    else if (gb.buttons.repeat(BUTTON_DOWN, 1) && playerY < gb.display.height() - PLAYER_HEIGHT) {
        playerY += 3;
    }
    if (gb.buttons.repeat(BUTTON_A, 25)) {
        menu = false;
        gameOver = false;
        score = 0;
        newGame();       
    }
}

void newGame() {
//init player
    playerX = 58;
    playerY = 58;

//init Flies
//0 = X; 1 = Y; 2 = ZX; 3 = ZY; 4 = width; 5 = height;
    for(int i = 0; i < 100; i++) {
            swarmOfFlies[i][0] = 25;
            swarmOfFlies[i][1] = 25;
            swarmOfFlies[i][2] = 1;
            swarmOfFlies[i][3] = 1;
            swarmOfFlies[i][6] = random(0, 7);

        if (i == 0) {
            swarmOfFlies[i][4] = 2;
            swarmOfFlies[i][5] = 2;
           
        } else {
            swarmOfFlies[i][4] = 0;
            swarmOfFlies[i][5] = 0;
        }
    }
}

void update() {
    score += 1;

    for (int i = 0; i <= numberOfFlies; i++) {

        // update movement
        swarmOfFlies[i][0] += swarmOfFlies[i][2];
        swarmOfFlies[i][1] += swarmOfFlies[i][3];

        // randomly moving
        int rand = random(2);

        if (score%2 == 0 && rand == 1) {
            if (swarmOfFlies[i][0] > 0 || swarmOfFlies[i][0] < gb.display.width()) {
                if (swarmOfFlies[i][0] < 1) {
                    swarmOfFlies[i][0] = 78;
                }
                if (swarmOfFlies[i][0] > 78) {
                    swarmOfFlies[i][0] = 1;
                }
                swarmOfFlies[i][2] *= -1;
            }
        }
    
        if (score%2 != 0 && rand == 1) {
            if (swarmOfFlies[i][0] > 0 || swarmOfFlies[i][0] < gb.display.width()) {
                if (swarmOfFlies[i][0] < 1) {
                    swarmOfFlies[i][0] = 78;
                }
                if (swarmOfFlies[i][0] > 78) {
                    swarmOfFlies[i][0] = 1;
                }
                swarmOfFlies[i][2] *= 1;
            }
        }
    
        if (score%2 == 0 && rand != 1) {
            if (swarmOfFlies[i][1] > 0 || swarmOfFlies[i][1] < gb.display.height()) {
                if (swarmOfFlies[i][1] < 1) {
                    swarmOfFlies[i][1] = 62;
                }
                if (swarmOfFlies[i][1] > 62) {
                    swarmOfFlies[i][1] = 1;
                }
                swarmOfFlies[i][3] *= -1;
            }
        }
      
        if (score%2 != 0 && rand != 1) {
            if (swarmOfFlies[i][1] > 0 || swarmOfFlies[i][1] < gb.display.height()) {
                if (swarmOfFlies[i][1] < 0) {
                    swarmOfFlies[i][1] = 63;
                }
                if (swarmOfFlies[i][1] > 63) {
                    swarmOfFlies[i][1] = 0;
                }
                swarmOfFlies[i][3] *= 1;
          }
        }
      }
    //bee spwaning
    if (score % 25 == 0) {
        numberOfFlies += 1;
        swarmOfFlies[numberOfFlies][4] = 2;
        swarmOfFlies[numberOfFlies][5] = 2;
    }

    //snake and player colliding
    for(int i; i < 100; i++) {
        if (gb.collide.rectRect(playerX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT, swarmOfFlies[i][0], swarmOfFlies[i][1], swarmOfFlies[i][4], swarmOfFlies[i][5])) {
            finalScore = score;
            if (finalScore > highScore) {
                highScore = finalScore;
            }
    //putting player off map to avoid further collisions
            playerX = -10;
            playerY = -10;

            gameOver = true;
        }
    }
}

void draw() {
    gb.display.clear();

    if(menu) {
        gb.display.setCursor(10, 25);
        gb.display.println("Bees panic !!!");
        gb.display.setCursor(7, 40);
        gb.display.println("Press A to start");
        } else if (!gameOver) {
            gb.display.setCursor(3, 3);
            gb.display.print(score);
    
            //player
            gb.display.setColor(PINK);
            gb.display.fillRect(playerX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT);
    
            //Flies
            for (int i = 0; i <= numberOfFlies; i++) {
                gb.display.setColor(flyColor[swarmOfFlies[i][6]]);
                gb.display.fillRect(swarmOfFlies[i][0], swarmOfFlies[i][1], swarmOfFlies[i][4], swarmOfFlies[i][5]);
                }
        } else if (gameOver) {
            gb.display.setCursor(25, 25);
            gb.display.println("GAME OVER");
            gb.display.print("Your score : ");
            gb.display.println(finalScore);
            gb.display.print("Highest score : ");
            gb.display.println(highScore);
            gb.display.setCursor(4, 50);
            gb.display.println("Press A to restart");
        }   
}