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


#include "configurer.h"

#include <fcntl.h>
#include <unistd.h>
#include "sexp_ops.h"
#include <string>


Configurer::Configurer(std::string filename) {
    this->filename = filename;
}


static bool listp(sexp_t* sx) {
    return (sx && (sx->ty == SEXP_LIST));
}

static bool null(sexp_t* sx) {
    return (sx==NULL || (sx->val == NULL && sx->next == NULL && sx->list == NULL));
}

bool Configurer::parse() {

    roots.clear();

    int fd;
    sexp_t *sx, *param;
    sexp_iowrap_t *iow;

    fd = open(filename.c_str(),O_RDONLY);
    if(fd<0)
        return false;

    iow = init_iowrap(fd);

    while(!null(sx = read_one_sexp(iow))) {
        roots.push_back(sx);
    }

    close(fd);
    destroy_iowrap(iow);
}

bool Configurer::read_string(std::string name, std::string &variable) {
  return retrieve_string(split(name), roots, variable);
}

bool Configurer::read_int(std::string name, int &variable) {
  std::string tmp;
  if(retrieve_string(split(name), roots, tmp)){
      variable = atoi(tmp.c_str());
      return true;
  }
  return false;
}


std::vector<std::string> Configurer::split(std::string string){
    size_t p;
    std::vector<std::string> strings;
    
    p = string.find_first_of("/");
    
    while(p!= std::string::npos){
      strings.push_back(string.substr(0,p));
      string = string.substr(p+1,std::string::npos);
      p = string.find_first_of("/");
    }
    strings.push_back(string);
    return strings;
}

bool Configurer::retrieve_string(std::vector<std::string> names, std::vector<sexp_t*> roots, std::string& string) {
    if(names.empty() || roots.empty())
        return false;

    std::string name = names[0];
    names.assign(++names.begin(), names.end());

    for(int i=0; i<roots.size(); i++) {
        sexp_t* root = roots[i];
	
        if(listp(root)) {
	    sexp_t* list = root->list;
	    
            if(name.compare(list->val)==0) {
	      
		if(names.empty()){
		  if(!null(list->next) && list->next->val){
		    string = std::string(list->next->val);
		    return true;
		  }
		  else return false;
		}
		
                sexp_t* next = list->next;
		std::vector<sexp_t*> next_roots;
                while(!null(next)) {
		    next_roots.push_back(next);
                    next = next->next;
                }
                return retrieve_string(names, next_roots, string);
            }
        }
    }
    return false;
}

Configurer::~Configurer() {
    while(roots.size()>0) {
        destroy_sexp(roots.back());
        roots.pop_back();
    }
}
