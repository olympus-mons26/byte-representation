# 8-Bit Binary LED Display

An Arduino UNO project that displays an 8-bit binary number using eight LEDs. Enter a binary number through the Serial Monitor, and the Arduino will turn the corresponding LEDs ON or OFF and print the decimal equivalent.

## Features

- Displays one byte (8 bits) using eight LEDs.
- Accepts binary input through the Serial Monitor.
- Ignores whitespace in the input, so `0101 0101` is accepted.
- Validates that the input contains exactly eight binary digits.
- Rejects characters other than `0` and `1`.
- Calculates and prints the decimal value of the entered binary number.
- Saves the most recently entered byte to the Arduino's EEPROM.
- Restores the saved byte to the LEDs and prints it in the Serial Monitor after a restart or reconnection.

## Components Required

- Arduino UNO (or a compatible Arduino board)
- 8 LEDs
- 8 current-limiting resistors (typically 220 Ω to 330 Ω)
- Breadboard
- Jumper wires
- USB cable for programming and Serial Monitor communication

> **Safety note:** Use a current-limiting resistor in series with each LED. Connect each LED's cathode to GND and its anode through a resistor to its assigned Arduino pin.

## Connections

| Component           | Component Pin | Arduino UNO Pin |
| ------------------- | ------------- | --------------- |
| LED 1 (MSB)         | Anode (+), through resistor | D2 |
|                     | Cathode (-)   | GND             |
| LED 2               | Anode (+), through resistor | D3 |
|                     | Cathode (-)   | GND             |
| LED 3               | Anode (+), through resistor | D4 |
|                     | Cathode (-)   | GND             |
| LED 4               | Anode (+), through resistor | D5 |
|                     | Cathode (-)   | GND             |
| LED 5               | Anode (+), through resistor | D6 |
|                     | Cathode (-)   | GND             |
| LED 6               | Anode (+), through resistor | D7 |
|                     | Cathode (-)   | GND             |
| LED 7               | Anode (+), through resistor | D8 |
|                     | Cathode (-)   | GND             |
| LED 8 (LSB)          | Anode (+), through resistor | D9 |
|                     | Cathode (-)   | GND             |

Each LED is controlled independently. A binary `1` turns its LED ON; a binary `0` turns it OFF. The first input bit (most significant bit) is shown by LED 1 on D2, and the last input bit (least significant bit) is shown by LED 8 on D9.

No extra components or wiring are needed for memory: EEPROM is built into the Arduino UNO.

## How to Use

1. Connect the circuit according to the connections table.
2. Open the sketch in the Arduino IDE.
3. Select your board and port from **Tools**.
4. Upload the sketch to the Arduino.
5. Open **Tools → Serial Monitor**.
6. Set the baud rate to **9600**.
7. Select **Newline** as the line ending.
8. Enter exactly eight binary digits and press Enter. Spaces are ignored, so `0101 0101` is also accepted.

When a valid sequence is entered, the sketch updates the LEDs, saves the byte to EEPROM, and prints its binary and decimal values. After restarting or reconnecting the Arduino, the last saved sequence is restored to the LEDs and printed in the Serial Monitor.

### Example

Input:

```text
0101 0101
```

The spaces are ignored, so the Arduino processes:

```text
01010101
```

Output:

```text
Binary: 01010101
Decimal: 85
```

On a later startup after a sequence has been saved, the Serial Monitor also prints:

```text
Previous sequence restored!
Binary: 01010101
Decimal: 85
```

If no sequence has been saved yet, the sketch starts with all LEDs off and waits for input.

## EEPROM Memory

The sketch stores the entered 8-bit value as one byte in the Arduino's EEPROM and uses a marker to determine whether a saved value is available. EEPROM retains its contents when the Arduino is disconnected or powered off, so the latest valid sequence is restored on the next startup. `EEPROM.update()` avoids writing a value when the stored byte is already the same. EEPROM has a limited write endurance (typically about 100,000 writes per location), so avoid continuously resending the same input unnecessarily.

## Binary-to-Decimal Conversion

The sketch calculates the decimal value from left to right. For each bit, it doubles the value accumulated so far and adds the current bit:

```cpp
decimalValue = decimalValue * 2 + (binary[i] - '0');
```

For example, `01010101` is:

```text
0 × 128 + 1 × 64 + 0 × 32 + 1 × 16 + 0 × 8 + 1 × 4 + 0 × 2 + 1 × 1 = 85
```

The LEDs display the entered bits in the same left-to-right order.

## Troubleshooting

- **No output:** Check that the Serial Monitor baud rate is set to `9600`.
- **No previous sequence is restored:** Enter a valid 8-bit sequence first; invalid input is not saved.
- **Input is rejected:** Enter exactly eight `0` or `1` characters. Spaces are allowed.
- **LEDs do not light:** Check LED polarity, resistor connections, and the selected Arduino pins.
- **Input is not processed as expected:** Set the Serial Monitor line ending to **Newline**.

## License

This project is licensed under the MIT License. See the [`LICENSE`](LICENSE) file for the full license text.

***

Made by Baljit Panda ([olympus-mons26](https://olympus-mons26/byte-representation)).
