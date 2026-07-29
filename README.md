# 📦 Shipestimator — Parcel Cost Calculator

A command-line parcel shipping cost calculator written in C. Shipestimator computes accurate shipping costs across multiple courier services, factoring in package dimensions, delivery zone, service tier, fragile handling, and promotional discounts.

## Features

- **Multi-courier support** — choose between 4 courier companies (FastShip, QuickPost, SpeedyCourier, GlobalExpress), each with its own domestic/international rate card
- **Dimensional weight calculation** — uses a volume-to-weight ratio so bulky-but-light packages are priced fairly, not just by actual weight
- **Zone-based pricing** — distance-based multipliers for local, regional, medium-range, and long-distance shipments
- **Service tiers** — normal vs. express delivery, with express carrying a surcharge
- **Fragile handling fee** — optional surcharge for fragile packages
- **Promotional discounts** — optional coupon-based discount applied to the final bill
- **Itemized invoice output** — a clear, formatted cost breakdown at the end of each run

## Tech Stack

- **Language:** C (C99/C11)
- **Compiler:** GCC / MinGW
- **Libraries:** `stdio.h`, `string.h` (standard library only — no external dependencies)

## Project Structure

```
shipestimator/
├── main.c        # Application source code
├── README.md     # This file
└── .gitignore
```

## Getting Started

### Prerequisites

You need a C compiler installed:

- **Linux/macOS:** GCC (usually pre-installed, or `sudo apt install gcc` / `brew install gcc`)
- **Windows:** [MinGW](http://www.mingw.org/) or use WSL

### Build

```bash
gcc -Wall -o shipestimator main.c
```

### Run

```bash
./shipestimator          # Linux/macOS
shipestimator.exe        # Windows
```

## How It Works

1. Displays a welcome banner
2. Collects package weight, dimensions, distance, delivery zone, service tier, fragile status, and discount eligibility
3. Lets you pick a courier from a rate-card menu
4. Calculates dimensional weight, applies zone multipliers, express/fragile surcharges, and discounts
5. Prints an itemized invoice with the final amount due

## Sample Output

```
****************************************
SHIPESTIMATOR: Parcel Cost Calculator
****************************************

Basic shipping cost: 5.00 kg x Rs4 = Rs20.00
Extra charge for express delivery: Rs10.00
Local delivery: No distance premium
Extra charge for fragile handling: Rs4.00

==========================================
 HERE IS YOUR FINAL BILL
==========================================
FINAL AMOUNT YOU NEED TO PAY: Rs34.00
```

## Possible Future Improvements

- Replace `scanf` string input with safer bounded reads (avoid buffer overflows on zone/service input)
- Move rate cards and constants into a config file
- Add unit tests for the calculation functions
- Support saving invoices to a file

## License

MIT
