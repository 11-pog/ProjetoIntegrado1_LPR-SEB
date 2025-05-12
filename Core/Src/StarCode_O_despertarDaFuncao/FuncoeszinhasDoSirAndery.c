#include "FuncoeszinhasDoSirAndery.h"

void IniciarJogo(char diff) {
	SelectedX = 0;
	SelectedY = 0;

	LastSelectedX = 0;
	LastSelectedY = 0;

	Tries = 0;

	if (GameMode == MULTIPLAYER) {
		// Reset/Initialize Vars
		RedScore = 0;
		BlueScore = 0;

		RedTries = 0;
		BlueTries = 0;

		PlayerTurn = rand() % 2; // Decide quem começa aleatoriamente
		ShowTurn(); // Mostra quem começa
	}

	const char Size = CalcSize(diff);

	char CardField[Size][Size][3];
	/*
		 cardField[PosY][PosX][Attr]

		 PosY - A coordenada Y das cartas no tabuleiro
		 PosX - A coordenada X das cartas no tabuleiro
		 Attr - Os attributos de cada carta.

		 ATTRIBUTES:
		 0 - NUMBER_ATTR - Representa o numero da carta
		 1 - REVEAL_ATTR - Estado da carta (virado/desvirado/pareado)
		 2 - GRAPHIC_UPDATE_STATUS - Força a atualização do estado da carta na tela

	*/


	GerarParesAleatorios(Size, CardField);

	PrintGameScreen(Size, CardField);

	MainGameLoop(Size, CardField);
}

void MainGameLoop(size_t size, char field[size][size][3]) {
	char btns[4];

	while (VerificarFimDeJogo(size, field) == 0) {
		DetectAnyButtonPress(btns);

		if (btns[BTN_PIN_9] == PRESSED && btns[BTN_PIN_11] == PRESSED) {
			SelecionarCarta(size, field);
			continue;
		}

		if (btns[BTN_PIN_9] == PRESSED)
			NavegarCursor(-1, 0, size);
		if (btns[BTN_PIN_10] == PRESSED)
			NavegarCursor(0, 1, size);
		if (btns[BTN_PIN_11] == PRESSED)
			NavegarCursor(1, 0, size);
		if (btns[BTN_PIN_12] == PRESSED)
			NavegarCursor(0, -1, size);

		PrintGameScreen(size, field);
	}

	AtualizarRecorde();
	ExibirFimDeJogo();
}

void GerarParesAleatorios(char fieldSize,
		char cardField[fieldSize][fieldSize][3]) {

	/*
	 cardField[PosY][PosX][Attr]

	 PosY - A coordenada Y das cartas no tabuleiro
	 PosX - A coordenada X das cartas no tabuleiro
	 Attr - Os attributos de cada carta, até agora [0] é o numero/imagen da carta e [1] é se ela esta virada ou não
	 */

	InitFieldMatrix(fieldSize, cardField); // Inicializa a matriz

	for (int y = 0; y < fieldSize; y++)  // Percorre sobre toda linha na matriz
		for (int x = 0; x < fieldSize; x++)  // Percorre sobre toda colunas na matriz
			do { // Enquanto tiver mais de 2 de um mesmo numero, aleatorizar denovo
				cardField[y][x][NUMBER_ATTR] = (rand()
						% CalcPossibilities(fieldSize)) + 1; // aletoriza a carta em X, Y
				HAL_Delay(1); // Delay por causa da pseudo-aleatoriedade0
			} while (ContainsVector2(fieldSize, cardField,
					cardField[y][x][NUMBER_ATTR], NUMBER_ATTR) > 2);
}

void NavegarCursor(signed char directionX, signed char directionY, size_t size) {
	SelectedX += directionX;
	SelectedY += directionY;

	if (SelectedX < 0)
		SelectedX = size - 1;
	if (SelectedY < 0)
		SelectedY = size - 1;

	SelectedX %= size;
	SelectedY %= size;
}

