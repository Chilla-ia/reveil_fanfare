#include "song.h"

Buzzer buzzer(14);
int i_note_song = 0;
int StarWarsNote[] = {
    NOTE_A3,
    NOTE_A3,
    NOTE_A3,
    NOTE_A3,
    NOTE_A3,
    NOTE_A3,
    NOTE_F3,
    NOTE_C4,
    NOTE_A3,
    NOTE_F3,
    NOTE_C4,
    NOTE_A3,
    NOTE_E4,
    NOTE_E4,
    NOTE_E4,
    NOTE_F4,
    NOTE_C4,
    NOTE_GS3,
    NOTE_F3,
    NOTE_C4,
    NOTE_A3,
    NOTE_A4,
    NOTE_A3,
    NOTE_A3,
    NOTE_A4,
    NOTE_GS4,
    NOTE_G4,
    NOTE_FS4,
    NOTE_E4,
    NOTE_F4,
    0,
    NOTE_AS3,
    NOTE_DS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_C4,
    NOTE_B3,
    NOTE_C4,
    0,
    NOTE_F3,
    NOTE_GS3,
    NOTE_F3,
    NOTE_A3,
    NOTE_C4,
    NOTE_A3,
    NOTE_C4,
    NOTE_E4,
    NOTE_A4,
    NOTE_A3,
    NOTE_A3,
    NOTE_A4,
    NOTE_GS4,
    NOTE_G4,
    NOTE_FS4,
    NOTE_E4,
    NOTE_F4,
    0,
    NOTE_AS3,
    NOTE_DS4,
    NOTE_D4,
    NOTE_CS4,
    NOTE_C4,
    NOTE_B3,
    NOTE_C4,
    0,
    NOTE_F3,
    NOTE_GS3,
    NOTE_F3,
    NOTE_C4,
    NOTE_A3,
    NOTE_F3,
    NOTE_C4,
    NOTE_A3};
int StarWarsRytm[] = {
    500, 500, 500, 375, 125, 500, 375, 125, 1000, 500, 500, 500, 375, 125, 500, 375, 125, 1000, 500, 375, 125, 500, 375, 125, 125, 125,
    250, 250, 250, 500, 375, 125, 125, 125, 250, 250, 250, 500, 375, 125, 500, 375, 125, 1000, 500, 375, 125, 500, 375, 125, 125, 125, 250,
    250, 250, 500, 375, 125, 125, 125, 250, 250, 250, 500, 375, 125, 500, 375, 125, 1000};

void starwars_song()
{
    Serial.println("Star Wars");
    if (i_note_song == 0)
    {
        buzzer.begin(10);
    }

    if (StarWarsNote[i_note_song] != sizeof(StarWarsNote))
    {
        buzzer.sound(StarWarsNote[i_note_song], StarWarsRytm[i_note_song]);
        ++i_note_song;
    }
    else
    {
        i_note_song = 0;
        buzzer.end(2000);
    }
}