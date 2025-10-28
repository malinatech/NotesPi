#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "notes.h"
#define SPEAKER_PIN 1 // wiringPi pin 16 (GPIO23)


void beep(int freq, int duration_ms) {
    int delay_us = 1000000 / (freq * 2);
    int cycles = (freq * duration_ms) / 1000;
    for (int i = 0; i < cycles; i++) {
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delay_us);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delay_us);
    }
}

int note_to_freq(const char* note) {
    #define CHECK(note_str) if(strcmp(note, #note_str)==0) return note_str;
    CHECK(C0) CHECK(Cs0) CHECK(D0) CHECK(Ds0) CHECK(E0) CHECK(F0) CHECK(Fs0) CHECK(G0) CHECK(Gs0) CHECK(A0) CHECK(As0) CHECK(B0)
    CHECK(C1) CHECK(Cs1) CHECK(D1) CHECK(Ds1) CHECK(E1) CHECK(F1) CHECK(Fs1) CHECK(G1) CHECK(Gs1) CHECK(A1) CHECK(As1) CHECK(B1)
    CHECK(C2) CHECK(Cs2) CHECK(D2) CHECK(Ds2) CHECK(E2) CHECK(F2) CHECK(Fs2) CHECK(G2) CHECK(Gs2) CHECK(A2) CHECK(As2) CHECK(B2)
    CHECK(C3) CHECK(Cs3) CHECK(D3) CHECK(Ds3) CHECK(E3) CHECK(F3) CHECK(Fs3) CHECK(G3) CHECK(Gs3) CHECK(A3) CHECK(As3) CHECK(B3)
    CHECK(C4) CHECK(Cs4) CHECK(D4) CHECK(Ds4) CHECK(E4) CHECK(F4) CHECK(Fs4) CHECK(G4) CHECK(Gs4) CHECK(A4) CHECK(As4) CHECK(B4)
    CHECK(C5) CHECK(Cs5) CHECK(D5) CHECK(Ds5) CHECK(E5) CHECK(F5) CHECK(Fs5) CHECK(G5) CHECK(Gs5) CHECK(A5) CHECK(As5) CHECK(B5)
    CHECK(C6) CHECK(Cs6) CHECK(D6) CHECK(Ds6) CHECK(E6) CHECK(F6) CHECK(Fs6) CHECK(G6) CHECK(Gs6) CHECK(A6) CHECK(As6) CHECK(B6)
    CHECK(C7) CHECK(Cs7) CHECK(D7) CHECK(Ds7) CHECK(E7) CHECK(F7) CHECK(Fs7) CHECK(G7) CHECK(Gs7) CHECK(A7) CHECK(As7) CHECK(B7)
    CHECK(C8) CHECK(Cs8) CHECK(D8) CHECK(Ds8)
    #undef CHECK
    return 0; 
}

int main(int argc, char *argv[]) {

    if (argc < 2) { 
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1; 
    }
    
    printf("Output file: %s\n", argv[1]);  // Ispravan način za ispis naziva fajla

    wiringPiSetup();
    pinMode(SPEAKER_PIN, OUTPUT);
    FILE *file = fopen(argv[1], "r");  // Koristi argv[1] za naziv fajla
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char note[4];
    int duration;
    while (fscanf(file, "%3s %d", note, &duration) == 2) {
        int freq = note_to_freq(note);
        if (freq > 0) {
            beep(freq, duration);
        }
    }

    fclose(file);
    return 0;
}
