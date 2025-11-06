# CSC139 – Synchronization Project (Fall 2025)

This project is a simulation of a **multi-threaded web server** designed to demonstrate synchronization techniques in C using **mutex locks**, **condition variables**, and **semaphores**.

It was developed as part of **CSC 139 (Operating Systems)** to explore the classic **Producer–Consumer Problem** using POSIX threads.

---

## 🧠 Overview

The simulation represents a simplified web server where:
- The **Producer thread** simulates incoming HTTPS requests and adds them to a **shared buffer (server queue)**.
- The **Consumer thread** simulates the web server processing those requests by removing them from the buffer.
- A **shared circular buffer** is used as the common resource between threads.
- Synchronization ensures that multiple threads access the buffer safely without race conditions.

Three different synchronization mechanisms are implemented:

| Sync Type | Mechanism | Description |
|------------|------------|-------------|
| **1** | Mutex | Provides basic mutual exclusion for buffer access. No blocking/waiting behavior. |
| **2** | Condition Variables | Adds smarter waiting — producer sleeps when buffer is full, consumer sleeps when buffer is empty. |
| **3** | Semaphores | Uses counting semaphores to manage full/empty slots — efficient and structured synchronization. |

---

## ⚙️ Compilation

gcc main.c buffer.c producer.c consumer.c -o server -lpthread

## 🚀 How to Run

./server 1  {number of requests} # Run using Mutex locks
./server 2  {number of requests} # Run using Condition Variables
./server 3  {number of requests} # Run using Semaphores


## 🧩 Example Output

Using Semaphores Synchronization...
Semaphore produced request #1
Semaphore consumed request #1
Semaphore produced request #2
Semaphore consumed request #2
Finished successfully.


## 🧵 How It Works
```
- The producer thread generates a given number of requests and inserts them into the shared buffer.

- The consumer thread removes those requests one at a time.

- The buffer operations (insert_request() and remove_request()) are implemented in buffer.c.

- Each synchronization type controls access to the buffer differently, demonstrating how synchronization affects concurrency.

```