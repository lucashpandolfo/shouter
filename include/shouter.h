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


#ifndef SHOUTER_H
#define SHOUTER_H

#include "stream.h"
#include "shout/shout.h"

class Shouter{

    public:	

    Shouter();
    bool initialize();
    void start();
    void stop();
   ~Shouter();

    static Shouter* create_from_file(const char* filename);
   
    private:

    bool connect();

    Stream* stream;
    shout_t* shout;

    bool stop_requested;
    
    std::string hostname;
    std::string password;
    std::string mountpoint;
    std::string user_name;
    int port;
    int protocol;
    int format;

    std::string stream_name;
    std::string stream_genre;
    std::string stream_description;
    std::string stream_url;
};

#endif // SHOUTER_H
