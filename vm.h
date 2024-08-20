#ifndef clox_vm_h
#define clox_vm_h

#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (UINT8_COUNT * FRAMES_MAX)

typedef struct
{
  ObjFunction *function;
  // the caller stores its own instruction pointer
  uint8_t *ip;
  // points into the VM's value stack at the first slot this func can use
  Value *slots;
} CallFrame;

typedef struct
{
  CallFrame frames[FRAMES_MAX];
  int frameCount;

  Value stack[STACK_MAX];
  Value *stackTop;
  Table globals;
  Table strings;
  Obj *objects; // head of the list (for GC)
} VM;

typedef enum
{
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

#endif
