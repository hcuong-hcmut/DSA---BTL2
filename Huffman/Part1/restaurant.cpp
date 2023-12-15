/*
! Võ Tiến ..............
* Võ Tiến ..............
~ Võ Tiến ..............
& Võ Tiến ..............
TODO Võ Tiến ..............
*/

#include "main.h"


int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;


//* nhà hàng của sư phụ GOJO
class RESTAURANT_Gojo
{
	//TODO: implement
};
//* nhà hàng su cờ na
class RESTAURANT_Sukuna{
	//TODO: implement
};

class HuffTree_AVL{

public:
	vector<pair<char, int>> string_Processing(string& name)
	{
		//TODO: implement string_Processing
		
	}

	int encode(string name){

		if(name.length() < 3) return 1;

		//* bước 1 xử lí chuỗi thu được list để tới phần sau
		vector<pair<char, int>> freq = this->string_Processing(name);

		solution << "list : ";
		for (auto i : freq) solution << "{" << i.first << ":" << i.second << "} -> ";	
		solution << "\n";	
		return -1;
	}
};


class JJK_RESTAURANT_OPERATIONS
{
private:
	HuffTree_AVL New_customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;
	
public:

	void LAPSE(string name)
	{
		//* mã hóa HuffTree_AVL kết quả là 10 kí tự nhị phân cuối chuyển sang thập phân
		int result = New_customers_arrive.encode(name);
		if(result == -1) return;
		
		//* phân chia nhà hàng 
		if(result % 2 == 1) hash.insertAreaTable(result);
		else heap.insertAreaTable(result);
	}	

	//* xử lí nhà hàng gojo
	void KOKUSEN(){}
	void LIMITLESS(int num){}
	
	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num){}
	void CLEAVE(int num){}

	//* xử lý HuffTree_AVL
	void HAND(){}
};


