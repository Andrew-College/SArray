#include "Array.h"
#include "Windows.h"
#include <iostream>
#include <string>


using namespace std;
void main(){
	Array<int> thingie(10);

	//thingie.load("unordered.txt");
	for(int i = 0;i<10000; i++)
		thingie.push(i);
	
	thingie.order();

	//thingie.pop();


	//for(int i = 0;i<=thingie.m_num_elem; i++)
		//cout << thingie[i] << endl;
	//Each test works
	cout << (thingie.search(33)!=-1?"found it!":"Not find D:") << endl;
	//cout << (thingie.search(0)!=-1?"found it!":"Not find D:") << endl;
	cout << (thingie.search(8998)!=-1?"found it!":"Not find D:") << endl;
	//cout << (thingie.search(33)!=-1?"found it!":"Not find D:") << endl;
	//thingie.save("ordered.txt");
	thingie.clear();
	string temp;
	getline(cin,temp);
}