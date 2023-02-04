#include <boost/regex.hpp>
#include <string>
#include <iostream>
#include <locale>

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
    //Example 8.3. Replacing characters in strings with boost::regex_replace()
    std::string s2 = "Boost Libraries";
    boost::regex expr3{"\\s"};
    std::string fmt{"_"};
    std::cout << boost::regex_replace(s2, expr3, fmt) << '\n';
    // boost::regex_replace() always searches through the entire string for the regular expression. Thus, the program actually replaces all three spaces with underscores.

    //Example 8.4. Format with references to groups in regular expressions== use it for swapping groups
    std::string s3 = "Boost Libraries";
    boost::regex expr4{"(\\w+)\\s(\\w+)"};
    std::string fmt4{"\\2 \\1"};
    std::cout << boost::regex_replace(s3, expr4, fmt4) << '\n';
    // Example 8.6. Iterating over strings with boost::regex_token_iterator
    std::string s5 = "Boost Libraries";
    boost::regex expr5{"\\w+"};
    boost::regex_token_iterator<std::string::iterator> it{s5.begin(), s5.end(),expr5};
    boost::regex_token_iterator<std::string::iterator> end;
    while (it != end)
        std::cout << *it++ << '\n';
    //  it is initialized with iterators to s and the regular expression “\w+”. The default constructor creates an end iterator.

    // Example 8.7. Accessing groups with boost::regex_token_iterator
    std::string s6 = "Boost Libraries";
    boost::regex expr6{"(\\w)\\w+"};
    boost::regex_token_iterator<std::string::iterator> it2{s6.begin(), s6.end(),expr6, 1};
    boost::regex_token_iterator<std::string::iterator> end2;
    while (it2 != end2)
        std::cout << *it2++ << '\n';

    // Example 8.8. Linking a locale to a regular expression
    std::string s7 = "Boost k\xfct\xfcphaneleri";
    boost::basic_regex<char, boost::cpp_regex_traits<char>> expr7;
    expr7.imbue(std::locale{"Turkish"});
    expr7 = "\\w+\\s\\w+";
    std::cout << std::boolalpha << boost::regex_match(s7, expr7) << '\n';
}