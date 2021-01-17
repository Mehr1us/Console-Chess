#include "main.h"
// using ofstream constructors.
#include <iostream>
#include <fstream> 

void Log::print() {
	//spit out moves done onto a txt file

	if (!hasLog) {
		//hh-mm-ss dd-mm-yyyy.txt
		//A filename cannot contain the basic characters '\', '/', ':', '*', '?', '"', '<', '>', '|'
		time_t fileT = time(NULL);
		std::string raw = ctime(&fileT); //e.g."Wed Feb 13 15:46:11 2013"
		std::string temp;
		std::string mnth;
		int c = 0;
		for (int i = 0; i < raw.size(); i++) {
			if (raw[i] == ' ')c++;
			if (c == 3) {
				temp += raw[i];
			}
		}
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] == ':')temp[i] == '-';
		}
		temp += ' ';
		for (int i = 0; i < raw.size(); i++) {
			if (raw[i] == ' ')c++;
			if (c == 2) {
				temp += raw[i];
			}
		}
		temp += '-';
		for (int i = 0; i < raw.size(); i++) {
			if (raw[i] == ' ')c++;
			if (c == 1) {
				mnth += raw[i];
			}
		}
		{
			if (mnth == "Jan")temp += "01";
			if (mnth == "Feb")temp += "02";
			if (mnth == "Mar")temp += "03";
			if (mnth == "Apr")temp += "04";
			if (mnth == "May")temp += "05";
			if (mnth == "Jun")temp += "06";
			if (mnth == "Jul")temp += "07";
			if (mnth == "Aug")temp += "08";
			if (mnth == "Sep")temp += "09";
			if (mnth == "Oct")temp += "10";
			if (mnth == "Nov")temp += "11";
			if (mnth == "Dec")temp += "12";
		}
		temp += '-';
		for (int i = 0; i < raw.size(); i++) {
			if (raw[i] == ' ')c++;
			if (c == 4) {
				temp += raw[i];
			}
		}
		logName == temp;
		logName += ".txt";

	std::ofstream outfile(logName);
	outfile.close();
	}
	hasLog = true;

	std::ofstream outfile;
	outfile.open(logName, std::ofstream::out | std::ofstream::trunc);

	for (int i = 0; i < L.log.size(); i += 2) {
		outfile << L.log[i] << " " << L.log[i + 1] << std::endl;
	}

	outfile.close();
}

//to-do add move to log translation
void Log::logMove(Tile s, Tile t, bool WhiteMove) {

}