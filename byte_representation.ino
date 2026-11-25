#include <EEPROM.h>

int ledPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup()
{
    Serial.begin(9600);
    Serial.setTimeout(100);

    for (int i = 0; i < 8; i++)
    {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }

    Serial.println("==================================");
    Serial.println("8-BIT (1 BYTE) BINARY LED DISPLAY");
    Serial.println("==================================");
    Serial.println("Enter 8 bits. Spaces are ignored.");
    Serial.println("Example: 0101 0101");

    // Restore previous sequence from EEPROM
    if (EEPROM.read(1) == 123)
    {
        byte savedValue = EEPROM.read(0);

        String binary = "";

        for (int i = 7; i >= 0; i--)
        {
            binary += bitRead(savedValue, i) ? '1' : '0';
        }

        for (int i = 0; i < 8; i++)
        {
            digitalWrite(ledPins[i],
                         binary[i] == '1' ? HIGH : LOW);
        }

        Serial.println("----------------------------");
        Serial.println("Previous sequence restored!");

        Serial.print("Binary: ");
        Serial.println(binary);

        Serial.print("Decimal: ");
        Serial.println(savedValue);
        Serial.println("----------------------------");
    }
}

void loop()
{

    if (Serial.available() > 0)
    {

        String input = Serial.readStringUntil('\n');
        String binary = "";

        // Remove all whitespace characters
        for (int i = 0; i < input.length(); i++)
        {
            if (!isspace(input[i]))
            {
                binary += input[i];
            }
        }

        if (binary.length() != 8)
        {
            Serial.println("ERROR: Enter exactly 8 binary digits!");
            return;
        }

        bool valid = true;
        int decimalValue = 0;

        for (int i = 0; i < 8; i++)
        {

            if (binary[i] != '0' && binary[i] != '1')
            {
                valid = false;
                break;
            }

            decimalValue = decimalValue * 2 + (binary[i] - '0');
        }

        if (!valid)
        {
            Serial.println("ERROR: Only 0 and 1 allowed!");
            return;
        }

        // Update all 8 LEDs
        for (int i = 0; i < 8; i++)
        {
            digitalWrite(ledPins[i],
                         binary[i] == '1' ? HIGH : LOW);
        }

        // Save sequence in EEPROM
        EEPROM.update(0, decimalValue);
        EEPROM.update(1, 123);

        Serial.println("----------------------------");
        Serial.print("Binary: ");
        Serial.println(binary);

        Serial.print("Decimal: ");
        Serial.println(decimalValue);
        Serial.println("----------------------------");
    }
}