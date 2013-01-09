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


#ifndef CONFIGURER_H
#define CONFIGURER_H

#include <string>
#include <vector>
#include "sexp.h"

class Configurer{
public:
  Configurer(std::string filename);
  Configurer operator=(Configurer &conf);

  bool parse();
  
  bool read_string(std::string name, std::string &variable);
  bool read_int(std::string name, int &variable);

  ~Configurer();
private:
  std::vector<std::string> split(std::string string);
    bool retrieve_string(std::vector< std::string > names, std::vector< sexp_t* > roots, std::string& string);
  
  std::vector<sexp_t*> roots;
  std::string filename;
};

#endif // CONFIGURER_H
