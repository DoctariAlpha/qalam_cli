#include <cpr/cpr.h>
#include <string>

#include <gq/Document.h>
#include <gq/Selection.h>
#include <gq/Node.h>


#ifndef LOGIN_H
#define LOGIN_H
int login(cpr::Session& session, std::string username, std::string password);

#endif