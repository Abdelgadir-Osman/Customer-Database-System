
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) { // done, please do not edit
    this->books = 0;
    this->dice = 0;
    this->figures = 0;
    this->towers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) { // not done, your effort goes here
// check if name exists
for (int i = 0; i < this->length; i++) {
    if (this->data[i].name == name) {
        return this->data[i]; // return existing customer
    }
}


if (this->length == this->capacity) { //if full
    // Double the capacity and replace data
    this->capacity *= 2;
    Customer* newData = new Customer[this->capacity];
    for (int i = 0; i < this->length; i++) {
        newData[i] = this->data[i];
    }
    delete[] this->data;
    this->data = newData;
}

// add new customer
this->data[this->length] = Customer(name);
return this->data[this->length++]; // return new customer and increment length
}

bool CustomerDB::isMember(UTString name) { 
// go through array
 for (int i = 0; i < this->length; i++) {
    if (this->data[i].name == name) {
        return true; // found
    }
}
return false; //not found
}
