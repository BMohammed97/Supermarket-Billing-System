# Supermarket Billing & Invoice System in C

This project is a high-performance **C program** designed to parse large tabular sales log files and dynamically structure them into beautifully formatted, professional customer invoices.

## 🚀 Features
- **Efficient Fixed-Width Parsing:** Extracts structured data fields (Receipt Code, Customer Name, Product, Date, Qty, Price) directly from text buffers using customized parsing logic.
- **Data Integrity Verification:** Automatically calculates and verifies total item prices (`Qty * Unit_Price`) for every processed line.
- **Control-Loop Grouping:** Implements smart nested loops to group consecutive product records belonging to the same `Receipt_Code` into a unified layout.
- **Professional Formatting:** Outputs a clean, receipt-like view inside `SalesWriteBons.txt` with formatted headers, item alignments, and accumulated final totals.

## 🛠️ Technical Overview
- **Language:** C (C99/C11 standard)
- **Concepts Used:** File I/O (`fopen`, `fgets`, `fprintf`), Structures (`typedef struct`), String Manipulation (`strcmp`, `strcpy`, `snprintf`), Parsing algorithms.
- **Optimization:** Fixed-width memory offsets ensuring minimal CPU and memory footprint, ideal for embedded and low-level resource management systems.

## 📂 Project Structure
- `main.c` - The core program containing the fixed-width parser and invoice engine.
- `sales.txt` - Raw input log database containing bulk daily sales transactions.
- `SalesWriteBons.txt` - The finalized output report containing structured customer receipts.
