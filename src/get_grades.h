#include "read_file.h"
#include <vector>

#include <cpr/cpr.h>


#include <gq/Document.h>
#include <gq/Node.h>
#include <gq/Selection.h>

#ifndef GET_GRADES_H
#define GET_GRADES_H


std::vector<std::vector<std::string>> get_grades(std::string& url, cpr::Session& session);

#endif