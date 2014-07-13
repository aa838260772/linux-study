#ifndef _MAZE_H_
#define _MAZE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tagpos{
int s_x;
int s_y;
}Pos,*pPos;
typedef struct tagnode{
Pos  s_ps;
struct tagnode *s_next;
}NODE,*pNODE;

void stack_init(pNODE *);
void stack_push(pNODE *,Pos);
void stack_pop(pNODE *);
int stack_empty(pNODE *);
pNODE stack_top(pNODE );

void stack_reverse(pNODE *);
void stack_show(pNODE );
#endif
