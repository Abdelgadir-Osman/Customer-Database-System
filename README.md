# Customer Database

This project implements a simple customer and inventory management system in C++. It simulates a small retail environment where customers can purchase and return items, and where the store tracks its inventory and top customers by product type.

## Project Structure

* **`CustomerDB.cpp`**: Implements the `CustomerDB` class that manages dynamic storage of customers. Handles adding new customers, checking membership, and resizing the internal array.
* **`Project7.cpp`**: Contains the main program logic for processing purchases, returns, inventory updates, and summary reports. Also manages global inventory counts.
* **`metadata.yml`**: Contains configuration or metadata for project setup (not used directly in the program).

## Features

### Customer Management
* Automatically creates customer records when purchases occur
* Tracks the number of each item purchased by each customer
* Checks whether a customer exists in the database

### Inventory Tracking
* Maintains total counts for Books, Dice, Figures, and Towers
* Supports adding and returning items to inventory

### Transactions
* Handles purchase and return operations with proper validation
* Prevents transactions with negative or zero quantities
* Displays appropriate error messages for invalid actions

### Summary Reporting
* Prints total inventory and customer statistics
* Identifies the customer who has purchased the most of each item type

## Classes and Functions

### `Customer`
Represents a single customer record.

**Stores:**
* `books`
* `dice`
* `figures`
* `towers`
* `name`

### `CustomerDB`
Dynamic array-based customer database with:

* `operator[](UTString name)`: Accesses or adds a customer.
* `isMember(UTString name)`: Checks membership.
* Automatic capacity doubling when full.

### Main Functions in `Project7.cpp`
* `reset()`: Clears database and inventory.
* `processPurchase()`: Processes a customer purchase.
* `processReturn()`: Handles item returns.
* `processInventory()`: Updates total inventory quantities.
* `processSummarize()`: Prints summary statistics.

## Example Behavior

**Input**
Inventory Books 10 Purchase Alice Books 3 Purchase Bob Dice 5 Return Alice Books 1 Summarize


**Output**
There are 9 Books 5 Dice 0 Figures and 0 Towers in inventory we have had a total of 2 different customers Alice has purchased the most Books (2) Bob has purchased the most Dice (5) no one has purchased any Figures no one has purchased any Towers


## Compilation and Execution

You can compile and run the program using any standard C++ compiler:

```bash
g++ Project7.cpp CustomerDB.cpp -o project7
./project7 < input.txt
Replace input.txt with your test file if desired.
