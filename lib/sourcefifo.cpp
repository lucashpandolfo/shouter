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


#include "sourcefifo.h"

#include "log.h"

#include <fcntl.h>
#include <unistd.h>
#include "configurer.h"

SourceFifo::SourceFifo(std::string fifo_name, std::string metadata_filename) {
    this->fifo_name = fifo_name;
    this->metadata_filename = metadata_filename;
}

bool SourceFifo::initialize() {
    fifo = open(fifo_name.c_str(), O_RDONLY);
    if(fifo<0)
      log(0, "Could not open fifo " + fifo_name + " for reading");
    return fifo > 0;
}

size_t SourceFifo::get_data(char* buffer, size_t n) {
    if(fifo<0)
      return 0;
    return read(fifo, buffer, n);
}

std::string SourceFifo::get_metadata(std::string name){
    std::cout << "Reading metadata from " << metadata_filename << "\n";
    Configurer conf(metadata_filename);
    conf.parse();
  
    std::string meta;
    conf.read_string(name, meta);
    return meta;
}

SourceFifo::~SourceFifo() {
    if(fifo>0)
        close(fifo);
    fifo = -1;
}