void SelecionarCarta(size_t size, char field[size][size][3]) {
	if (field[SelectedY][SelectedX][REVEAL_ATTR] == UNREVEALED) {
		field[SelectedY][SelectedX][REVEAL_ATTR] = REVEALED;
		field[SelectedY][SelectedX][GRAPHIC_UPDATE_ATTR] = UPDATE;
	} else
		return;

	PrintGameScreen(size, field);

	if (ContainsVector2(size, field, REVEALED, REVEAL_ATTR) > 1) {
		CompararPares(size, field);
		PrintGameScreen(size, field);
		AtualizarTentativas();
	}
}

void CompararPares(size_t size, char field[size][size][3]) {
	const char selectedNumber = field[SelectedY][SelectedX][NUMBER_ATTR];

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (field[y][x][REVEAL_ATTR] == REVEALED) {
				if (field[y][x][NUMBER_ATTR] == selectedNumber) {

					Pair(size, field, x, y);

				} else {

					HAL_Delay(1000);
					field[SelectedY][SelectedX][REVEAL_ATTR] = UNREVEALED;
					field[y][x][REVEAL_ATTR] = UNREVEALED;
					if (GameMode == MULTIPLAYER) SwitchTurn();

				}

				field[SelectedY][SelectedX][GRAPHIC_UPDATE_ATTR] = UPDATE;
				field[y][x][GRAPHIC_UPDATE_ATTR] = UPDATE;
			}
		}
	}
}

char VerificarFimDeJogo(char size, char cardField[size][size][3]) {
	if (ContainsVector2(size, cardField, PAIRED, REVEAL_ATTR)
			== size * size)
		return 1;

	if (GameMode == MULTIPLAYER
			&& ContainsVector2(size, cardField, RED_PAIR, REVEAL_ATTR)
					+ ContainsVector2(size, cardField, BLUE_PAIR,
							REVEAL_ATTR) == size * size) // Se cartas vermelhas + cartas azuis igual a quantidade de cartas maxima, termina o jogo
		return 1;

	return 0;
}

void AtualizarTentativas(void) {
	if (GameMode == SINGLEPLAYER)
		Tries++;
	else if (PlayerTurn == BLUE_TURN)
		BlueTries++;
	else
		RedTries++;
}

void AtualizarRecorde(void) {
	if (Tries < GameRecord || GameRecord == 0)
		GameRecord = Tries;
}

void ExibirFimDeJogo(void) {
	ST7789_Fill_Color(BLACK);

	if (GameMode == SINGLEPLAYER)
		ST7789_WriteString(AlignText(16, 10), 20, "YOU GANHOU", Font_16x26,
		WHITE,
		BLACK);
	else if (BlueScore > RedScore)
		ST7789_WriteString(AlignText(16, 11), 20, "AZUL GANHOU", Font_16x26,
		BLUE,
		BLACK);
	else if (RedScore > BlueScore)
		ST7789_WriteString(AlignText(16, 14), 20, "VERMEIO GANHOU", Font_16x26,
		RED,
		BLACK);
	else
		ST7789_WriteString(AlignText(16, 6), 20, "EMPATE", Font_16x26,
		YELLOW,
		BLACK);

	if (GameMode == SINGLEPLAYER) {
		char ToString[15];
		sprintf(ToString, "Tentativas: %i", Tries);
		ST7789_WriteString(30, 100, ToString, Font_11x18,
		WHITE,
		BLACK);
	} else {
		ST7789_WriteString(30, 70, "Tentativas: ", Font_11x18,
				WHITE,
				BLACK);
		char ToString[30];
		sprintf(ToString, "Azul = %i\nVermeio = %i", BlueTries, RedTries);
		ST7789_WriteString(50, 90, ToString, Font_11x18,
		WHITE,
		BLACK);
	}

	// Saber Rodando
	for (int i = 0; i < 6; i++) {
		ST7789_DrawImage(95, 150, SABER_WIDTH, SABER_HEIGHT,
				(uint16_t*) saber_1);
		HAL_Delay(200);
		ST7789_DrawImage(95, 150, SABER_WIDTH, SABER_HEIGHT,
				(uint16_t*) saber_2);
		HAL_Delay(200);
		ST7789_DrawImage(95, 150, SABER_WIDTH, SABER_HEIGHT,
				(uint16_t*) saber_3);
		HAL_Delay(200);
		ST7789_DrawImage(95, 150, SABER_WIDTH, SABER_HEIGHT,
				(uint16_t*) saber_4);
		HAL_Delay(200);
	}
}
