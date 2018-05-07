#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

// Prompt Generator Function
string get_prompt(){
	string user = getenv("USER");
	string home = getenv("HOME");
	string pwd = getenv("PWD");
	if(pwd.find(home)!=string::npos){
		pwd.replace(pwd.begin(),pwd.begin()+home.size(),"~");
	}
	return user+':'+pwd+"$ ";
}

// Parser Function
void parse_cmd(const string &cmd, vector<string> &args){
	typedef boost::tokenizer<boost::escaped_list_separator<char> >  tok_t;

	tok_t tok(cmd);
	
	for(tok_t::iterator j (tok.begin()); j != tok.end(); ++j)
	{
		string f(*j);
		boost::trim(f);
		args.push_back(f);
		cout<<f<<endl;
	}
}

// Shell Loop Function
void vish_run(){
	string cmd;
	vector<string> args(0);
	int status = 1;
	do {

		// Print Prompt
		cout<<get_prompt();

		// Get Command
		getline (cin,cmd,'\n');

		// Check for Exit Condition
		if(cmd=="exit")
			status = 0;

		// Parse Command
		parse_cmd(cmd, args);
		

	} while(status);
}

int main(int argc, char const *argv[])
{
	// Shell Loop
	vish_run();

	return 0;
}
