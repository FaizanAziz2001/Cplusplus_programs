#include <iostream>
#include"ChaningMethod.h"
#include"LinearHash.h"
#include"QuadriticHash.h"
#include"Hashstring.h"
#include"UniversalHashing.h"
using namespace std;


int main()
{
	Unihash U(20);
	U.insert(1, "check");
	U.insert(2, "check");
	U.insert(3, "check");
	U.insert(5, "check");
	U.insert(6, "check");
	U.insert(7, "check");
	U.insert(8, "check");
	U.insert(9, "check");

	U.Print();
	auto D = U.Search(5);
	cout << D.data;

}

//int main()
//{
//	QuadriticHash L(10);
//		L.insert(5, "Nice");
//		L.insert(6,"ahmed");
//		L.insert(66,"Dele");
//		L.insert(8,"bob");
//		L.insert(88,"Austin");
//		L.insert(78,"V");
//		L.insert(68,"Asad");
//		L.insert(58,"Josh");
//		L.insert(107,"Khan");
//		/*L.insert(117,"Omer");*/
//		L.PrintTable();
//		cout << L.searchval(107);
//}

//int main()
//{
//	LinearHash L(10);
//	L.insert(5, "Nice");
//	L.insert(6,"ahmed");
//	L.insert(66,"Dele");
//	L.insert(8,"bob");
//	L.insert(88,"Austin");
//	L.insert(78,"V");
//	L.insert(68,"Asad");
//	L.insert(58,"Josh");
//	L.insert(48,"Khan");
//	L.insert(117,"Omer");
//	L.PrintTable();
//	cout << L.searchval(48);
//}
//int main()
//{
//    ChainHash T;
//    cout << T.isEmpty() << endl;
//    T.Insert(5, "nice");
//    T.Insert(10, "bob");
//    T.Insert(7, "ali");
//    T.Insert(8, "ahmed");
//    T.Insert(115, "jake");
//    T.Insert(8, "repalce");
//    cout << endl << endl;
//    T.Print();
//
//    T.Remove(10);
//    T.Remove(10);
//    cout << endl << endl;
//    T.Print();
//}
