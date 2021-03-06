#include"memorymanagement.hpp"
#include<vector>
#include <string>
#define MAX 50

using namespace std;

//bool MemProcess[MAX];
//bool MemFile[MAX];

namespace memmgmt {

	std::vector<File> FAT;

	std::vector <Process> PAT;

	Process::Process(std::string p_name, int p_size, int p_burst) {
		this->name = p_name;
		this->size = p_size;
		this->p_burst = p_burst;
		this->isComplete = false;
	}

	int spaceOccupiedProcess() {
		// Checks total space occupied
		int totalOccupied = 0;
		for (vector<Process>::iterator i = PAT.begin(); i != PAT.end(); i++) {
			totalOccupied = totalOccupied + i->size;
		}

		return totalOccupied;
	}

	bool updatePAT(Process p) {
		int totalOccupied = 0;
		if (p.size <= MAX) {
			if (PAT.empty()) {
				p.start_block = 0;
				PAT.push_back(p);
				return true;
			}
			else {
				totalOccupied = spaceOccupiedProcess();
				if (p.size <= MAX - totalOccupied) {
					Process temp = *(PAT.end() - 1);
					p.start_block = temp.start_block + temp.size;
					PAT.push_back(p);
					return true;
				}
				else {
					return false;
				}

			}
		}
		else {
			return false;
		}
	}

	bool deleteProcessfromPAT(string p_name) {
		// DELETING A PROCESS FROM A PAT TABLE
		int flag = 0;
		for (vector<Process>::iterator i = PAT.begin(); i < PAT.end(); i++) {
			if (i->name == p_name) {
				PAT.erase(i);
				return true;
			}
		}
		return false;
	}

	string displayPAT() {
		string response = "Name\t\tSize\t\tStart\t\t\n";
		for (vector<Process>::iterator i = PAT.begin(); i != PAT.end(); i++) {
			response.append(i->name + "\t\t" + std::to_string(i->size) + "\t\t" + to_string(i->start_block) + "\n");
		}
		return response;
	}

	//bool MemProcess[MAX];
	//bool MemFile[MAX];

	File takeFileParamters(string f_name, int f_size) {
		// Takes Process Parameters and creates a file with startblock -1
		struct File f;
		f.name = f_name;
		f.size = f_size;
		f.start_block = -1;

		return f;
	}

	int spaceOccupiedFile() {
		// Checks total space occupied
		int totalOccupied = 0;
		for (vector<File>::iterator i = FAT.begin(); i != FAT.end(); i++) {
			totalOccupied = totalOccupied + i->size;
		}

		return totalOccupied;
	}

	bool updateFAT(File f) {
		int totalOccupied = 0;
		if (f.size <= MAX) {
			if (FAT.empty()) {
				f.start_block = 0;
				FAT.push_back(f);

				return true;
			}
			else {

				totalOccupied = spaceOccupiedFile();
				if (f.size <= MAX - totalOccupied) {
					File temp = *(FAT.end() - 1);
					f.start_block = f.size + temp.start_block + temp.size - 1;
					FAT.push_back(f);

					return true;
				}
				else {
					return false;
				}

			}
		}
		else {
			return false;

		}
	}




	bool deleteFilefromFAT(string f_name) {
		// DELETING A FILE FROM A PAT TABLE
		int flag = 0;
		for (vector<File>::iterator i = FAT.begin(); i != FAT.end(); i++) {
			if (i->name == f_name) {
				FAT.erase(i);
				flag = -1;
				return true;

			}
		}

		return false;
	}

	std::string displayFAT() {
		std::string string = "";
		for (vector<File>::iterator i = FAT.begin(); i != FAT.end(); i++) {
			string += (i->name) + "\t" + std::to_string(i->size) + "\t" + std::to_string(i->start_block);
		}

		return string;
	}



	float percentageSpace() {
		// Shell process which will give the total utilization of the system space in percentage
		float totalOccupied = 0;
		for (vector<Process>::iterator i = PAT.begin(); i != PAT.end(); i++) {
			totalOccupied = totalOccupied + i->size;
		}
		for (vector<File>::iterator i = FAT.begin(); i != FAT.end(); i++) {
			totalOccupied = totalOccupied + i->size;
		}

		return (totalOccupied * 100) / (2 * MAX);
	}
	// COMPACTION LOGIC, HIGHLY RECOMMENDED THAT WE USE EVERYTIME

	void compactionPAT() {
		if (PAT.size() > 0) {
			if ((PAT.begin())->start_block != 0) {
				(PAT.begin())->start_block = 0;
			}
			for (vector<Process>::iterator i = (PAT.begin()); i < PAT.end() - 1; i++) {

				(i + 1)->start_block = i->size + i->start_block;
			}
		}
	}

	void compactionFAT() {

		if ((FAT.begin())->start_block != 0) {
			(FAT.begin())->start_block = 0;
		}
		for (vector<File>::iterator i = (FAT.begin() + 1); i != FAT.end(); i++) {

			(i + 1)->start_block = i->size + i->start_block;
		}
	}

}
