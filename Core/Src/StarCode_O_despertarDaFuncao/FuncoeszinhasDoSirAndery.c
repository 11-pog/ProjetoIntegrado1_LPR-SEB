#include "FuncoeszinhasDoSirAndery.h"

void IniciarJogo(char diff, char mode) {
	const char Size = CalcSize(diff);

	char CardField[Size][Size][2];
	GerarParesAleatorios(Size, CardField);
	TestPrint(Size, CardField);

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
				cardField[Y][X][0] = (rand() % CalcPossibilities(fieldSize)) + 1; // aletoriza a carta em X, Y
				HAL_Delay(.1f); // Delay pra ver
			} while (ContainsVector2(fieldSize, cardField, cardField[Y][X][0])
					> 2);

			cardField[Y][X][1] = 0; // Atributo inicializado como 0
		}
	}
}

void NavegarCursor(void) {

}
void SelecionarCarta(void) {

}
void CompararPares(void) {

}
void VerificarFimDeJogo(void) {

}
void AtualizarTentativas(void) {

}
int AtualizarRecorde(void) {
	return 0;
}
void ExibirFimDeJogo(void) {

}
