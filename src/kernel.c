#include "kernel.h"
#include <stddef.h>
#include <stdint.h>

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

// Create a coloured character 
uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

// Display a character on the screen
void terminal_put_char(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

// Writes character to the screen offset by the last
void terminal_write_char(char c, char colour)
{
    if (c == '\n')
    {
        terminal_col = 0;
        terminal_row += 1;
        return;
    }

    terminal_put_char(terminal_col, terminal_row, c, colour);
    terminal_col += 1;

    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

// Function to clear the screen
void terminal_initialise()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_put_char(x, y, ' ', 0);
        }
    }
}

// Get length of a string
size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
    {
        len++;
    }

    return len;
}

// Prints a string
void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_write_char(str[i], 15);
    }
}

// Main method
void kernel_main()
{
    terminal_initialise();
    print("Hello, World!\n");
}