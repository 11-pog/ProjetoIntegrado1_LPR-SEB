#include "FuncoeszinhasDoSirAndery.h"

void IniciarJogo(char diff, char mode) {
	SelectedX = 0;
	SelectedY = 0;

	LastSelectedX = 0;
	LastSelectedY = 0;

	const char Size = CalcSize(diff);

	char CardField[Size][Size][2];
	GerarParesAleatorios(Size, CardField);

	PrintGameScreen(Size, CardField);
	MainGame(Size, CardField);
}

void MainGame(size_t size, char field[size][size][2]) {
	char btns[4];


	while (VerificarFimDeJogo(size, field) == 0) {
		DetectAnyButtonPress(btns);

		if (btns[0] == 0 && btns[2] == 0) {
			SelecionarCarta(size, field);
			continue;
		}

		if (btns[0] == 0)
			NavegarCursor(-1, 0, size);
		if (btns[1] == 0)
			NavegarCursor(0, 1, size);
		if (btns[2] == 0)
			NavegarCursor(1, 0, size);
		if (btns[3] == 0)
			NavegarCursor(0, -1, size);

		PrintGameScreen(size, field);
	}

	ExibirFimDeJogo();
}

void GerarParesAleatorios(char fieldSize,
		char cardField[fieldSize][fieldSize][2]) {

	/*
	 cardField[PosY][PosX][Attr]

	 PosY - A coordenada Y das cartas no tabuleiro
	 PosX - A coordenada X das cartas no tabuleiro
	 Attr - Os attributos de cada carta, até agora [0] é o numero/imagen da carta e [1] é se ela esta virada ou não
	 */

	for (int Y = 0; Y < fieldSize; Y++) // Itera sobre toda coluna na matriz
		for (int X = 0; X < fieldSize; X++) // Itera sobre toda linha na matriz
			cardField[Y][X][0] = 0; // Inicializa o array inteiro como 0

	for (int Y = 0; Y < fieldSize; Y++) { // Itera sobre toda coluna na matriz
		for (int X = 0; X < fieldSize; X++) { // Itera sobre toda linha na matriz

			do { // Enquanto tiver mais de 2 de um mesmo numero, aleatorizar denovo
				cardField[Y][X][0] = (rand() % CalcPossibilities(fieldSize))
						+ 1; // aletoriza a carta em X, Y
				HAL_Delay(1); // Delay pra ver
			} while (ContainsVector2(fieldSize, cardField, cardField[Y][X][0],
					0) > 2);

			cardField[Y][X][1] = 0; // Atributo inicializado como 0
		}
	}
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

void SelecionarCarta(size_t size, char field[size][size][2]) {
	if (field[SelectedY][SelectedX][1] == 0)
		field[SelectedY][SelectedX][1] = 1;

	PrintGameScreen(size, field);

	if (ContainsVector2(size, field, 1, 1) > 1) {
		CompararPares(size, field);

		PrintGameScreen(size, field);
	}
}

void CompararPares(size_t size, char field[size][size][2]) {
	const char selectedNumber = field[SelectedY][SelectedX][0];

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {

			if (field[y][x][1] == 1) {
				if (field[y][x][0] == selectedNumber) {
					field[SelectedY][SelectedX][1] = 2;
					field[y][x][1] = 2;
				} else {
					HAL_Delay(1000);
					field[SelectedY][SelectedX][1] = 0;
					field[y][x][1] = 0;
				}
			}

		}
	}
}

char VerificarFimDeJogo(char size, char cardField[size][size][2]) {
	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			if (cardField[y][x][1] != 2)
				return 0;

	return 1;
}

void AtualizarTentativas(char mode) {

}

void AtualizarRecorde(int amounts) {
	if (amounts > record)
		record = amounts;
}

void ExibirFimDeJogo(void) {
	ST7789_Fill_Color(BLACK);
	ST7789_WriteString(AlignText(16, 10), 60, "YOU GANHOU", Font_16x26, WHITE,
			BLACK);

	for (int i = 0; i < 4; i++) {
		/*
		ST7789_DrawImage(95, 1530, 70, 70, saber_1);
		HAL_Delay(300);
		ST7789_DrawImage(95, 1530, 70, 70, saber_2);
		HAL_Delay(300);
		ST7789_DrawImage(95, 1530, 70, 70, saber_3);
		HAL_Delay(300);
		ST7789_DrawImage(95, 1530, 70, 70, saber_4);
		HAL_Delay(300);
		*/
	}
}
