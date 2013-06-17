#ifndef SARRAY_H
#define SARRAY_H

#include<iostream>
using namespace std;
template <class Datatype, int m_size>;	
class sArray{

private:
	sArray<Datatype*> m_array;

public:



	sArray<Datatype*> sArray(int p_size){

	}

	/*
	Name;			sArray::resize
	Description;	Creates a new array (newarray) of size p_size, adds all the elements of the array m_array, then deletes m_array
	Arguments;		p_size - Integer to define size of newarray
	*/

	void resize( int p_size)
	{
		Datatype* newarray= new Datatype[p_size];
		if( newarray== 0 )
			return;
		int min;
		if( p_size< m_size)
			min = p_size;
		else
			min = m_size;
		int index;
		for( index = 0; index < min; index++ )
			newarray[index] = m_array[index];
		m_size= p_size;
		if( m_array!= 0 )
			delete[] m_array;
		m_array= newarray;
	}
}
#endif