# Minitalk

A simple client-server communication program using UNIX signals (`SIGUSR1` and `SIGUSR2`).

## About

Minitalk is a 42 school project where a client sends a string to a server, one bit at a time, using only UNIX signals. The server receives the bits, reconstructs the characters, and displays the message.

## How it works

### Client — Encoding

Each character is 8 bits. The client uses a bitmask starting at `1 << 7` (128) and shifts it right after each bit is sent. For each bit position, it performs a bitwise AND between the character and the mask:
- If the result matches the mask, the bit is `1` → send `SIGUSR1`
- Otherwise, the bit is `0` → send `SIGUSR2`

For example, the character `A` (ASCII 65 = `01000001`) is sent as:
```
SIGUSR2 SIGUSR1 SIGUSR2 SIGUSR2 SIGUSR2 SIGUSR2 SIGUSR2 SIGUSR1
   0       1       0       0       0       0       0       1
```

Before sending the string, the client also sends its length encoded as a 32-bit integer using the same bit-shifting technique, so the server knows how much memory to allocate.

### Server — Decoding

The server rebuilds each character bit by bit using left shifts. On each signal received:
- `SIGUSR1` → shift left and add 1 (`c = c << 1; c++`)
- `SIGUSR2` → shift left only (`c = c << 1`)

After 8 bits, the character is complete and stored in a buffer. Once a null character (`\0`) is received, the full message is printed.

### Synchronization

After processing each bit, the server sends `SIGUSR1` back to the client as an acknowledgment. The client waits for this signal before sending the next bit, ensuring no signals are lost.

## Usage

```
make
```

Start the server:
```
./server
```

The server will display its PID. Then in another terminal:
```
./client <server_pid> "your message here"
```
