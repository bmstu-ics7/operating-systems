#ifndef __STACK_H
#define __STACK_H

#include <stdlib.h>

#define STACK_SIZE 200

struct stack
{
    char *data[STACK_SIZE];
    int size;
};

struct stack *stack_create();
int stack_is_empty(struct stack *stack);
int stack_push(struct stack *stack, char *element);
const char *stack_pop(struct stack *stack);
void stack_free(struct stack **stack);

#endif /* __STACK_H */
