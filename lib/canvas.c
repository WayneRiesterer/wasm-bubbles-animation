#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CIRCLES 5000
#define CIRCLE_STRUCT_SIZE 6

struct Circle {
  int x;
  int y;
  int r;
  int cr;
  int cg;
  int cb;
};

struct CircleAnimation {
  int x;
  int y;
  int r;
  int xv;
  int yv;
  int xd;
  int yd;
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimation animation[NUM_CIRCLES];

/* JS Functions */
EM_JS(struct Circle *, render, (int dataLength, int circleStructSize),
      {render(dataLength, circleStructSize)})

int getRand(const int max) { return (rand() % max); }

int main() {
  srand(time(NULL));
  for (int i = 0; i < NUM_CIRCLES; i++) {
    int radius = getRand(10);
    int x = getRand(250);
    int y = getRand(250);

    animation[i].x = x;
    animation[i].y = y;
    animation[i].r = radius;
    animation[i].xv = getRand(10);
    animation[i].yv = getRand(10);
    animation[i].xd = 1;
    animation[i].yd = 1;

    circles[i].x = x + radius;
    circles[i].y = y + radius;
    circles[i].r = radius;
    circles[i].cr = getRand(255);
    circles[i].cg = getRand(255);
    circles[i].cb = getRand(255);
  }

  render(NUM_CIRCLES * CIRCLE_STRUCT_SIZE, CIRCLE_STRUCT_SIZE);
}

struct Circle *getCircles(int canvasWidth, int canvasHeight) {
  for (int i = 0; i < NUM_CIRCLES; i++) {
    if (animation[i].x + animation[i].r >= canvasWidth)
      animation[i].xd = 0;
    if (animation[i].x - animation[i].r <= 0)
      animation[i].xd = 1;
    if (animation[i].y + animation[i].r >= canvasHeight)
      animation[i].yd = 0;
    if (animation[i].y - animation[i].r <= 0)
      animation[i].yd = 1;

    if (animation[i].xd == 1)
      animation[i].x += animation[i].xv;
    else
      animation[i].x -= animation[i].xv;

    if (animation[i].yd == 1)
      animation[i].y += animation[i].yv;
    else
      animation[i].y -= animation[i].yv;

    circles[i].x = animation[i].x;
    circles[i].y = animation[i].y;
  }

  return circles;
}