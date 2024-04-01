// Keyboard Implementation
#pragma once

#define MAX_BUFFER_SIZE 128

#include "handlers.h"
#include "system.h"
#include <kernel.h>

void keyboard_install();
void keyboard_handler(interruptFrame *frame);