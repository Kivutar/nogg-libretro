#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <stdbool.h>
#include "libretro.h"
#include "rpng.h"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 240

retro_log_printf_t log_cb;
retro_video_refresh_t video_cb;
retro_audio_sample_t audio_cb;
retro_audio_sample_batch_t audio_batch_cb;
retro_environment_t environ_cb;
retro_input_poll_t input_poll_cb;
retro_input_state_t input_state_cb;

typedef struct surface_s
{
   uint32_t *image;
   unsigned w;
   unsigned h;
} surface_t;

typedef struct anim_s
{
   surface_t surface;
   int t;
   int p;
   int w;
   int h;
} anim_t;

typedef struct
{
   int up;
   int down;
   int left;
   int right;
   int start;
   int select;
   int a;
   int b;
   int x;
   int y;
} key_state_t;

typedef struct entity_s
{
   int type;
   int w;
   int h;
   int x;
   int y;
   int f;
   float vx;
   float vy;
   float t;
   bool  d;
   anim_t *anim;
   void (*update)(struct entity_s *);
   void (*draw)(struct entity_s *);
   void (*on_collide)(struct entity_s *, struct entity_s *, int dx, int dy);
   key_state_t *ks;
   uint32_t c;
} entity_t;

key_state_t ks1;
key_state_t ks2;

entity_t *p1;
entity_t *p2;

entity_t camera;

surface_t surface_new(char *name);
void draw_rect(int x, int y, int w, int h, uint32_t c);
void blit(int dest_x, int dest_y, int w, int h, int total_w, int total_h, uint32_t *data, int orig_x, int orig_y);
void blit_colored(int dest_x, int dest_y, int w, int h, int total_w, int total_h, uint32_t *data, int orig_x, int orig_y, uint32_t c);
void draw_image(int x, int y, int w, int h, uint32_t *data);
void draw_tile(int dest_x, int dest_y, int w, int h, int total_w, int total_h, uint32_t *data, int id);
void draw_tile_colored(int dest_x, int dest_y, int w, int h, int total_w, int total_h, uint32_t *data, int id, uint32_t c);
void draw_anim(int dest_x, int dest_y, anim_t* anim);
void draw_anim_colored(int dest_x, int dest_y, anim_t* anim, uint32_t c);
void add_entity(entity_t* ent);
void render_game();
void load_game();
void detect_collisions();
bool solid_at(int x, int y);

entity_t* map_new();
entity_t* pl_new();
entity_t* ground_new(int x, int y, int w, int h);

uint32_t fb[SCREEN_WIDTH * SCREEN_HEIGHT * 2];
size_t fbpitch;

extern int num_entities;
extern entity_t** entities;

#endif
