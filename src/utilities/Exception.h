//
// Created by duong on 15/09/2024.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <string_view>

using std::string;
using std::string_view;


namespace Cal
{
class Exception;
}

class Cal::Exception
{
public:
    explicit Exception(string_view msg) : msg_{msg} { }
    const string& what() const { return msg_; }

private:
    string msg_;
};

#endif //EXCEPTION_H
