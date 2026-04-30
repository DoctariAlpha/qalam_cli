#include "get_courses.h"
#include "file_manip.h"

#include "read_file.h"

#include <gq/Document.h>
#include <gq/Node.h>
#include <gq/Selection.h>




std::vector<std::vector<std::string>> get_courses(cpr::Session& session){

	std::string url_str = "https://qalam.nust.edu.pk/student/dashboard"; // this is the url from where the courses will be scraped
	session.SetUrl(cpr::Url{url_str});
	cpr::Response r = session.Get();
	writeFile("courses.html",r.text); // saving the file // for debugging and efficiency while building
	
	CDocument doc; // gq
	doc.parse(r.text);
	CSelection div1 = doc.find("#hierarchical_show2");
	
	CSelection a_s = div1.find("a"); // finding all the <a> tags in the retrieved html

	int n_nodes = a_s.nodeNum(); // number of nodes.

	CSelection c_name_s  = a_s.nodeAt(0).find(".card-header");; // this is to be used as a buffer.
	std::vector<std::vector<std::string>> data; // a nested vector to store the data
	data.reserve(a_s.nodeNum()); // reserving memory for efficiency.
	std::string href; // to be used as a buffer while extracting course id
	for (int i=0; i<a_s.nodeNum();i++){
		std::vector<std::string> c_data;
		c_data.reserve(6); // to store data of each course

		// extracting course id
		href = a_s.nodeAt(i).attribute("href");
		size_t s = href.find("info/");
		c_data.push_back(href.substr(s+5,7));

		// course_name
		c_name_s = a_s.nodeAt(i).find(".card-header");
		c_data.push_back(c_name_s.nodeAt(0).text());

		//instructor name
		c_name_s = a_s.nodeAt(i).find(".card-title");
		c_data.push_back(c_name_s.nodeAt(0).text());

		// course code
		c_name_s = a_s.nodeAt(i).find("span.sub-heading");
		c_data.push_back(c_name_s.nodeAt(0).text());

		// credit hours 
		c_name_s = a_s.nodeAt(i).find("span.md-list-heading");
		c_data.push_back(c_name_s.nodeAt(0).text());
		// Attendance
		c_name_s = a_s.nodeAt(i).find("div.uk-text-small").find("span");
		c_data.push_back(c_name_s.nodeAt(0).text());

		data.push_back(c_data); // adding the current course details to the data vector.
	}
	return data;
}