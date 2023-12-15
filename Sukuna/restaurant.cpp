#include "main.h"


int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

//* nhà hàng su cờ na
class RESTAURANT_Sukuna{
	class Node;
private:
	vector<Node* > areaTable;  //! nơi lưu trữ các khu vực
	list<Node* > LRU; 		  //!  Least Recently Used này là cơ chế khu vực nào có khác vào nhà hàng lâu nhất
private:

	//* hàm gợi ý của anh thôi dùng hay không thì tùy các bạn nha -> nên suy nghĩ khác
	bool Compare(int index1, int index2)
	{
		if (areaTable[index1]->size() != areaTable[index2]->size()) {
        	return areaTable[index1]->size() < areaTable[index2]->size();
    	}

    	// If sizes are equal, compare based on their position in the LRU list
    	// The one with a lower position (closer to front) in LRU list is "smaller" for heap purposes
    	auto it1 = std::find(LRU.begin(), LRU.end(), areaTable[index1]);
    	auto it2 = std::find(LRU.begin(), LRU.end(), areaTable[index2]);
    	return std::distance(LRU.begin(), it1) < std::distance(LRU.begin(), it2);
	}

	void ReHeap_down(int index)
	{
		//TODO: với giá trị xét là areaTable[index].size()
		//TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		//TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất dùng list<Node* > LRU;
		//TODO: ví dụ khu A và khu B có số khách bằng nhau nếu khu A mới có khách vào thì so sánh min heap thì khu B đang nhỏ hơn khu A nên ở trên khu A
		int smallest = index; 
    	int left = 2 * index + 1; 
    	int right = 2 * index + 2; 

    	// Check if left child exists and is "smaller" than current node
    	if (left < areaTable.size() && Compare(left, smallest)) {
    	    smallest = left;
    	}

    	// Check if right child exists and is "smaller" than the smallest so far
   		if (right < areaTable.size() && Compare(right, smallest)) {
    	    smallest = right;
    	}

    	// If the smallest is not the current item, swap and continue heapifying down
    	if (smallest != index) {
    	    std::swap(areaTable[index], areaTable[smallest]);
    	    // Move the modified node to the top of the LRU list
        	moveTop(areaTable[smallest]);
        	ReHeap_down(smallest);
    	}
	}

	void ReHeap_up(int index)
	{
		//TODO: với giá trị xét là areaTable[index].size()
		//TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		//TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất
		//TODO: này xử lí tương tự reheap_down
		while (index != 0 && Compare(index, (index - 1) / 2)) {
        	// Swap with parent if current node is "smaller" according to Compare
        	std::swap(areaTable[index], areaTable[(index - 1) / 2]);
        	// Move the modified node to the top of the LRU list
        	moveTop(areaTable[index]);
        	index = (index - 1) / 2; // Move to the parent index
    	}
	}

	//* nếu node chưa tồn tại trong LRU thì thêm vô nếu tồn tại thì dịch nó lên đầu danh sách
	void moveTop(Node* node)
	{	
		//TODO: BƯỚC 1 Tìm vị trí của node trong danh sách
		auto it = std::find(LRU.begin(), LRU.end(), node); // Step 1: Find the node in LRU

		//TODO: BƯỚC 2 nếu nó tồn tại thì dịch nó lên đầu danh sách, nếu không thì insert ở đầu danh sách
		if (it != LRU.end()) {
        // Node is found, move it to the front of LRU
        	LRU.erase(it);
        	LRU.push_front(node);
    	} else {
        	// Node is not found, insert it at the front of LRU
        	LRU.push_front(node);
    	}
	}

	//* xóa một node ra khỏi danh sách liên kết không gần gọi delete nha vì đã dùng bên dưới hàm xóa
    void removeNode(Node* node)
	{
		//TODO: 
		for (auto it = LRU.begin(); it != LRU.end(); ++it) {
        	if (*it == node) {
        	    // Erase the node from the LRU list
        	    LRU.erase(it);
        	    break;
        	}
    	}
	}
public:
	RESTAURANT_Sukuna(){}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;
		//TODO TODO TODO TODO TODO bước 1


