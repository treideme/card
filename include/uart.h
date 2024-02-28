/*
 * Copyright 2024 Thomas Reidemeister
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * Utility functions for UART processing.
 * @file uart.h
 * @author Thomas Reidemeister
 */
#ifndef _uart_h_
#define _uart_h_

#include <msp430.h>

extern char *uart_last_out_ptr;
extern char uart_last_in;

void uart_init();
void uart_send(const char*s);

#endif // _hardware_h_
