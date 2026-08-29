#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

class Book {
public:
    std::string name;
    std::string genre;
    bool borrowed;
    std::string user;

    Book(std::string title, std::string type, bool status, std::string owner) {
        name = title;
        genre = type;
        borrowed = status;
        user = owner;
    }

    std::string ret() {
        return name + "," + genre + "," + (borrowed ? "true" : "false") + "," + user;
    }

    void returnBook() {
        user = "library";
        borrowed = false;
    }

    void borrowBook(std::string newOwner) {
        user = newOwner;
        borrowed = true;
    }
};

int main() {
    std::ifstream file("data.csv");
    
    std::vector<Book> catalogue;

    std::string text;

    std::string title;
    std::string type;
    std::string borrowedStr;
    bool borrowed;
    std::string owner;

    std::getline(file,text);

    while (std::getline(file,text)) {
        std::stringstream ss(text);

        std::getline(ss, title, ',');
        std::getline(ss, type, ',');
        std::getline(ss, borrowedStr, ',');
        std::getline(ss, owner,',');

        borrowed = (borrowedStr == "true");

        catalogue.push_back(Book(title, type, borrowed, owner));
    } 

    file.close();

    for (std::size_t i = catalogue.size(); i-- > 0;) {
        std::cout << catalogue[i].ret() << std::endl;
    }

    std::cout << "Enter action ('borrow', 'return', 'exit')" << std::endl;

    std::string response = "";
    std::string book = "";


    while (response != "exit") {
        std::cin >> response;
        if (response == "borrow") {
            std::cout << "Enter the book you want to borrow" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::getline(std::cin, book);
            
            std::size_t index = std::string::npos;

            for (std::size_t i = catalogue.size(); i-- > 0;) {
                if (catalogue[i].name == book) index = i;
            }

            if (index == std::string::npos) std::cout << "That book was not found" << std::endl;
            else {
                if (catalogue[index].borrowed == true) std::cout << "The book has already been borrowed" << std::endl;
                else {
                    std::string name = "";
                    std::cout << "Enter your name" << std::endl;

                    std::getline(std::cin, name);
                    catalogue[index].borrowBook(name);
                }
            }
        }
        if (response == "return") {
            std::string name = "";
            std::cout << "Enter your name" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, name);


            std::cout << "Enter your book" << std::endl;
            std::getline(std::cin, book);
            std::size_t index = std::string::npos;

            for (std::size_t i = catalogue.size(); i-- > 0;) {
                if (catalogue[i].name == book && catalogue[i].user == name) index = i;
            }
            if (index == std::string::npos) std::cout << "That book was not found in your name" << std::endl;
            else {
                catalogue[index].returnBook();
            }
        }
        std::cout << "Enter action ('borrow', 'return', 'exit')" << std::endl;
    }

    std::ofstream outFile("data.csv");

    for (std::size_t i = catalogue.size(); i-- > 0;) {
        outFile << catalogue[i].ret() << std::endl;
    }

    return 0;
}