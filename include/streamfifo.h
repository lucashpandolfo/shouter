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


#ifndef STREAMFIFO_H
#define STREAMFIFO_H

#include "stream.h"


class StreamFifo: public Stream{
    StreamFifo(const char* fifo_name, const char* metadata_filename);

    bool initialize();

    size_t get_data(char* buffer, size_t n);

    ~StreamFifo();

    private:

    int fifo;

    std::string fifo_name;
    std::string metadata_filename;
};

#endif // STREAMFIFO_H
