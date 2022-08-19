#  GNU C library's (glibc's) malloc library implementation
```c
void  *malloc(size_t size);
```
```c
void  free(void *ptr);
```
```c
void  *realloc(void *ptr, size_t size);
```
```c
void  *calloc(size_t nelem, size_t size);
```
```c
void  show_alloc_mem();
```
```c
void  show_free_mem();
```

## Injection
The project comes with an injector (LD_PRELOAD hooking)
- Running a binary using the inject script will make the program use my malloc library instead of the glibc's one
```
./inject [BINARY]
```

## Make
Given Makefile contains all standard rules
- all
- clean
- fclean
- re

## Demo
![malloc demo](demo.gif)
