/*
    Copyright (C) 2018-2019 SKALE Labs

    This file is part of skale-consensus.

    skale-consensus is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    skale-consensus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with skale-consensus.  If not, see <https://www.gnu.org/licenses/>.

    @file Exception.h
    @author Stan Kladko
    @date 2018
*/

#pragma once

#include <boost/exception/exception.hpp>
#include <exception>
#include <string>

class Exception : virtual public std::exception, public boost::exception {
public:
    Exception( const std::string& _message, const std::string& _className ) {
        message = _className + ":" + _message;
    }
    const char* what() const noexcept override {
        return message.empty() ? std::exception::what() : message.c_str();
    }

    const std::string& getMessage() const { return message; }

    bool isFatal() const { return fatal; }

private:
    std::string message;

protected:
    bool fatal = false;

public:
    static void logNested( const std::exception& e, int level = 0 );
};
