//
// Created by Amanda  on 19/05/20.
//

#ifndef CAL_ERRO_H
#define CAL_ERRO_H

#include <string>



using namespace std;

class Error {
protected:
    string info;                                       /**<string containing the cause of the error*/
public:
    /**
     * @brief Construct a new Error object
     *
     * @param Info Information about the error
     */
    Error(string Info) : info(Info) {};

    /**
     * @brief Get the Info parameter
     *
     * @return std::string
     */
    virtual std::string getInfo() const { return info; };
};

class WrongInput_option : Error {
public:
    WrongInput_option(const std::string &input) : Error(input) {}

    std::string getInfo() const { return info; };
};
#endif //CAL_ERRO_