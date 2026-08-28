# minitalk 📡

**minitalk** is a 42 School project focused on **inter-process communication**.

The goal is to create a communication system between a **client** and a **server** using only Unix signals.

## 🧠 Concepts

* Signals
* Process IDs (PID)
* Inter-Process Communication (IPC)
* Bit manipulation
* Signal handling
* `SIGUSR1`
* `SIGUSR2`

## ⚙️ How It Works

The **client** sends a message to the **server** one bit at a time using:

```text
SIGUSR1 → 0
SIGUSR2 → 1
```

The server receives the signals and rebuilds the original message.

```text
Client
  │
  │ SIGUSR1 / SIGUSR2
  ▼
Server
  │
  ▼
Message
```

## 🚀 Usage

Compile:

```bash
make
```

Start the server:

```bash
./server
```

The server displays its PID.

Send a message from the client:

```bash
./client <PID> "Hello World!"
```

Example:

```bash
./client 12345 "Hello from minitalk!"
```

## 🛠️ Technologies

* C
* Unix Signals
* Process IDs
* Bit Manipulation
* Inter-Process Communication
* Makefile

## 🎯 Goal

Learn how processes can communicate using **Unix signals** and understand how data can be transmitted **bit by bit**.
