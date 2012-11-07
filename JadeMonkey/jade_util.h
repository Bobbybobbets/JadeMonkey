#pragma once

// macro for release the com objects (move to a utility file)
#define COM_RELEASE(X) {if ((X) != NULL) {(X)->Release(); (X) = NULL;}}

// macro for release allocated memory using malloc
#define FREE_MEMORY_MALLOC(X) {if ((X) != NULL) {free(X); (X) = NULL;}}

// macro for release allocated memory using malloc
#define DELETE_MEMORY_NEW(X) {if ((X) != NULL) {delete(X); (X) = NULL;}}