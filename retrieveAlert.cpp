#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "xmlParser.h"
#include "retrieveAlert.h"



#pragma warning (disable : 4996)


int get_alert(char* user_name, char* password, long memory, long cpu, long process) {
	XMLNode xMainNode = XMLNode::openFileHelper("config.xml", "PMML");

	for (int i = 0; i < xMainNode.nChildNode("client"); i++) {
		XMLNode xNode = xMainNode.getChildNode("client", i);
		if (strcmp(xNode.getAttribute("login"), user_name) == 0
			&& strcmp(xNode.getAttribute("pass"), password) == 0) {
			long memory_limit = atoi(xNode.getChildNode("alert", 0).getAttribute("limit"));
			long cpu_limit = atoi(xNode.getChildNode(("alert"), 1).getAttribute(("limit")));
			long process_limit = atoi(xNode.getChildNode(("alert"), 2).getAttribute(("limit")));

			int result = 0;
			result = (memory > memory_limit) ? 1 : 0;
			result = (cpu > cpu_limit) ? (result + 2) : result;
			result = (process > process_limit) ? (result + 4) : result;

			return result;
		}
	}
	return -1;
}
std::string getAlertType(char* username, char* password, long mem, long cpu, long process)
{
	//this data should be read in the JSON request
	 username = "user";
	 password = "password";
	mem = 20, cpu = 20, process = 200;//This is why it send an alert, because the number of processes exceeds the XML file.
	int result = get_alert(username, password, mem, cpu, process);
	printf("%d\n", result);
	int res = 0;
	switch(result) {
	case 0:
		return "no alerts\n";
		
	case 1:
		return "memory alert\n";
	case 2:
		return "cpu alert\n";
	case  3:
		return "memory and cpu alerts\n";
		
	case 4:
		return "process number too high alert\n";
		
	case 5:
		return "memory and process alerts\n";
		
	case 6:
		return "cpu and process alerts\n";
	case 7:
		return "memory, cpu and process alerts\n";
	default:
		return "username and password not found\n";
		
	}

	return "";
}

const char *GetWC(const char *c)
{
	const size_t cSize = strlen(c)+1;
	char* wc = new char[cSize];
		return wc;
}