		//*bước 2: xem thử có khu này trong heap chưa để thêm vô 
		if(index == -1){
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}
		//*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào và tiến hàn reheap down bàn này xuống vì có số khách đông hơn
		else 
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}

	void remove_KEITEIKEN(int number)
	{
		if(areaTable.size() <= 0) return;

		//* đuổi num khách hàng tại num khu vực
		int numberRemove = number;
		while(areaTable.size() != 0 && number != 0){
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			solution << "remove customers in the area ID = " << areaTable[0]->ID << ": ";
			areaTable[0]->remove(numberRemove);
			solution << "\n";

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
			if(areaTable[0]->size() == 0)
			{
				swap(areaTable[0], areaTable[areaTable.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];

				//! xóa trong heap nữa
				areaTable.pop_back();
			}
			this->ReHeap_down(0);
			number --;
		}
 	}
//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void print_pre_order(int index, int number)
	{	
		if(index >= this->areaTable.size()) return;

		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_CLEAVE(int number)
	{
		if(number <= 0) return;

		solution << "Heap : ";
		for(auto it : this->areaTable)
		{
			int order = 0;
			for (auto ix : LRU) {
				if (ix == it) break;
				++order;
			}
			solution << it->ID << "(len="<< it->size() <<",index=" << order <<")" << " ";
		}
		solution << "\n";

		solution << "Heap : ";
		for(auto it : this->areaTable) solution << it->ID  << " ";
		solution << "\n";

		solution << "list LRU : ";
		for(auto it : LRU) solution << it->ID << " ";
		solution << "\n";


		print_pre_order(0, number);
	}
//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	class Node{
	private:
		int ID;					//! ID của bàn đó
		list<int> head; 		//! lưu danh sách các result của khách hàng
		friend class RESTAURANT_Sukuna;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		//* thêm vô đầu danh sách
		void insert(int result){head.push_front(result);}
		//* xóa ở cuối với số lượng là number cơ chế FIFO vô sớm thì cút sớm
		void remove(int number)
		{
			//TODO: xóa number khác hàng ở cuối danh sách tương ứng với vô sớm nhất 
			//^ gợi ý dùng hàm của linklist có sẵn
			//* thêm solution << head.back() << " "; để in ra
			while (number > 0 && !head.empty()) {
        		// Remove the last customer from the list
        		int customer = head.back();
        		head.pop_back();  // Or the appropriate method to remove the last element
        		solution << customer << " ";
        		number--;
    		}
		}
		//* print ra number khách hàng mới đến gần nhất theo cơ chế LIFO các khách hàng gần nhất
		void print(int number)
		{
			solution << "customers in the area ID = " << ID << ": ";
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				solution << *it << " ";
			}
			solution << "\n";
		}

	};

};


//* nhà hàng của sư phụ GOJO
class RESTAURANT_Gojo{
	//TODO: code đâu nén vô
};


class HuffTree_AVL{
	class Node;
private:
	Node* root;
public:
	int encode(string name){
		return stoi(name);
	}

	void print(){}
private:
	class Node{
	public:
		int weight;
		char c;
		int rankingPosition;
		Node* left;
		Node* right;
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c,Node* left = nullptr, Node* right = nullptr ): weight(weight), c(c), left(left), right(right) {}
		bool isLeaf() const { return left == nullptr && right == nullptr; }
	};
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
		//* mã hóa HuffTree_AVL kế quả là 10 kí tự nhị phân cuối chuyển sang thập phân
		int result = New_customers_arrive.encode(name);
		
		//* phân chia nhà hàng 
		if(result % 2 == 1) hash.insertAreaTable(result);
		else heap.insertAreaTable(result);
	}	

	//* xử lí nhà hàng gojo
	void KOKUSEN(){hash.remove_KOKUSEN();}
	void LIMITLESS(int num){hash.print_LIMITLESS(num);}
	
	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num){heap.remove_KEITEIKEN(num);}
	void CLEAVE(int num){heap.print_CLEAVE(num);}

	//* xử lý HuffTree_AVL
	void HAND(){New_customers_arrive.print();}
};


