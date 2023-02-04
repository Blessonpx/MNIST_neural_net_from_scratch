#include <boost/regex.hpp>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    // Reference article https://theboostcpplibraries.com/boost.regex
    
    //Example 8.1. Comparing strings with boost::regex_match()
    std::string s = "Boost Libraries";
    boost::regex expr{"\\w+\\s\\w+"};
    // Iterations that are true for above string s
    // "Boost Libraries"
    // "B_1234ost Libraries"

    // \w Matches a word character (that is, an alphanumeric or underscore (_) character). 
    // The expression \w+?x\w matches abxc in the string abxcxd
    // \W Matches a nonword character.
    std::cout << std::boolalpha << boost::regex_match(s, expr) << '\n';

    //Example 8.2. Searching strings with boost::regex_search()
    std::string s1 = "Boost Libraries";
    boost::regex expr2{"(\\w+)\\s(\\w+)"};
    boost::smatch what;
    // result of regex_search gets stored in smatch watch 
    // what[0]="Boost Libraries";
    // what[1]="Boost" and what[2]="Libraries";;
    if (boost::regex_search(s1, what, expr2)){
        std::cout << what[0] << '\n';
        std::cout << what[1] << "_" << what[2] << '\n';
        }
}