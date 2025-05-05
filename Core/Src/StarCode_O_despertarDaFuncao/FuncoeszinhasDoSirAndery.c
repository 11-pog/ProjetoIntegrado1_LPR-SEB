#include "FuncoeszinhasDoSirAndery.h"

void IniciarJogo(void) {

}
void GerarParesAleatorios(char fieldSize,
		char cardField[fieldSize][fieldSize][2]) {

	for (int i = 0; i < fieldSize; i++) {
		for (int j = 0; j < fieldSize; j++) {

			char random;
			do {
				random = rand() % fieldSize * fieldSize / 2;
				HAL_Delay(1);
			} while (ContainsVector2(fieldSize, cardField, random) >= 2);

			cardField[i][j][0] = random;
			cardField[i][j][1] = 0;
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
