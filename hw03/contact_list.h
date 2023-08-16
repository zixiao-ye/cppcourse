#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>


/**
 * this namespace contains all contact list features and internal types.
 */
namespace contact_list {


/**
 * "enterprise grade" "ideal" storage type for telephone numbers.
 */
using number_t = int64_t;


/**
 * stores contacts by saving names and numbers.
 * be careful - these vectors have to be kept in sync!
 *
 * you may adjust this struct to store the data differently, or add index structures, ...
 * this is fine as long as the API of the functions below remains the same.
 */
struct storage {
    std::vector<number_t> numbers;
    std::vector<std::string> names;
};



// functions for dealing with the contact list storage - this is your contact list API.
// you have to implement them - and we check if they behave as expected.

/**
 * Given a contact storage, create a new contact entry by name and number.
 */
bool add(storage& contacts, std::string_view name, number_t number);


/**
 * Given a contact storage, how many contacts are currently stored?
 */
size_t size(const storage& contacts);


/**
 * Fetch a contact number from storage given a name.
 */
number_t get_number_by_name(storage& contacts, std::string_view name);


/**
 * Return a string representing the contact list.
 */
std::string to_string(const storage& contacts);


/**
 * Remove a contact by name from the contact list.
 */
bool remove(storage& contacts, std::string_view name);


/**
 * Sort the contact list in-place by name.
 */
void sort(storage& contacts);


/**
 * Fetch a contact name from storage given a number.
 */
std::string get_name_by_number(storage& contacts, number_t number);


} // namespace contact_list
