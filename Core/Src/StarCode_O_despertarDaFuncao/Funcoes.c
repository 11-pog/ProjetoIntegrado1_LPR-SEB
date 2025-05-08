#include "Funcoes.h"

void Menu(int record) {
	ST7789_WriteString(90, 60, "MENU", Font_16x26, WHITE, BLACK);
	ST7789_WriteString(60, 120, "New Game", Font_11x18, WHITE, BLACK);

	char result[12];
	sprintf(result, "Record: %i", record);
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
	} while (btns[1] != 0);

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
	} while (btns[1] != 0);

	return selection;
}

void PrintGameScreen(char CardField)
{

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
	} while (!Contains(4, buttons, 0));
}

void DetectAnyButtonPress(char *out) {
	char buttons[4];

	for (int i = 0; i < 4; ++i)
		out[i] = 1;

	do {
		ReadButtons(buttons);
	} while (!Contains(4, buttons, 0));

	long btnPressTime = HAL_GetTick();

	do {
		for (int i = 0; i < 4; ++i)
			if (out[i] == 1)
				out[i] = buttons[i];

		ReadButtons(buttons);
	} while (HAL_GetTick() - btnPressTime < 100);
}

void DetectButtonPress(char buttons[], char *out, size_t amount) {
	char btnValues[4];
	char end = 0;
	do {
		DetectAnyButtonPress(btnValues);

		char outIndex = 0;
		for (int i = 0; i < 4; i++) {
			if (Contains(amount, buttons, i + 9)) {
				char aux = NOTPRESSED;
				if (btnValues[i] == aux)
					end = 1;
				out[outIndex] = btnValues[i];
				outIndex++;
			}
		}
	} while (end == 0);
}

void TestPrint(size_t fieldSize, char field[fieldSize][fieldSize][2]) {
	for (int i = 0; i < fieldSize; i++)
		for (int j = 0; j < fieldSize; j++) {
			char ToWrite[2];
			sprintf(ToWrite, "%i", field[i][j][0]);

			ST7789_WriteString(i * 36, j * 36, ToWrite, Font_11x18, WHITE,
			BLACK);
		};
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

char ContainsVector2(size_t size, char Iterable[size][size][2], char Contains) {
	int recurrence = 0;
	char spy;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (Iterable[i][j][0] == Contains) {
				spy = Iterable[i][j][0];
				recurrence++;
			}
		}
	}
	return recurrence;
}
