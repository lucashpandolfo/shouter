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


#ifndef SOURCEFIFO_H
#define SOURCEFIFO_H

#include "source.h"


class SourceFifo: public Source{
public:
    SourceFifo(std::string fifo_name, std::string metadata_filename);

    bool initialize();

    size_t get_data(char* buffer, size_t n);
    std::string get_metadata(std::string name);
    ~SourceFifo();

    private:

    int fifo;

    std::string fifo_name;
    std::string metadata_filename;
};

#endif // SOURCEFIFO_H
