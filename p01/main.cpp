#include "utility.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <string>

#include "Node.h"
// #include "List2.h"
#include "List1.h" // defines template List<T>

static void clear_line() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void print_roster(List<Personal_record> &roster) {
  // Fill in your code
  roster.traverse(print_record);
}

static void lookup_by_id(const List<Personal_record> &roster) {
  // Fill in your code
  // You might need to implement and use find_by_id in utility.h
  std::string id;
  std::cout << "Enter badge ID: ";
  std::cin >> id;
  clear_line();

  Personal_record result;
  if (find_by_id(roster, id, result)) {
    print_record(result);
  } else {
    std::cout << "Not found\n";
  }
}

static void lookup_by_name_prefix(const List<Personal_record> &roster) {
  // Fill in your code
  // You might need to implement and use find_all_by_name_prefix in utility.h
  std::string first, last;
  std::cout << "Enter first name prefix: ";
  std::cin >> first;
  std::cout << "Enter last name prefix: ";
  std::cin >> last;
  clear_line();

  int matches = find_all_by_name_prefix(roster, first, last, print_record);
  if (matches == 0) {
    std::cout << "Not found\n";
  }
}

static void menu() {
  std::cout << "\n=== Visitor Check-In & Badge Lookup ===\n"
            << "1) Import visitors from file\n"
            << "2) Print roster\n"
            << "3) Lookup by badge ID\n"
            << "4) Lookup by name (prefix)\n"
            << "5) Quit\n"
            << "Choice: ";
}

int main() {
  List<Personal_record> roster;

  while (true) {
    menu();

    int choice;
    if (!(std::cin >> choice)) {
      // EOF or invalid input
      return 0;
    }
    clear_line();

    switch (choice) {
    case 1: {
      // fill in your code to implement task 1
      Import_stats stats = import_file(roster, "data.txt");

      std::cout << "Inserted: " << stats.inserted
                << ", Discarded(DuplicateID): " << stats.duplicate_id
                << ", Discarded(DuplicateName): " << stats.duplicate_name
                << std::endl;
      break;
    }
    case 2:
      print_roster(roster); // Implement this function
      break;
    case 3:
      lookup_by_id(roster); // Implement this function
      break;
    case 4:
      lookup_by_name_prefix(roster); // Implement this function
      break;
    case 5:
      return 0;
    default:
      std::cout << "Invalid choice.\n";
      break;
    }
  }
}
