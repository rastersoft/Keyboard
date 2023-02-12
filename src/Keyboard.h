/*
  Keyboard.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef KEYBOARD_h
#define KEYBOARD_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//================================================================================
//================================================================================
//  Keyboard

// Letters
#define KEY_A             0x8C
#define KEY_B             0x8D
#define KEY_C             0x8E
#define KEY_D             0x8F
#define KEY_E             0x90
#define KEY_F             0x91
#define KEY_G             0x92
#define KEY_H             0x93
#define KEY_I             0x94
#define KEY_J             0x95
#define KEY_K             0x96
#define KEY_L             0x97
#define KEY_M             0x98
#define KEY_N             0x99
#define KEY_O             0x9A
#define KEY_P             0x9B
#define KEY_Q             0x9C
#define KEY_R             0x9D
#define KEY_S             0x9E
#define KEY_T             0x9F
#define KEY_U             0xA0
#define KEY_V             0xA1
#define KEY_W             0xA2
#define KEY_X             0xA3
#define KEY_Y             0xA4
#define KEY_Z             0xA5

// Normal numbers
#define KEY_0             0xA6
#define KEY_1             0xA7
#define KEY_2             0xA8
#define KEY_3             0xA9
#define KEY_4             0xAA
#define KEY_5             0xAB
#define KEY_6             0xAC
#define KEY_7             0xAD
#define KEY_8             0xAE
#define KEY_9             0xAF

// Symbols
#define KEY_SPACE         0xCC
#define KEY_TILDE         0xBD
#define KEY_MINUS         0xB5
#define KEY_EQUAL         0xB6
#define KEY_LEFT_BRACE    0xB7
#define KEY_RIGHT_BRACE   0xB8
#define KEY_SEMICOLON     0xBB
#define KEY_QUOTE         0xBC
#define KEY_BACKSLASH     0xB9
#define KEY_NON_US_BS     0xEC
#define KEY_COMMA         0xBE
#define KEY_PERIOD        0xBF
#define KEY_SLASH         0xC0


// Modifiers
#define KEY_LEFT_CTRL     0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT      0x82
#define KEY_LEFT_GUI      0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT     0x86
#define KEY_RIGHT_GUI     0x87

// Misc keys
#define KEY_UP_ARROW      0xDA
#define KEY_DOWN_ARROW    0xD9
#define KEY_LEFT_ARROW    0xD8
#define KEY_RIGHT_ARROW   0xD7
#define KEY_BACKSPACE     0xB2
#define KEY_TAB           0xB3
#define KEY_RETURN        0xB0
#define KEY_MENU          0xED // "Keyboard Application" in USB standard
#define KEY_ESC           0xB1
#define KEY_INSERT        0xD1
#define KEY_DELETE        0xD4
#define KEY_PAGE_UP       0xD3
#define KEY_PAGE_DOWN     0xD6
#define KEY_HOME          0xD2
#define KEY_END           0xD5
#define KEY_CAPS_LOCK     0xC1
#define KEY_PRINT_SCREEN  0xCE // Print Screen / SysRq
#define KEY_SCROLL_LOCK   0xCF
#define KEY_PAUSE         0xD0 // Pause / Break

// Numeric keypad
#define KEY_NUM_LOCK      0xDB
#define KEY_KP_SLASH      0xDC
#define KEY_KP_ASTERISK   0xDD
#define KEY_KP_MINUS      0xDE
#define KEY_KP_PLUS       0xDF
#define KEY_KP_ENTER      0xE0
#define KEY_KP_1          0xE1
#define KEY_KP_2          0xE2
#define KEY_KP_3          0xE3
#define KEY_KP_4          0xE4
#define KEY_KP_5          0xE5
#define KEY_KP_6          0xE6
#define KEY_KP_7          0xE7
#define KEY_KP_8          0xE8
#define KEY_KP_9          0xE9
#define KEY_KP_0          0xEA
#define KEY_KP_DOT        0xEB

// Function keys
#define KEY_F1            0xC2
#define KEY_F2            0xC3
#define KEY_F3            0xC4
#define KEY_F4            0xC5
#define KEY_F5            0xC6
#define KEY_F6            0xC7
#define KEY_F7            0xC8
#define KEY_F8            0xC9
#define KEY_F9            0xCA
#define KEY_F10           0xCB
#define KEY_F11           0xCC
#define KEY_F12           0xCD
#define KEY_F13           0xF0
#define KEY_F14           0xF1
#define KEY_F15           0xF2
#define KEY_F16           0xF3
#define KEY_F17           0xF4
#define KEY_F18           0xF5
#define KEY_F19           0xF6
#define KEY_F20           0xF7
#define KEY_F21           0xF8
#define KEY_F22           0xF9
#define KEY_F23           0xFA
#define KEY_F24           0xFB

// Multimedia keys
#define KEY_MEDIA_MUTE    0x88
#define KEY_MEDIA_VOL_INC 0x89
#define KEY_MEDIA_VOL_DEC 0x8A

// Supported keyboard layouts
extern const uint8_t KeyboardLayout_de_DE[];
extern const uint8_t KeyboardLayout_en_US[];
extern const uint8_t KeyboardLayout_es_ES[];
extern const uint8_t KeyboardLayout_fr_FR[];
extern const uint8_t KeyboardLayout_it_IT[];
extern const uint8_t KeyboardLayout_sv_SE[];
extern const uint8_t KeyboardLayout_da_DK[];

// Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class Keyboard_ : public Print
{
private:
  KeyReport _keyReport;
  const uint8_t *_asciimap;
  void sendReport(KeyReport* keys);
public:
  Keyboard_(void);
  void begin(const uint8_t *layout = KeyboardLayout_en_US);
  void end(void);
  size_t write(uint8_t k);
  size_t write(const uint8_t *buffer, size_t size);
  size_t press(uint8_t k);
  size_t release(uint8_t k);
  void releaseAll(void);
};
extern Keyboard_ Keyboard;

#endif
#endif
