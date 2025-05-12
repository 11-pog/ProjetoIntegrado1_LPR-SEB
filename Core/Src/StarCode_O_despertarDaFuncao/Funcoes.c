#include "Funcoes.h"

void Menu(void) {
	ST7789_WriteString(90, 60, "MENU", Font_16x26, WHITE, BLACK);
	ST7789_WriteString(60, 120, "New Game", Font_11x18, WHITE, BLACK);

	char result[12];
	sprintf(result, "Record: %i", GameRecord);
	ST7789_WriteString(60, 140, result, Font_11x18, WHITE, BLACK);

	ST7789_WriteString(36, 180, "Pressione qualquer botao", Font_7x10, WHITE,
	BLACK);
	ST7789_WriteString(82, 190, "Pra comecar", Font_7x10, WHITE, BLACK);

	AwaitForAnyButton();
}

void PrintSelectDifficulty(char selection) {
	ST7789_WriteString(20, 30, "Selecione uma\ndificuldade:", Font_11x18, WHITE,
	BLACK);

	switch (selection) {
	case 0:
		ST7789_WriteString(10, 120, "- 4x4", Font_11x18, YELLOW, BLACK);
		ST7789_WriteString(10, 140, "- 6x6", Font_11x18, WHITE, BLACK);
		break;
	case 1:
		ST7789_WriteString(10, 120, "- 4x4", Font_11x18, WHITE, BLACK);
		ST7789_WriteString(10, 140, "- 6x6", Font_11x18, YELLOW, BLACK);
		break;
	default:
		break;
	}
}

char SelectDifficulty(void) {
	ST7789_Fill_Color(BLACK);
	PrintSelectDifficulty(0);

	char btns[3];
	const char UsingBtns[3] = { 10, 11, 12 };

	char selection = SIZE4X4;

	do {
		DetectButtonPress((char*) UsingBtns, btns, 3);

		if (btns[0] == 0 || btns[2] == 0) {
			selection++;
			selection %= 2;
		}

		PrintSelectDifficulty(selection);
	} while (btns[1] == UNPRESSED);

	return selection;
}

void PrintSelectMode(char selection) {
	ST7789_WriteString(20, 30, "Modo de Jogo: ", Font_11x18, WHITE, BLACK);
	switch (selection) {
	case 0:
		ST7789_WriteString(10, 120, "Singleplayer", Font_11x18, YELLOW, BLACK);
		ST7789_WriteString(10, 140, "Multiplayer", Font_11x18, WHITE, BLACK);
		break;
	case 1:
		ST7789_WriteString(10, 120, "Singleplayer", Font_11x18, WHITE, BLACK);
		ST7789_WriteString(10, 140, "Multiplayer", Font_11x18, YELLOW, BLACK);
		break;
	default:
		break;
	}
}

char SelectMode(void) {
	ST7789_Fill_Color(BLACK);
	PrintSelectMode(0);
	char btns[3];
	const char UsingBtns[3] = { 10, 11, 12 };

	char selection = SINGLEPLAYER;

	do {
		DetectButtonPress((char*) UsingBtns, btns, 3);

		if (btns[0] == 0 || btns[2] == 0) {
			selection++;
			selection %= 2;
		}

		PrintSelectMode(selection);
	} while (btns[1] == UNPRESSED);

	return selection;
}

void PrintGameScreen(size_t size, char cardField[size][size][3]) {
	const char cardGapY = CalcCardGap(size, CARD_HEIGHT);
	const char cardGapX = CalcCardGap(size, CARD_WIDTH);

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (UpdateCardImage(x, y, cardField[y][x]) == 1) {
				PrintCard(x, y, cardGapX, cardGapY, size, cardField[y][x]);
				cardField[y][x][GRAPHIC_UPDATE_STATUS] = STANDBY;
			}
		}
	}

	LastSelectedX = SelectedX;
	LastSelectedY = SelectedY;
}

char UpdateCardImage(uint8_t x, uint8_t y, char card[3]) {
	if ((SelectedX == x && SelectedY == y)
			|| (LastSelectedX == x && LastSelectedY == y))
		return 1;

	if (IsUnpaired(card) == 1)
		return 1;

	if (card[GRAPHIC_UPDATE_STATUS] == UPDATE)
		return 1;

	return 0;
}

void PrintCard(uint8_t cardX, uint8_t cardY, uint8_t GapX, uint8_t GapY, size_t size, char card[3]) {
	const uint8_t x = CalcCardPos(GapX, CARD_WIDTH, cardX);
	const uint8_t y = CalcCardPos(GapY, CARD_HEIGHT, cardY);

	switch (card[REVEAL_ATTR]) {
	case UNREVEALED:
		if (cardX == SelectedX && cardY == SelectedY)
			ST7789_DrawImage(x, y, CARD_WIDTH, CARD_HEIGHT,
					(uint16_t*) SelectedCard);
		else
			ST7789_DrawImage(x, y, CARD_WIDTH, CARD_HEIGHT,
					(uint16_t*) CardBackemon);
		break;

	case REVEALED:
	case PAIRED:
		DrawRevealedCard(x, y, cardX, cardY, card[NUMBER_ATTR], WHITE);
		break;

	case RED_PAIR:
		DrawRevealedCard(x, y, cardX, cardY, card[NUMBER_ATTR], RED);
		break;

	case BLUE_PAIR:
		DrawRevealedCard(x, y, cardX, cardY, card[NUMBER_ATTR], BLUE);
		break;
	}
}

