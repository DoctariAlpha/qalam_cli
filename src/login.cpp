#include "login.h"
#include "file_manip.h"

int login(cpr::Session& session, std::string username, std::string password){

    std::string url_str = "https://qalam.nust.edu.pk/web/login"; //login url
    cpr::Url url{url_str};
    session.SetUrl(url);

    cpr::Response r = session.Get(); 
    writeFile("file.html",r.text); // for debugging
    if (r.status_code != 200) return 0;
    // Parsing document
    CDocument doc;
    doc.parse(r.text);

    // extracting csrf_token
    CSelection csrf = doc.find(".max-w-sm > input:nth-child(1)");
    std::string csrf_token = csrf.nodeAt(0).attribute("value");
    
    // sending payload to log in.
    session.SetPayload({
        {"csrf_token",csrf_token},
        {"login", username},
        {"password", password}       
    });

    cpr::Response r2 =  session.Post();
     
    CDocument doc2; // parsing again to check if has logged in correctly.
    doc2.parse(r2.text);

    CSelection h2 = doc2.find(".heading_b"); // this tag contains info about the user

    // clearing session payload buffer
    session.SetPayload(cpr::Payload{}); // clearing payload buffer. important!

    writeFile("login.html",r2.text); // writing to file. leaving this for now.

    return h2.nodeNum();
}