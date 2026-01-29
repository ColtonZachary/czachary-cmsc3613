#include "utility.h"

#include <fstream>
#include <iostream>

#include "Node.h"
// #include "List2.h"
#include "List1.h" // defines template List<T>

bool same_id(const Personal_record &a,
             const Personal_record &b) { // comparison helper
  return a.ID == b.ID;
}

bool same_person(const Personal_record &a,
                 const Personal_record &b) { // comparison helper
  return a.first_name == b.first_name && a.last_name == b.last_name;
}

bool comes_before(const Personal_record &a, const Personal_record &b) {
  // Fill in your code to support sorting the records by last_name, then
  // first_name, then ID for deterministic ordering.
  if (a.last_name != b.last_name)
    return a.last_name < b.last_name;

  if (a.first_name != b.first_name)
    return a.first_name < b.first_name;

  return a.ID < b.ID;
}

void print_record(Personal_record &r) {
  // Fill in your code to print a Personal_record
  std::cout << "Last Name: " << r.last_name << std::endl;
  std::cout << "First Name: " << r.first_name << std::endl;
  std::cout << "ID: " << r.ID << std::endl;
}

Import_stats import_file(List<Personal_record> &roster,
                         const std::string &filename) {
  Import_stats stats;
  // Fill in your code to support file import for Task 1 in p01
  std::ifstream file(filename);
  if (!file)
    return stats;

  Personal_record r;

  while (file >> r.first_name >> r.last_name >> r.ID) {
    // Check duplicate ID
    bool dupID = false;
    for (int i = 0; i < roster.size(); i++) {
      Personal_record temp;
      roster.retrieve(i, temp);
      if (same_id(r, temp)) {
        dupID = true;
        break;
      }
    }
    if (dupID) {
      stats.duplicate_id++;
      continue;
    }

    // Check duplicate person (first + last)
    bool dupName = false;
    for (int i = 0; i < roster.size(); i++) {
      Personal_record temp;
      roster.retrieve(i, temp);
      if (same_person(r, temp)) {
        dupName = true;
        break;
      }
    }
    if (dupName) {
      stats.duplicate_name++;
      continue;
    }

    // Find insert position to maintain sorted order
    int pos = 0;
    for (; pos < roster.size(); pos++) {
      Personal_record temp;
      roster.retrieve(pos, temp);
      if (comes_before(r, temp))
        break;
    }

    // Insert at the correct position
    roster.insert(pos, r);
    stats.inserted++;
  }

  return stats;
}

bool find_by_id(const List<Personal_record> &roster, const std::string &id,
                Personal_record &out) {
  // Fill in your code to support finding a record by ID for Task 3
  for (int i = 0; i < roster.size(); i++) {
    Personal_record temp;
    roster.retrieve(i, temp);
    if (temp.ID == id) {
      out = temp;
      return true;
    }
  }
  return false;
}

static bool starts_with(const std::string& s, const std::string& prefix) {
    return s.compare(0, prefix.size(), prefix) == 0;
}

int find_all_by_name_prefix(const List<Personal_record> &roster,
                            const std::string &first_prefix,
                            const std::string &last_prefix,
                            void (*visit)(Personal_record &)) {
  // Fill in your code to support finding matches by name prefix for Task 3
  int matches = 0;
  for (int i = 0; i < roster.size(); i++) {
    Personal_record temp;
    roster.retrieve(i, temp);
    if (starts_with(temp.first_name, first_prefix) &&
        starts_with(temp.last_name, last_prefix)) {
      visit(temp);
      matches++;
    }
  }
  return matches;
}
