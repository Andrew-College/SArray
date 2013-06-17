#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include "Windows.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
template<class Datatype>
class Array
{

public: 

	/*
	// Name:        Array::Array
	// Description: This constructs the array with default grow value.
	// Arguments:   - p_size: the size of the array.
	*/
	Array( int p_size )
	{
		// allocate enough memory for the array.
		m_array = new Datatype[p_size];

		// set the size variable
		m_size = p_size;

		// set grow size
		m_grow = m_size;

		//set number of elements
		m_num_elem = 0;
	}


	/*
	// Name:        Array::~Array
	// Description: This destructs the array.
	*/
	~Array()
	{
		// if the array is not null, delete it.
		if( m_array != 0 )
			delete[] m_array;

		// clear the pointer, just in case we ever modify this.
		m_array = 0;
	}

	/*
	// Name:		Array::freeUp
	// Description:	Ensures that all remnants left in memory allocations are empty
	// Arguments:	Datatype* tempArray: templated pointer to array to be cleared 
	//				{warning!! Completely erases ALL content of array, make sure to pass in correct array}
	*/
	void freeUp(Datatype* tempArray){
		//New array will contain data from previous owner of memory section, clear this filth away
		for(int i = 0;i < m_size;i++){
			tempArray[i] = 0;
		}
	}

	void load(string input){
		string currentLine;
		Datatype temp;
		ifstream myfile(input);
		if (myfile.is_open())
		{
			while ( myfile.good() )
			{
				getline (myfile,currentLine);
				istringstream buffer(currentLine);
				buffer >> temp;
				push(temp);
			}
			myfile.close();
		} else{
			cout << "ERROR: can't open file.\nAre you sure you have the file in the right folder?" << endl;
			Sleep(1000);
			cout << "That file does not exist, punk.";
			Sleep(3000);
		}
	}
	/*
	//Name;			Array::save
	//Description;	Writes file to folder under its specified name
	//Arguments;	fName - Name of the file
	*/
	void save(string fName){
		int i = 1;
		ofstream myfile(fName);
		if (myfile.is_open())
		{
			while(i <= m_num_elem){
				cout << "writing " << m_array[i] << endl;
				myfile << m_array[i] << endl;
				i++;
			}

			myfile.close();
		}
	}
	/*
	// Name:        Array::Push
	// Description: Pushes element onto end of array
	// Arguments:   Datatype input: the data to be added to the array.
	*/
	void push( Datatype input )
	{

		if(m_num_elem+1 == m_size){
			//std::cout << "Resizing to " + m_size+m_grow << endl;
			Resize(m_grow);
		}
		m_num_elem++;
		m_array[m_num_elem] = input;
	}

	/*
	// Name:        Array::pop
	// Description: Pops last element off of array and returns that element
	*/
	Datatype pop(){
		Datatype temp =m_array[m_num_elem];
		m_array[m_num_elem] = 0;
		m_num_elem--;
		return temp;
	}
	/*
	// Name:        Array::order
	// Description: Quicksorts current array
	*/
	void order(){
		int i = 0;
		Datatype temp;
		while(true){			
			for(int k = 0; k < m_size-1; k++){
				if(m_array[k] > m_array[k+1]){
					temp = m_array[k];
					m_array[k] = m_array[k+1];
					m_array[k+1] = temp;
				}
			}
			if (i == m_size){
				return;
			}
			i++;
		}
	}
	/*
	// Name:        Array::order
	// Description: Quicksorts given array
	// Arguments:   Datatype* sortArray: Pointer to the data to be sorted
	*/
	void order(Datatype* sortArray){
		int i = 0;
		Datatype temp;
		while(true){			
			for(int k = 0; k < m_size-1; k++){
				if(sortArray[k] > sortArray[k+1]){
					temp = sortArray[k];
					sortArray[k] = sortArray[k+1];
					sortArray[k+1] = temp;
				}
			}
			if (i == m_size){
				return;
			}
			i++;
		}
	}
	/*
	// Name:		Array::search
	// Description:	Searches through array for a value and returns the index it was discovered in using either linear or binary search based on the size
	// Arguments:	Datatype input: Negates the need for overloading the search function for double, float, etc. 
	//							    (cant -technically- be used for strings)
	*/
	int search(Datatype input){
		//An arbitrary value, anything smaller than this number uses linear search, anything higher, binary search
		int limit = 50;
		if(m_size <= limit){//Linear O(kn) where k = m_num_elem
			//cout << "Linear" << endl;
			int i = 0;
			while(true){
				if(m_array[i]==input) return i;
				if(i > m_num_elem) return -1;
				i++;
			}

		}
		else{//Binary O(log n)
			//cout << "Binary" << endl;
			int now = m_size-1, last = 0, temp, count = 0;

			while(true){
				count ++;
				cout << now << "====" << last << endl;

				temp = last+(now-last)/2;


				//Found the point were looking for
				if(m_array[temp]== input)
					return now;
				//less than input value
				if(m_array[temp] < input){
					last = temp+1;
				}
				//greater than input
				else{
					now = temp-1;
				}

				//Searched entire array, didnt find the thing we were looking for
				if(count == m_size){
					return -1;
				}
			}
		}
	}
	/*
	// Name:        Array::Resize
	// Description: This resizes the array to a new size.
	// Arguments:   - p_size: the new size of the array.
	*/
	void Resize( int p_size )
	{


		// determine which size is smaller.
		int min;
		if( p_size <= -1 ){
			//User inputted a value or system calculated that the array can shrink
			min = p_size;
			// set the size of the new array

		}
		else{
			//User inputted a value or system calculated that the array can grow
			min = m_size+p_size;
			// set the size of the new array
		}
		m_size = min;
		// create a new array with the new size
		Datatype* newarray = new Datatype[min];
		freeUp(newarray);

		//std::cout << "Resized array "<< min << endl;

		// if the new array wasn't allocated, then just return
		// and don't change anything.
		if( newarray == 0 ){
			std::cout << "Resized array failed" << endl;
			return;
		}

		// loop through and copy everything possible over.
		int index;
		for( index = 0; index < min; index++ )
			newarray[index] = m_array[index];

		// delete the old array.
		if( m_array != 0 )
			delete[] m_array;

		// copy the pointer over.
		m_array = newarray;
	}


