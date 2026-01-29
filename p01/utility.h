#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <istream>

// Forward declaration (template defined in List1.h / List2.h)
template <class T>
class List;

struct Personal_record {
    std::string first_name;
    std::string last_name;
    std::string ID;
};

enum Error_code {
    duplicate_error,
    not_present,
    success,
    overflow,
    underflow,
    range_err,
    fail
};

struct Import_stats {
    int inserted = 0;
    int duplicate_id = 0;
    int duplicate_name = 0;
    int bad_records = 0;   // malformed lines/records
};

// Comparison / matching helpers
bool same_id(const Personal_record& a, const Personal_record& b);
bool same_person(const Personal_record& a, const Personal_record& b);

// Sort order: last_name, then first_name, then ID
bool comes_before(const Personal_record& a, const Personal_record& b);

// Printing callback
void print_record(Personal_record& r);

// List operations
Import_stats import_file(List<Personal_record>& roster, const std::string& filename);

bool find_by_id(const List<Personal_record>& roster, const std::string& id, Personal_record& out);
int  find_all_by_name_prefix(const List<Personal_record>& roster,
                             const std::string& first_prefix,
                             const std::string& last_prefix,
                             void (*visit)(Personal_record&));

#endif // UTILITY_H
