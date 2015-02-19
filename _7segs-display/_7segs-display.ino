/*
    Count from 0 to 9999 on a 4-digits 7-segments display.

    This is for a common cathode display. For common anode, invert digitalWrite calls (HIGH <-> LOW).
    If you have less digits, change NUM_DIGITS and MAX_NUMBER.

    Created 18 Feb 2015
    by Jean-Christophe Lariviere
*/

#define NUM_SEGMENTS 8
#define NUM_DIGITS 4
#define MAX_NUMBER 9999

// Since the display is multiplexed, we need to turn the digits on and off very quickly.
// This defines the "on" time of a digit before switching to the next (in milliseconds).
#define DELAY_BETWEEN_DIGITS 3

// Change these to fit your setup
int segPins[] = {12, 11, 10, 9, 8, 7, 6, 5};
int digitPins[] = {1, 2, 3, 4};

char* numberSegments[] = {
    "11111100", // 0
    "01100000", // 1
    "11011010", // 2
    "11110010", // 3
    "01100110", // 4
    "10110110", // 5
    "10111110", // 6
    "11100100", // 7
    "11111110", // 8
    "11110110"  // 9
};


void setup()
{
    for (int i = 0; i < NUM_SEGMENTS; i++)
    {
        pinMode(segPins[i], OUTPUT);
    }

    for (int i = 0; i < NUM_DIGITS; i++)
    {
        pinMode(digitPins[i], OUTPUT);
        digitalWrite(digitPins[i], HIGH); // off
    }
}

int num = 0;

void loop()
{
    displayNumber(num);

    num++;
    num %= (MAX_NUMBER + 1);
}

void displayNumber(int number)
{
    // Most significant digit first, iterate on the number of digits of the number (to show 42 instead of 0042)
    for (int i = numberOfDigits(number) - 1; i >= 0; i--)
    {
        int currentDigit = number / pow(10, i);
        displayDigit(digitPins[i], currentDigit);

        number -= pow(10, i) * currentDigit;
    }
}

int numberOfDigits(int number)
{
    return
        (number < 10 ? 1 :
        (number < 100 ? 2 :
        (number < 1000 ? 3 :
        4)));
}

void displayDigit(int digitPin, int number)
{
    prepareSegsForNumber(number);

    digitalWrite(digitPin, LOW);
    delay(DELAY_BETWEEN_DIGITS);
    digitalWrite(digitPin, HIGH);
}

void prepareSegsForNumber(int number)
{
    char* segments = numberSegments[number];

    for (int i = 0; i < NUM_SEGMENTS; i++)
    {
        digitalWrite(segPins[i], segments[i] == '0' ? LOW : HIGH);
    }
}

