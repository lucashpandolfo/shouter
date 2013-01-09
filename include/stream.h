/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef STREAM_H
#define STREAM_H

#include <unistd.h>
#include <string>

class Stream{

    public:
    Stream();
    bool initialize();
    virtual size_t get_data(char* buffer, size_t n)=0;
    std::string get_metadata(std::string name);
    
    private:
    std::string name;
    std::string artist;
    std::string album;
    std::string year;
    std::string genre;
    std::string track;
};

#endif // STREAM_H
