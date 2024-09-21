#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef Library
#define Library __declspec(dllexport)
#else
#define Library __declspec(dllimport)
#endif


extern "C" Library uint64_t des(uint64_t input, uint64_t key, char mode);