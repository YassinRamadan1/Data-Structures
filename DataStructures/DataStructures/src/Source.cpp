#include <iostream>
#include "BTree.h"
#include "SuffixArray.h"

void BTreeTest() {
	
	BTree<int, 3> t1;

	t1.insert(1);
	t1.insert(5);
	t1.insert(0);
	t1.insert(4);
	t1.insert(3);
	t1.insert(2);
	t1.print();
	
	std::cout << "-----------------------------------------------------------------\n";

	BTree <char, 5> t; 
	
	t.insert('G');
	t.insert('I');
	t.insert('B');
	t.insert('J');
	t.insert('C');
	t.insert('A');
	t.insert('K');
	t.insert('E');
	t.insert('D');
	t.insert('S');
	t.insert('T');
	t.insert('R');
	t.insert('L');
	t.insert('F');
	t.insert('H');
	t.insert('M');
	t.insert('N');
	t.insert('P');
	t.insert('Q');
	
	t.insert('O');
	t.insert('U');
	t.insert('V');
	t.insert('W');
	t.insert('X');
	t.insert('Y');
	t.insert('Z');
	t.insert('a');
	t.insert('b');
	t.insert('c');
	
	t.print();
}

void SuffixArrayTest() {

	SuffixArray t("ACGACTACGATAAC$");
	t.constructUsingPrefixDoubling();
	t.print();
	// Prints: 14 11 12 0 6 3 9 13 1 7 4 2 8 10 5
}

int main() {

	SuffixArrayTest();
	return 0;
}