void DrawRevealedCard(uint8_t x, uint8_t y, uint8_t cardX, uint8_t cardY, char cardValue, uint16_t bgColor)
{
	if (cardX == SelectedX && cardY == SelectedY)
		ST7789_DrawFilledRectangle(x, y, CARD_WIDTH - 1, CARD_HEIGHT - 1,
		YELLOW);
	else
		ST7789_DrawFilledRectangle(x, y, CARD_WIDTH - 1, CARD_HEIGHT - 1,
		bgColor);

	char NumString[2];
	sprintf(NumString, "%i", cardValue);

	ST7789_WriteString(x, y + 5, NumString, Font_11x18, BLACK, WHITE);
}

void ReadButtons(char *out) {
	out[0] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
	out[1] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
	out[2] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);
	out[3] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12);
}

void AwaitForAnyButton(void) {
	char buttons[4];

	do {
		ReadButtons(buttons);
	} while (!Contains(4, buttons, PRESSED));
}

void DetectAnyButtonPress(char *out) {
	const unsigned int MultiButtonCaptureWindowMs = 200;
	char buttons[4];

	for (int i = 0; i < 4; ++i)
		out[i] = UNPRESSED;

	do {
		ReadButtons(buttons);
	} while (!Contains(4, buttons, PRESSED));

	long btnPressTime = HAL_GetTick();

	do {
		for (int i = 0; i < 4; ++i)
			if (out[i] == UNPRESSED)
				out[i] = buttons[i];

		ReadButtons(buttons);
	} while (HAL_GetTick() - btnPressTime < MultiButtonCaptureWindowMs);
}

void DetectButtonPress(char buttons[], char *out, size_t amount) {
	char btnValues[4];
	char end = 0;
	do {
		DetectAnyButtonPress(btnValues);

		uint8_t outIndex = 0;
		for (uint8_t i = 0; i < 4; i++) {
			if (Contains(amount, buttons, i + 9)) {
				if (btnValues[i] == UNPRESSED)
					end = 1;
				out[outIndex] = btnValues[i];
				outIndex++;
			}
		}
	} while (end == 0);
}

void InitFieldMatrix(size_t size, char matrix[size][size][3]) {
	for (int y = 0; y < size; y++) // Percorre sobre toda linha na matriz
		for (int x = 0; x < size; x++) { // Percorre sobre toda coluna na matriz
			matrix[y][x][NUMBER_ATTR] = 0; // Inicializa o numero da carta como 0 (não atribuido)
			matrix[y][x][REVEAL_ATTR] = UNREVEALED; // Inicializa a carta como Não Revelado
			matrix[y][x][GRAPHIC_UPDATE_STATUS] = UPDATE;
		};
}
// Teste
void Pair(size_t size, char field[size][size][3], uint8_t x, uint8_t y) {
	if (GameMode == MULTIPLAYER) {
		if (PlayerTurn == BLUE_TURN) {
			field[SelectedY][SelectedX][REVEAL_ATTR] = BLUE_PAIR;
			field[y][x][REVEAL_ATTR] = BLUE_PAIR;
			BlueScore++;
		} else {
			field[SelectedY][SelectedX][REVEAL_ATTR] = RED_PAIR;
			field[y][x][REVEAL_ATTR] = RED_PAIR;
			RedScore++;
		}
	} else {
		field[SelectedY][SelectedX][REVEAL_ATTR] = PAIRED;
		field[y][x][REVEAL_ATTR] = PAIRED;
	}

	field[SelectedY][SelectedX][GRAPHIC_UPDATE_STATUS] = UPDATE;
	field[y][x][GRAPHIC_UPDATE_STATUS] = UPDATE;
}

void SwitchTurn(void) {
	PlayerTurn++;
	PlayerTurn %= 2;

	ShowTurn();
}

void ShowTurn(void) {
	if (PlayerTurn == BLUE_TURN) {
		ST7789_DrawFilledRectangle(0, 0, 5, 240, BLUE);
		ST7789_DrawFilledRectangle(235, 0, 5, 240, BLACK);
	} else {
		ST7789_DrawFilledRectangle(0, 0, 5, 240, BLACK);
		ST7789_DrawFilledRectangle(235, 0, 5, 240, RED);
	}
}

void TestPrint(size_t fieldSize, char field[fieldSize][fieldSize][3]) {
	for (int y = 0; y < fieldSize; y++)
		for (int x = 0; x < fieldSize; x++) {
			char ToWrite[2];
			sprintf(ToWrite, "%i", field[y][x][NUMBER_ATTR]);

			ST7789_WriteString(x * 36, y * 36, ToWrite, Font_11x18, WHITE,
			BLACK);
		};
}


char IsUnpaired(char card[3])
{
	if (card[REVEAL_ATTR] == UNREVEALED
			|| card[REVEAL_ATTR] == REVEALED)
		return 1;
	return 0;
}

char Contains(size_t size, char Iterable[size], char Contains) {
	int recurrence = 0;

	for (int i = 0; i < size; i++) {
		if (Iterable[i] == Contains) {
			recurrence++;
		}
	}
	return recurrence;
}

char ContainsVector2(size_t size, char Iterable[size][size][3], char Contains,
		uint8_t attr) {
	int recurrence = 0;

	for (uint8_t y = 0; y < size; y++) {
		for (uint8_t x = 0; x < size; x++) {
			if (Iterable[y][x][attr] == Contains) {
				recurrence++;
			}
		}
	}
	return recurrence;
}
