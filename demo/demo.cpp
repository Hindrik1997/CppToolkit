#include <utility>

//
// Created by hindrik on 11-8-18.
//

#include "../cpp_tools.h"
#include <string>

struct Person {
    int         id;
    std::string name;
    int         age;

    Person(int id, std::string name, int age) : id(id), name(std::move(name)), age(age) {
        //Do stuff here...
    }

};

class PersonContainer {
private:

    //Person is not initialized, no default constructor is called.
    LazyInit<Person> person;
public:
    PersonContainer() {

        //Actual person object is constructed in constructor body.
        person = make_delayed<Person>(5, "John Doe", 28);

    }

    ~PersonContainer() {
        //Automatically calls ~Person()
    }
};