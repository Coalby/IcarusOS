#pragma once

#include "handlers.h"
#include "system.h"
#include <kernel.h>

void keyboard_install();
void keyboard_handler(interruptFrame *frame);