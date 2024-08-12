#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
  (type *)allocateObject(sizeof(type), objectType)

// mimicking `Obj` "constructor"
static Obj *allocateObject(size_t size, ObjType type)
{
  Obj *object = (Obj *)reallocate(NULL, 0, size);
  object->type = type;
  // Insert the object as the new head for the list (for GC)
  object->next = vm.objects;
  vm.objects = object;
  return object;
}

static ObjString *allocateString(char *chars, int length)
{
  // Construct the new "instance" of `Obj` with type `ObjString`
  ObjString *string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  return string;
}

// Take ownership
ObjString *takeString(char *chars, int length)
{
  return allocateString(chars, length);
}

ObjString *copyString(const char *chars, int length)
{
  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocateString(heapChars, length);
}

void printObject(Value value)
{
  switch (OBJ_TYPE(value))
  {
  case OBJ_STRING:
    printf("%s", AS_CSTRING(value));
    break;
  }
}
