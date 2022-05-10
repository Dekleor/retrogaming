#include <Gamebuino-Meta.h>

int score = 0;

//player
int playerX = 58;
int playerY = 58;
const int PLAYER_WIDTH = 3;
const int PLAYER_HEIGHT = 3;

//Flies
int numberOfFlies = 0;
int swarmOfFlies [100][7];
const Color flyColor[8] = {GRAY, PURPLE, RED, YELLOW, DARKGRAY, BEIGE, DARKBLUE, BROWN};

void setup() {
    gb.begin();
    initialize();
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
            if (swarmOfFlies[i][0] < 0 || swarmOfFlies[i][0] < gb.display.width()) {
                swarmOfFlies[i][2] *= -1;
            }
        }
    
        if (score%2 != 0 && rand == 1) {
            if (swarmOfFlies[i][0] < 0 || swarmOfFlies[i][0] < gb.display.width()) {
                swarmOfFlies[i][2] *= 1;
            }
        }
    
        if (score%2 == 0 && rand != 1) {
            if (swarmOfFlies[i][1] < 0 || swarmOfFlies[i][1] < gb.display.width()) {
                swarmOfFlies[i][3] *= -1;
            }
        }
      
        if (score%2 != 0 && rand != 1) {
            if (swarmOfFlies[i][1] < 0 || swarmOfFlies[i][1] < gb.display.width()) {
                swarmOfFlies[i][3] *= 1;
            }
        }
      }

    if (score % 25 == 0) {
        numberOfFlies += 1;
        swarmOfFlies[numberOfFlies][4] = 3;
        swarmOfFlies[numberOfFlies][5] = 3;
    }

    //snake and player colliding
}

void initialize() {
//init snake
//0 = X; 1 = Y; 2 = ZX; 3 = ZY; 4 = width; 5 = height;
    for(int i = 0; i < 100; i++) {
            swarmOfFlies[i][0] = 10;
            swarmOfFlies[i][1] = 10;
            swarmOfFlies[i][2] = 1;
            swarmOfFlies[i][3] = 1;
            swarmOfFlies[i][6] = random(0, 7);

        if (i == 0) {
            swarmOfFlies[i][4] = 3;
            swarmOfFlies[i][5] = 3;
           
        } else {
            swarmOfFlies[i][4] = 0;
            swarmOfFlies[i][5] = 0;
            }
    }
}

void draw() {
    gb.display.clear();
    gb.display.print(score);
    
    //player
    gb.display.setColor(PINK);
    gb.display.fillRect(playerX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT);
    

    //Flies
    for (int i = 0; i <= numberOfFlies; i++) {
        gb.display.setColor(flyColor[swarmOfFlies[i][6]]);
        gb.display.fillRect(swarmOfFlies[i][0], swarmOfFlies[i][1], swarmOfFlies[i][4], swarmOfFlies[i][5]);
    }
}