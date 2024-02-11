#pragma once

void disable_interrupts();
void enable_interrupts();

void ksegment_load();

void push_general_reg();
void pop_general_reg();