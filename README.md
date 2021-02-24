# Attempt to Fetch GTK3 Clipboard Rich Text
Attempt to Fetch GTK3 Clipboard Rich Text **But Failed**.

## Environment
- Ubuntu 20.04

## Build and Run
cmake or gcc.

gcc:
```bash
gcc main.c -o main `pkg-config --libs --cflags gtk+-3.0`
```


