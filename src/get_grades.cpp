#include "get_grades.h"
#include "file_manip.h"
#include <iostream>


std::string removeSpace(std::string& source){
	std::string r_str = "";
	for (int i = 0;i<source.size();i++){
		if (std::isspace(source[i])){}
		else r_str+=source[i];
	}
	r_str.shrink_to_fit();
	return r_str;
}


std::vector<std::vector<std::string>> get_grades(std::string& course_id, cpr::Session& session){
	
	std::string b_url = "https://qalam.nust.edu.pk/student/course/gradebook/";
	session.SetUrl(cpr::Url{b_url+course_id});
	cpr::Response r = session.Get();

	writeFile("grades.html",r.text); // for debugging

	CDocument doc;
	doc.parse(r.text);
	
	CSelection g_trs = doc.find("table.uk-table").nodeAt(0).find("tbody").nodeAt(0).find("tr"); // "Contains the tr's"
	CSelection tds = doc.find("table.uk-table").nodeAt(0).find("tbody").nodeAt(0).find("tr"); // this is to be used as a buffer
	std::vector<std::vector<std::string>> grades;
	if (g_trs.nodeNum()>0){
		grades.reserve(g_trs.nodeNum()); 
		std::string empty_str = "";
		bool contains_elems = false; // this is to see whether the tr has any data in it.
		for (int i=0;i<g_trs.nodeNum(); i++){ // iterating over all the tr's found
			tds = g_trs.nodeAt(i).find("td"); // finding all the td's in the current tr
			std::vector<std::string> c_data; // to store data for the current tr
			contains_elems = false; // specifies whether the td contains text
			for (int j = 0; j<tds.nodeNum();j++){
				std::string txt = tds.nodeAt(j).text(); 
				std::string ptxt = removeSpace(txt); // removing whitespaces

				if (ptxt != empty_str){ // checking whether this td has text in it.
					c_data.push_back(ptxt);
					contains_elems = true;
				}
			}
			c_data.shrink_to_fit();
			if (contains_elems){ // adding to the list if the tr contains data.
				grades.push_back(c_data);
			}
		}
	}
	else std::cout<< "Node not found!\n";
	
	grades.shrink_to_fit();
	return grades;
}