	/*
	//  Name:         Array::operator[]
	//  Description:  gets a reference to the item at given 
	//                index.
	//  Arguments:    - p_index: index of the item to get.
	//  Return Value: reference to the item at the index.
	*/
	Datatype& operator[] ( int p_index )
	{
		return m_array[p_index];
	}



	/*
	//  Name:         Array::Insert
	//  Description:  Inserts a cell inbetween two others.
	//  Arguments:    - p_item: item to insert
	//                - p_index: index to insert at.
	*/
	void Insert( Datatype p_item, int p_index )
	{
		int index;
		if(m_num_elem == m_size-1){
			resize();
		}
		// move everything after p_index up by one cell.
		for( index = m_size - 1; index > p_index; index-- )
			m_array[index] = m_array[index - 1];

		// insert the item.
		m_array[p_index] = p_item;
	}


	/*
	//Name;			Array::clear
	//Description;	clears the array
	*/
	void clear(){
		Array::~Array();
	}
	/*
	//  Name:         Array::Remove
	//  Description:  Removes a cell
	//  Arguments:    - p_index: index to remove.
	*/
	void Remove( int p_index )
	{
		int index;

		// move everything after p_index down by one cell.
		for( index = p_index + 1; index < m_size; index++ )
			m_array[index - 1] = m_array[index];

		//decrement m_num_elem
		m_num_elem--;

	}



	/*
	//  Name:         Array::Size
	//  Description:  gets the size of the array.
	//  Arguments:    None.
	//  Return Value: the size of the array.
	*/
	int Size()
	{
		return m_size;
	}

	int length(){
		int j = 0;
		for(int i = m_size;i > 0;i--){
			if(!m_array[i])
				j++;
			else{
				break;
			}
		}
		return m_size-j;
	}

	/*
	//  Name:         Array::operator DataType*
	//  Description:  conversion operator, converts array
	//                into a pointer, for use in C-functions
	//                and other normal array functions
	//  Arguments:    None.
	//  Return Value: a pointer to the array.
	*/
	operator Datatype* ()
	{
		return m_array;
	}


	/*
	//  Name:         Array::WriteFile
	//  Description:  Writes an array to disk
	//  Arguments:    The Filename
	//  Return Value: true on success, false on failure
	*/
	bool WriteFile( const char* p_filename )
	{
		FILE* outfile = 0;
		int written = 0;

		// open the file
		outfile = fopen( p_filename, "wb" );

		// return if it couldn't be opened
		if( outfile == 0 )
			return false;

		// write the array and close thef ile
		written = fwrite( m_array, sizeof( Datatype ), m_size, outfile );
		fclose( outfile );

		// if we didn't write the number of items we expected,
		// return failure
		if( written != m_size )
			return false;

		// return success.
		return true;
	}


	/*
	//  Name:         Array::ReadFile
	//  Description:  reads an array from disk
	//  Arguments:    The Filename
	//  Return Value: true on success, false on failure
	*/
	bool ReadFile( const char* p_filename )
	{
		FILE* infile = 0;
		int read = 0;

		// open the file
		infile = fopen( p_filename, "rb" );

		// return if it couldn't be opened
		if( infile == 0 )
			return false;

		// read the array and close the file
		read = fread( m_array, sizeof( Datatype ), m_size, infile );
		fclose( infile );

		// if we didn't read the number of items we expected,
		// return failure
		if( read != m_size )
			return false;

		// return success
		return true;
	}



	/*
	// Name:        Array::m_array
	// Description: This is a pointer to the array.
	*/
	Datatype* m_array;


	/*
	// Name:        Array::m_size
	// Description: the current size of the array.
	*/
	int m_size;

	/*
	// Name:        Array::m_grow
	// Description: the current grow size of the array.
	*/
	int m_grow;
	/*
	// Name:        Array::m_num_elem
	// Description: the current number of elements in the array.
	*/
	int m_num_elem;
};
#endif