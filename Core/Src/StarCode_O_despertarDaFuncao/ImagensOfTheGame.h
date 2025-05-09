#ifndef _THRONE_IMAGE_H
#define _THRONE_IMAGE_H

#include <stdint.h>

#define CARD_HEIGHT 30
#define CARD_WIDTH 21

extern const uint16_t CardBackemon[][CARD_WIDTH*CARD_HEIGHT/2];
extern const uint16_t SelectedCard[][CARD_WIDTH*CARD_HEIGHT/2];

#define SABER_HEIGHT 60
#define SABER_WIDTH 60

extern const uint16_t saber_1[][SABER_HEIGHT*SABER_WIDTH/2];
extern const uint16_t saber_2[][SABER_HEIGHT*SABER_WIDTH/2];
extern const uint16_t saber_3[][SABER_HEIGHT*SABER_WIDTH/2];
extern const uint16_t saber_4[][SABER_HEIGHT*SABER_WIDTH/2];

#endif
