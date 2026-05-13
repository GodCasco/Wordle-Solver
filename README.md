# Wordle Solver

A simple command-line Wordle solver written in C. This is a small side project I built in my free time to practice C — nothing fancy, just a fun way to sharpen the basics.

## How it works

The program suggests a word to play, you type in the colors Wordle gave you back, and it narrows down the remaining possibilities until it finds the answer. It picks guesses based on letter frequency in the English language, favouring words with more common letters.

## Requirements

- A C compiler (gcc or clang)
- The `words.txt` file (included) must be in the same directory as the executable

## Build

```bash
gcc wordleSolver.c -o wordleSolver
```

## Usage

1. Run the program:
   ```bash
   ./wordleSolver
   ```

2. The program suggests a word — go type it in Wordle.

3. Enter the colors you got back, one character at a time, using:
   - `G` — Green (correct letter, correct position)
   - `Y` — Yellow (correct letter, wrong position)
   - `W` — White (letter not in the word)

   Example — if Wordle returned green, white, yellow, white, green:
   ```
   G W Y W G
   ```

4. The program will suggest the next word. Repeat until you win.

5. When all five letters are green, type `G G G G G` and the program will congratulate you.

## Limitations

The word list (`words.txt`) is static and was compiled at the time this project was made. If Wordle introduces new words after that date, the solver may not be able to find them and will give up early. Nothing to do about it — the list would just need to be updated manually.

## Example session

```
Use the word AUDIO

G W W Y W
Use the word STERN

W G W W G
Use the word ENTER

G G G G G
Congrats!!!
```