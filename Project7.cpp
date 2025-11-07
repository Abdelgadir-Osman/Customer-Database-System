
#include "Customer.h"
#include "CustomerDB.h"
#include "UTString.h"
#include <iostream>
#include <stdio.h>

void readString(UTString &);
void readNum(int &);

CustomerDB database;

int num_books = 0;
int num_dice = 0;
int num_figures = 0;
int num_towers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
  database.clear();
  num_books = 0;
  num_dice = 0;
  num_figures = 0;
  num_towers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Books", "Dice", "Figures" or "Towers"
 * for example the expression *selectInventItem("Books") returns the
 * current global variable for the number of books in the inventory
 */
int *selectInventItem(UTString word) {
  if (word == "Books") {
    return &num_books;
  } else if (word == "Dice") {
    return &num_dice;
  } else if (word == "Figures") {
    return &num_figures;
  } else if (word == "Towers") {
    return &num_towers;
  }

  /* NOT REACHED */
  return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above,
 * however this overload takes a Customer as a second argument and selects the
 * data member of that Customer that matches "word". The function returns a
 * pointer to one of the three data members from the specified customer.
 */
int *selectInventItem(UTString word, Customer &cust) {
  if (word == "Books") {
    return &cust.books;
  } else if (word == "Dice") {
    return &cust.dice;
  } else if (word == "Figures") {
    return &cust.figures;
  } else if (word == "Towers") {
    return &cust.towers;
  }

  /* NOT REACHED */
  return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Books", "Dice", "Figures" or "Towers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that
 * item type then findMax returns the first Customer in the CustomerDB who has
 * purchased that maximal quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in
 * the CustomerDB, fundMax returns a null pointer (0)
 */
Customer *findMax(UTString type) {
  Customer *result = 0;
  int max = 0;
  for (int k = 0; k < database.size(); k += 1) {
    Customer &cust = database[k];
    int *p = selectInventItem(type, cust);
    if (*p > max) {
      max = *p;
      result = &cust;
    }
  }

  return result;
}

void processPurchase() {
  UTString Name;
  UTString Item;
  int Quantity;

  // Read the customer's name, item type, and quantity from input
  readString(Name);
  readString(Item);
  readNum(Quantity);

  // ignore if negative or 0
  if (Quantity <= 0) {
      return;
  }

  // inventory item ptr
  int* inventoryItem = selectInventItem(Item);

  // Check if the item type is valid and if there is enough inventory
  if (inventoryItem != nullptr) {
      if (*inventoryItem >= Quantity) {
          // decrease quantity from inventory
          *inventoryItem -= Quantity;

          // add customer or update existing customer
          Customer& customer = database[Name];

          // update record
          int* customerItem = selectInventItem(Item, customer);
          if (customerItem != nullptr) {
              *customerItem += Quantity;
          }
      } else {
          // not enough inventory
          std::cout << "Sorry " << Name.c_str() << ", we only have " << *inventoryItem
                    << " " << Item.c_str() << std::endl;
      }
  }
}

void processReturn() {
  UTString Name;
  UTString Item;
  int Quantity;

  // read name item type from input
  readString(Name);
  readString(Item);
  readNum(Quantity);

  // ignore if negative or 0
  if (Quantity <= 0) {
      return;
  }

  // ignore if doesn't exist
  if (!database.isMember(Name)) {
      std::cout << "Sorry " << Name.c_str() << ", we do not have you in our database" << std::endl;
      return;
  }

  // get record
  Customer& customer = database[Name];

  // ptr to item from record
  int* customerItem = selectInventItem(Item, customer);

  // check item and quantity
  if (customerItem != nullptr) {
      if (*customerItem >= Quantity) {
          // deduct item quantity from record
          *customerItem -= Quantity;

          // add back to inventory
          int* inventoryItem = selectInventItem(Item);
          if (inventoryItem != nullptr) {
              *inventoryItem += Quantity;
          }
      } else {
          std::cout << Name.c_str() << ", you do not have " << Quantity
                    << " " << Item.c_str() << std::endl;
      }
  }
}

void processSummarize() {
  // inventory summary
  std::cout << "There are " << num_books << " Books " 
            << num_dice << " Dice " 
            << num_figures << " Figures and " 
            << num_towers << " Towers in inventory" << std::endl;

  // number of customers
  std::cout << "we have had a total of " << database.size() << " different customers" << std::endl;

  // who purchased the most of each item 
  UTString itemTypes[] = {"Books", "Dice", "Figures", "Towers"};
  for (int i = 0; i < 4; i++) {
      Customer* maxCustomer = findMax(itemTypes[i]);
      if (maxCustomer != nullptr) {
          int* maxItem = selectInventItem(itemTypes[i], *maxCustomer);
          std::cout << maxCustomer->name.c_str() << " has purchased the most " 
                    << itemTypes[i].c_str() << " (" << *maxItem << ")" << std::endl;
      } else {
          std::cout << "no one has purchased any " << itemTypes[i].c_str() << std::endl;
      }
  }
}

void processInventory() {
  UTString Item;
  int Quantity;

  // get type and quantity from input
  readString(Item);
  readNum(Quantity);

  // update inventory
  int* inventoryItem = selectInventItem(Item);
  if (inventoryItem != nullptr) {
      *inventoryItem += Quantity;
  }
}
