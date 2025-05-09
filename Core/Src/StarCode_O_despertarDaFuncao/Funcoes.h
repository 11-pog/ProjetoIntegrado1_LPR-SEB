#ifndef _PRIV_FUNCTIONS_H
#define _PRIV_FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

#include "../ST7789/st7789.h"
#include "ImagensOfTheGame.h"


// Defines
// Field Size
#define SIZE4X4 0
#define SIZE6X6 1

// Game Mode
#define SINGLEPLAYER 0
#define MULTIPLAYER 1

// Button State
#define PRESSED 0
#define UNPRESSED 1

// Card Attributes
#define CARD_NUMBER_ATTR 0
#define CARD_REVEAL_ATTR 1

// Card Reveal Status
#define UNREVEALED 0
#define REVEALED 1
#define PAIRED 2 // Singleplayer Only
#define BLUE_PAIR 3 // Multiplayer Only
#define RED_PAIR 4 // Multiplayer Only

// Multiplayer Turn
#define BLUE_TURN 0
#define RED_TURN 1

// Card Image Size
#define CARD_HEIGHT 30
#define CARD_WIDTH 21

// Buttons
#define BTN_PIN_9 0
#define BTN_PIN_10 1
#define BTN_PIN_11 2
#define BTN_PIN_12 3

// Macro
#define AlignText(w, len) ((ST7789_WIDTH/2) - ((len*w)/2))
#define CalcSize(i) (4+i*2)
#define CalcPossibilities(Size) (Size*Size/2)

#define CalcCardGap(size, cardSize) ((ST7789_HEIGHT - size * cardSize) / (size * 2))
#define CalcCardPos(cardGap, cardSize, pos) (cardGap*(pos+1)*2 + (cardSize*pos) - cardGap)


// Global Variables
signed char SelectedX;
signed char SelectedY;

signed char LastSelectedX;
signed char LastSelectedY;

char GameMode;

int GameRecord; // Singleplayer Only
int Tries; // Singleplayer Only

// Multiplayer Exclusive
char PlayerTurn;
int BlueScore;
int RedScore;

int RedTries;
int BlueTries;

// Functions
// Button Detection
void AwaitForAnyButton(void);
void ReadButtons(char *out);
void DetectAnyButtonPress(char *out);
void DetectButtonPress(char buttons[], char *out, size_t amount);

// Screens
void Menu(void);

void PrintSelectDifficulty(char selection);
char SelectDifficulty(void);

void PrintSelectMode(char selection);
char SelectMode(void);

void PrintGameScreen(size_t size, char cardField[size][size][2]);
char UpdateCardImage(uint8_t x, uint8_t y, char card[2]);
void PrintCard(uint8_t cardX, uint8_t cardY, uint8_t GapX, uint8_t GapY, size_t size, char field[size][size][2]);
void DrawRevealedCard(uint8_t x, uint8_t y, uint8_t cardX, uint8_t cardY, char cardValue, uint16_t bgColor);

// Functionality
void InitFieldMatrix(size_t size, char matrix[size][size][2]);
void Pair(size_t size, char field[size][size][2], uint8_t x, uint8_t y);

// Multiplayer
void SwitchTurn(void);
void ShowTurn(void);

// Testes
void TestPrint(size_t fieldSize, char field[fieldSize][fieldSize][2]);

// Other/Util
char IsUnpaired(char card[2]);
char Contains(size_t size, char Iterable[size], char Contains);
char ContainsVector2(size_t size, char Iterable[size][size][2], char Contains, uint8_t attr);

// Pedro piadas
typedef uint16_t ceru;
typedef uint8_t alu;
typedef uint64_t ex;

// Pokemon
char mander(void);
char meleon(void);
char izard(void);
char cadet(void);
ceru ledge(void);
int elion(void);
float zel(void);
alu card(void);
ex calibur(void);

// que(rosene)
int ernet(void);
bool AAAAAAAA(void);

#endif
