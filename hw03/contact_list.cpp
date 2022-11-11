#include "contact_list.h"

#include <algorithm>
#include <numeric>
#include <sstream>

//#include <string>

// TODO create implementation here!



// functions for dealing with the contact list storage - this is your contact list API.
// you have to implement them - and we check if they behave as expected.

/**
 * Given a contact storage, create a new contact entry by name and number.
 */
bool contact_list::add(storage& contacts, std::string_view name, number_t number){
    if (!name.empty() && std::find(contacts.names.begin(),contacts.names.end(),name) == contacts.names.end())
    {
        std::string str{name};
        contacts.names.push_back(str);
        contacts.numbers.push_back(number);

        return true;
    }
    return false;
}


/**
 * Given a contact storage, how many contacts are currently stored?
 */
size_t contact_list::size(const storage& contacts){
    return contacts.numbers.size();
}


/**
 * Fetch a contact number from storage given a name.
 */
contact_list::number_t contact_list::get_number_by_name(storage& contacts, std::string_view name){
    for (size_t i = 0; i < contacts.names.size(); i++)
    {
        if(contacts.names[i]==name){
            return contacts.numbers[i];
        }
    }

    return -1;
}


/**
 * Return a string representing the contact list.
 */
std::string contact_list::to_string(const storage& contacts){
    std::string str_list;
    for (size_t i = 0; i < contacts.names.size(); i++)
    {   
        std::string str = contacts.names[i] + " - " + std::to_string(contacts.numbers[i]) + "\n";
        //str.append(contacts.names[i]);
        //str.append(" - ");
        //str.append(std::to_string(contacts.numbers[i]));
        //str.append("/n");
        str_list += str;
    }
    
    return str_list;
}


/**
 * Remove a contact by name from the contact list.
 */
bool contact_list::remove(storage& contacts, std::string_view name){
    if (get_number_by_name(contacts,name) != -1)
    {
        size_t position{0};
        for (position = 0; position < contacts.names.size(); position++)
        {
            if(contacts.names[position]==name){
                break;
            }
        }
        contacts.names.erase(contacts.names.begin()+int(position));
        contacts.numbers.erase(contacts.numbers.begin()+int(position));

        return true;
    }
    
    return false;
}


/**
 * Sort the contact list in-place by name.
 */
void contact_list::sort(storage& contacts){
    std::vector<std::string> names2(contacts.names);
    std::vector<number_t> numbers2(contacts.numbers);

    std::vector<std::string>::iterator it;

    std::sort(contacts.names.begin(),contacts.names.end());

    for (size_t i = 0; i < contacts.names.size(); i++)
    {
        it = std::find(names2.begin(),names2.end(),contacts.names[i]);
        numbers2[i] = contacts.numbers[size_t(it-names2.begin())];
    }
    contacts.numbers = numbers2;
}


/**
 * Fetch a contact name from storage given a number.
 */
std::string contact_list::get_name_by_number(storage& contacts, number_t number){
    for (size_t i = 0; i < contacts.names.size(); i++)
    {
        if(contacts.numbers[i] == number){
            return contacts.names[i];
        }
    }
    
    return "";
}