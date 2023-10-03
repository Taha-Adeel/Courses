/* 
	Header containing utility functions to print the data to standard output
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <iomanip>
#include <unordered_set>
#include "graph.h"

void printSet(const std::unordered_set<Person*>& people){
	for(auto& person: people){
		std::cout << person->m_node_id << ", ";
	}
	std::cout << std::endl;
}

// Utility function to print one cell.
template<typename T> 
void print_element(T element, int row_width = 18, std::string column_separator = " | ", char separator = ' '){
	std::cout << column_separator;
    std::cout << std::left << std::setw(row_width) << std::setfill(separator) << element;
}

void end_row(){
	print_element(" ");
	std::cout << std::endl;
}

void print_row_separator(int no_of_rows, int row_width = 18){
	print_element('-', row_width, " +-", '-');
	for(int i = 1; i < no_of_rows; ++i){
		print_element('-', row_width, "-+-", '-');
	}
	std::cout << "-+ " << std::endl;
}

#endif