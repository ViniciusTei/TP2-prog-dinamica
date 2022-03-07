#include "../../includes/Colors.h"

void black () {
    printf("\033[0;30m");
}

void red () {
    printf("\033[38;2;255;0m");
}

void green() {
    printf("\033[0;32m");
}

void yellow () {
    printf("\033[38;2;252;255m");
}

void blue() {
    printf("\033[0;34m");
}

void purple() {
    printf("\033[38;2;60;0;141m");
}

void cyan() {
    printf("\033[0;36m");
}

void white() {
    printf("\033[0;37m");
}

void laranja() {
    printf("\033[38;2;252;127m");
}

void marrom() {
    printf("\033[38;2;45;18m");
}

void rosa() {
    printf("\033[38;2;255;0;230m");
}

void bgGray() {
  printf("\033[48;2;237;237;237m");
}

// Necessário resetar para cor original
void reset () {
    printf("\033[0m"); 
}

void clearScreen() {
  printf("\e[1;1H\e[2J");
}