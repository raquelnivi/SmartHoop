#ifndef IMAGES_H_
#define IMAGES_H_

#include "images\abstract_diamonds_green.h"
#include "images\abstract_diamonds_pink.h"
#include "images\abstract_psychedelic_rbw.h"
#include "images\abstract_psychedelic_trip.h"
#include "images\afghan.h"
#include "images\aztec_rainbow_24px.h"
#include "images\bampow.h"
#include "images\blackstar.h"
#include "images\blossom1.h"
#include "images\burst_bright_purple.h"
#include "images\burst_fire_circle_.h"
#include "images\burst_flower_rbw.h"
#include "images\burst_psychedelic_1.h"
#include "images\burst_psychedelic_2.h"
#include "images\burst_psychedelic_rbw.h"
#include "images\burst_psychedelic_solid.h"
#include "images\burst_stars.h"
#include "images\burst_trippy_crosses.h"
#include "images\catrainbow.h"
#include "images\chase_fast_comets.h"

const uint8_t* const images[] PROGMEM {
	abstract_diamonds_green,
	abstract_diamonds_pink,
	abstract_psychedelic_rbw,
	abstract_psychedelic_trip,
	afghan,
	aztec_rainbow_24px,
	bampow,
	blackstar,
	blossom1,
	burst_bright_purple,
	burst_fire_circle_,
	burst_flower_rbw,
	burst_psychedelic_1,
	burst_psychedelic_2,
	burst_psychedelic_rbw,
	burst_psychedelic_solid,
	burst_stars,
	burst_trippy_crosses,
	catrainbow,
	chase_fast_comets
};

#define NUM_IMAGES (sizeof(images) / sizeof(images[0]))

#endif