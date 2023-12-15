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
class RESTAURANT_Gojo{
	class Tree_BST;
private:
	vector<Tree_BST> areaTable;
public:
	RESTAURANT_Gojo():areaTable(MAXSIZE + 1){}
	void insertAreaTable(int result)
	{
		//* khách mới vô thích chọn khu có ID = result % MAXSIZE + 1 dắt nó tới chỗ đó rồi nén vô cho nhân viên khu đó xử lí
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result); 
	}

	void remove_KOKUSEN()
	{
		for(int i = 1; i < MAXSIZE + 1; i++) areaTable[i].remove();
 	}

	void print_LIMITLESS(int number)
	{
		if(number <= 0 || number > MAXSIZE) return;
		areaTable[number].print();
	}
private:
	class Tree_BST{
		class Node;
	private:
		Node* root;	
		queue<int> queueTime; 
	public:
		Tree_BST():root(nullptr){}
		~Tree_BST()
		{
			while(!queueTime.empty())
			{
				int temp = queueTime.front();		
				queueTime.pop(); 						
				root = remove_recursive(root ,temp);
			}
		}
		int size(){
			return queueTime.size();
		}
		Node* insert_recursive(Node* node, int result)
		{
			if (node == nullptr) {
            	Node* newNode = new Node(result);
            	queueTime.push(result);  // When a new node is created, push it to queueTime.
            	return newNode;
        	}

        	if (result == node->result) {
            	node->right = insert_recursive(node->right, result);  // If equal, go to the right.
        	} else if (result < node->result) {
            	node->left = insert_recursive(node->left, result);   // If lesser, go to the left.
        	} else {
            	node->right = insert_recursive(node->right, result); // If greater, go to the right.
        	}

        	return node; // Return the (possibly) updated node.
		}

		void insert(int result){
			root = insert_recursive(root, result);
		}

		Node* remove_recursive(Node* node,int result)
		{	
			if (node == nullptr) return nullptr; // Node not found, nothing to do.

 			if (result < node->result) {
            	// Go left if the key to be deleted is smaller than the root's key.
            	node->left = remove_recursive(node->left, result);
        	} else if (result > node->result) {
            	// Go right if the key to be deleted is greater than the root's key.
            	node->right = remove_recursive(node->right, result);
        	} else {
            	// Node with only one child or no child.
            	if (node->left == nullptr) {
            	    Node* temp = node->right;
            	    delete node;
            	    return temp;
            	} else if (node->right == nullptr) {
            	    Node* temp = node->left;
            	    delete node;
            	    return temp;
            	}

            	// Node with two children: Get the inorder successor (smallest in the right subtree).
            	Node* temp = minValueNode(node->right);

            	// Copy the inorder successor's content to this node.
            	node->result = temp->result;

            	// Delete the inorder successor.
            	node->right = remove_recursive(node->right, temp->result);
        	}
        	return node; // Return the (possibly) updated node.
 		}

		Node* minValueNode(Node* node) {
    		Node* current = node;
    		// loop down to find the leftmost leaf
    		while (current && current->left != nullptr) {
    		    current = current->left;
    		}
    		return current;
		}

		int CountNode(Node* node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}
		unsigned long long factorial(int n) {
    		unsigned long long result = 1;
    		for (int i = 2; i <= n; i++) {
        		result *= i;
    		}
    		return result;
		}

		unsigned long long permutationFormula(int n, int k)
		{
			return factorial(n) / (factorial(k) * factorial(n - k));
		}

		unsigned long long DFS(Node* node)
		{
			if (node == NULL) return 1;
    
    		int leftCount = CountNode(node->left);
    		int rightCount = CountNode(node->right);
    
    		unsigned long long leftWays = DFS(node->left);
    		unsigned long long rightWays = DFS(node->right);
    
    		// The number of unique BSTs is the number of ways to combine the left and right subtrees
    		// times the number of unique BSTs within each subtree
    		return permutationFormula(leftCount + rightCount, leftCount) * leftWays * rightWays;
		}

		void remove(){
			if(queueTime.empty()) return;
			
			unsigned long long number = DFS(root) % MAXSIZE;
	
			while(number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		
				queueTime.pop(); 					
				root = remove_recursive(root ,temp);
				number --;
			}
		}
		void print_recursive(Node* node)
		{
			if(node != NULL){
				print_recursive(node->left);
				solution << node->result << "\n";
				print_recursive(node->right);
			}
		}
		void print(){print_recursive(root);}
	private:
		class Node{
		private:
			int result;
			Node* left;
			Node* right;
			friend class Tree_BST;
		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};

};

//* nhà hàng su cờ na
class RESTAURANT_Sukuna{
	class Node;
private:
	vector<Node* > areaTable;
	list<Node* > LRU; 
private:
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
		auto it = std::find(LRU.begin(), LRU.end(), node); // Step 1: Find the node in LRU

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
	~RESTAURANT_Sukuna(){
		for(int i = 0; i < areaTable.size(); i++){
			delete areaTable[i];
			COUNTDELETE ++;
		}
	}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;

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

		//* TẠO ra heap mới sao chép từ heap cũ
		vector<Node* > areaTableNew(areaTable.begin(), areaTable.end());
		queue<Node* > listDelete; //! danh sách các khu cấn xóa
		for(int i = 0;  areaTable.size() && i < number; i++)
		{
			//* lấy ra phần tử đầu tiên trong heap
			Node* nodeDelete = areaTable[0];
			swap(areaTable[0], areaTable[areaTable.size() - 1]);
			areaTable.pop_back();
			this->ReHeap_down(0);


			//* đưa vào danh sách cần xóa
			listDelete.push(nodeDelete);
		}

		//* trả lại heap
		areaTable = areaTableNew;

		//* đuổi num khách hàng tại num khu vực
		while(listDelete.size()){
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			Node* nodeDelete = listDelete.front();
			listDelete.pop();

			nodeDelete->remove(number);

			//* tìm vị trí của nó trong heap
			int index = 0;
			while(areaTable[index] !=  nodeDelete) index++;

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
			if(nodeDelete->size() == 0)
			{
				swap(areaTable[index], areaTable[areaTable.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];
				COUNTDELETE ++;

				//! xóa trong heap nữa
				areaTable.pop_back();
			}
			this->ReHeap_down(index);
		}
	}

	void print_pre_order(int index, int number)
	{	
		if(index >= this->areaTable.size() || number <= 0) return;
		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_LIMITLESS(int number){print_pre_order(0, number);}
private:
	class Node{
	private:
		int ID;					
		list<int> head; 	
		friend class RESTAURANT_Sukuna;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result){head.push_front(result);}
		void remove(int number)
		{
			while(number != 0 && !head.empty())
			{
				solution << head.back() << "-" <<ID << "\n";
				head.pop_back();
				number--;
			}
		}
		void print(int number)
		{
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				solution << ID << "-" << *it  << "\n";
			}
		}
	};
};



class HuffTree_AVL{
	class Node;
private:
	Node* root = nullptr;
public:
	~HuffTree_AVL(){clear(root);}
	void clear(Node* node)
	{
		if(node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	char caesarCipher(char ch, int shift) {
    	if (isalpha(ch)) {
    	    char offset = isupper(ch) ? 'A' : 'a';
    	    return (char)((ch - offset + shift) % 26 + offset);
    	}
    	return ch;
	}

	vector<pair<char, int>> string_Processing(string& name)
	{
		//*bước 1
		vector<pair<char, int>> freq_prev;
		for (char& ch : name) {
        	auto it = find_if(freq_prev.begin(), freq_prev.end(),
                               [ch](const pair<char, int>& p) { return p.first == ch; });
        	if (it != freq_prev.end()) {
            	it->second++;
        	} else {
            	freq_prev.push_back(make_pair(ch, 1));
        	}
    	}
		//! thêm
		if(freq_prev.size() < 3) return {};

		//*bước 2, 3, 4
		string updated_name;
    	for (char& ch : name) {
        	auto it = find_if(freq_prev.begin(), freq_prev.end(),
            	                   [ch](const pair<char, int>& p) { return p.first == ch; });
        	if (it != freq_prev.end()) {
        	    char ciphered_char = caesarCipher(ch, it->second);
        	    updated_name.push_back(ciphered_char);
        	}
    	}

    	freq_prev.clear();
    	for (char& ch : updated_name) {
    	    auto it = find_if(freq_prev.begin(), freq_prev.end(),
    	                           [ch](const pair<char, int>& p) { return p.first == ch; });
    	    if (it != freq_prev.end()) {
    	        it->second++;
    	    } else {
    	        freq_prev.push_back(make_pair(ch, 1));
    		}
    	}

    	name = updated_name;

    	// Step 3: Merge frequencies of the same characters
    	vector<pair<char, int>> freq;
    	for (auto& p : freq_prev) {
    	    auto it = find_if(freq.begin(), freq.end(), [p](const pair<char, int>& elem) {
    	        return elem.first == p.first;
    	    });

	        if (it != freq.end()) {
	            // Character found, add to the frequency
    	        it->second += p.second;
    	    } else {
    	        // Character not found, add a new pair
    	        freq.push_back(p);
    	    }
    	}

    	// Step 4: Sort the frequency vector
    	sort(freq.begin(), freq.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
    	    if (a.second != b.second) return a.second > b.second;
    	    else{
    	        if (islower(a.first) && islower(b.first)) {
    	        return a.first > b.first; // Lowercase characters in descending order
    	    } else if (isupper(a.first) && isupper(b.first)) {
    	        return a.first > b.first; // Uppercase characters in descending order
    	    } else {
    	        return (bool)(isupper(a.first)); // Uppercase characters take precedence over lowercase
    	    }
    	    }
        
    	});

    	return freq;
	}

	Node* rotateRight(Node* root) 
	{
    	Node* temp = root->left;
    	Node* temp2 = temp->right;

    	root->left = temp2;
    	temp->right = root;

    	root->height = 1 + max((root->left == NULL) ? 0 : root->left->height, (root->right == NULL) ? 0 : root->right->height);
    	temp->height = 1 + max((temp->left == NULL) ? 0 : temp->left->height, (temp->right == NULL) ? 0 : temp->right->height);
    	return temp;
	}

	Node* rotateLeft(Node* root) 
	{
	    Node* temp = root->right;
	    Node* temp2 = temp->left;

	    root->right = temp2;
	    temp->left = root;

	    root->height = 1 + max((root->left == NULL) ? 0 : root->left->height, (root->right == NULL) ? 0 : root->right->height);
	    temp->height = 1 + max((temp->left == NULL) ? 0 : temp->left->height, (temp->right == NULL) ? 0 : temp->right->height);
	    return temp;
	}

	int getBalanceState(Node* node) 
	{
	    if(node == NULL) return 0;
	    return (node->left == NULL ? 0 : node->left->height) - (node->right == NULL ? 0 : node->right->height);
	}


	Node* balanceNode(Node* node, int& count) 
	{
	    if (node == nullptr) return node;
	    int balance = getBalanceState(node);
	    if(balance > 1)
	    {
	        if(node->left->left->height >= node->left->right->height)
	        {	
            	count += 1; // Increment count for LL rotation
            	return rotateRight(node);
	        }
	        else
	        {
	            node->left = rotateLeft(node->left);
	            count += 2; // Increment count for LR rotation
	            return rotateRight(node);
	        }
	    }
	    else if(balance < -1)
	    {
	        if(node->right->right->height >= node->right->left->height)
	        {
	            count += 1; // Increment count for RR rotation
	            return rotateLeft(node);
	        }
	        else
	        {
	            node->right = rotateRight(node->right);
	            count += 2; // Increment count for RL rotation	
	            return rotateLeft(node);
	        }
	    }

	    node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));

	    return node;
	}

	Node* balanceTree(Node* node, int count = 0)
	{
		if(node == nullptr  || count == 1) return node;	//!count >= 3
		node = balanceNode(node, count);
		node->left = balanceTree(node->left, count);
		node->right = balanceTree(node->right, count);
		return node;
	}

	Node* buildHuff(vector<pair<char, int>> freq)
	{
		vector<Node*> build;
		//TODO:
		for (auto& f : freq) {
        	build.push_back(new Node(f.second, f.first));
    	}

		while(build.size() > 1)
		{
			Node* leftChild = build.back(); build.pop_back();
        	Node* rightChild = build.back(); build.pop_back();

	        // Create a new node with these two nodes as children.
	        Node* parent = new Node(leftChild->weight + rightChild->weight, '\0', leftChild, rightChild);

	        // Update height for the new parent node.
	        parent->height = 1 + max(leftChild->height, rightChild->height);

	        // Balance the tree with the newly created node.
	        int count = 0;
	        parent = balanceTree(parent, count);

	        // Insert the new node into build in a sorted manner.
	        auto it = lower_bound(build.begin(), build.end(), parent, [](Node* existingNode, Node* newNode) {
	            return existingNode->weight > newNode->weight; // Descending order sort.
	        });
	        build.insert(it, parent);
				//TODO: đưa node mới vào trong vector -> đảm bảo vector luôn giảm dần như ban đầu	
				//^ chú ý nếu bằng nhau thì xem như node mới luôn lớn hơn các node bằng giá trị weight -> ý là xếp nó gần head hơn
		}		
		return build[0];
	}
	void encodingHuffman_rec(vector<string>& encoding, Node* node, string s = "")
	{
    	if (node == nullptr) {
    	    return;
    	}
    	if (node->isChar()) {
    	    encoding[node->c] = s;
    	} else {
    	    encodingHuffman_rec(encoding, node->left, s + '0');  // Left child adds '0'
    	    encodingHuffman_rec(encoding, node->right, s + '1'); // Right child adds '1'
    	}
	}
	int encodingHuffman(Node * root,string nameCaesar)
	{
    	if (root == nullptr) return 0;
    	if (root->left == nullptr && root->right == nullptr) {
	        // Special case: only one character in the tree
	        return nameCaesar.length(); // Every character encodes to '0'
	    }
	    //* bước 1: lấy chuỗi kết quả của các kí tự đã mã hóa
	    //* ví dụ cây 2('a', 'b') ta lưu encoding['a'] = '0' và encoding['b'] = '1'
	    vector<string> encoding(256, "");
	    encodingHuffman_rec(encoding, root);

	    //* bước 2 lấy ra 10 kí tự nhị phân cuối sau khi mã hóa nameCaesar thành mã nhị phân lấy từ phải đên trái 
	    // Step 2: Convert the Caesar ciphered name to a binary string using the Huffman codes
	    string binaryEncoding = "";
	    for (char ch : nameCaesar) {
	        binaryEncoding += encoding[ch];
	    }

	    // Ensure we get the last 10 binary digits from the binaryEncoding
	    string lastTenBinary = binaryEncoding.substr(max(0, (int)binaryEncoding.length() - 10));
	    reverse(lastTenBinary.begin(), lastTenBinary.end());
	    // Step 3: Convert the last 10 binary digits to a decimal number
	    int result = 0;
	    int base = 1;
	    for (int i = lastTenBinary.length() - 1; i >= 0; --i) {
	        result += (lastTenBinary[i] == '1' ? base : 0);
	        base *= 2;
	    }

	    //* bước 3 mã hóa binary sang thập phân -> này ez rồi
	    //* kiểm tra test thôi nếu bạn thầy mình bị sai
	    // cout << "nameCaesar = " << nameCaesar << endl;
	    // cout << "encoding : ";
	    // for(int i = 0; i < encoding.size(); i++) 
	    // {
	    //     if(encoding[i] != "") cout << char(i) << "=" << encoding[i] << " - ";
	    // }
	    // cout << "\nbinary = " << binary << endl;
	    // cout << "result = " << result << endl;
	    //********************

	    return result;
	}

	int encode(string name){

		//* bước 1 xử lí chuỗi thu được list để tới phần sau
		vector<pair<char, int>> freq  = this->string_Processing(name);
		if(freq.size() == 0) return -1;


		// for (int i = 0; i <freq.size();i++){ //! BỎ hết khối luôn
		// 	freq_LAPSE.push_back({freq[i].first, freq[i].second});
		// }
		// this->clear(root);
		// root = this->buildHuff(freq);
		// if(root->left == nullptr && root->right == nullptr) return 0; 
		
		int result = this->encodingHuffman(root ,name);

		return result;
	}

	void print_recursive(Node* node){
		if(node == nullptr) return;
		print_recursive(node->left);
		if(node->c == '\0') solution << node->weight << "\n";
		else solution << node->c << "\n";
		print_recursive(node->right);
	}
	void print_HAND(){print_recursive(root);}

private:
	class Node{
	public:
		int weight;
		char c;
		int height;
		Node* left;
		Node* right;
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ):  weight(weight), c(c), left(left), right(right) {}
		bool isChar() const { return c != '\0'; }
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

		if(name[0] >= '0' && name[0] <= '9') //! BỎ lúc nộp
		{
			int result = stoi(name);
			if(result % 2 == 1) hash.insertAreaTable(result);
			else heap.insertAreaTable(result);
			return;
		}

		int result = New_customers_arrive.encode(name);
		if(result == -1) return;

		if(result % 2 == 1) hash.insertAreaTable(result);
		else heap.insertAreaTable(result);
	}	

	//* xử lí nhà hàng gojo
	void KOKUSEN(){
		hash.remove_KOKUSEN();
	}
	void LIMITLESS(int num){
		hash.print_LIMITLESS(num);
	}
	
	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num){
		heap.remove_KEITEIKEN(num);
	}
	void CLEAVE(int num){
		heap.print_LIMITLESS(num);
	}

	//* in ra HuffTree_AVL
	void HAND(){
		New_customers_arrive.print_HAND();
	}
};

void simulate_test_case(string filename) //! BỎ hết khối luôn
{
	solution.flush();
	//* nhập file
	ifstream ss(filename);
	if (ss.fail())
	{
		cout << "ERROR: " << filename << endl;
		return;
	}

	string str, name;
	int num, line = 2;
	ss >> str; ss >> MAXSIZE; 
	JJK_RESTAURANT_OPERATIONS* NOT_LIKE_CODE = new JJK_RESTAURANT_OPERATIONS();
	solution << "MAXSIZE " << MAXSIZE << "\n";
	//! xử lí file
	while (ss >> str)
	{

		freq_LAPSE = {};
		result_LAPSE = 0;
		root_LAPSE = "";
		number_KOKUSEN = {};
		root_before_KOKUSEN = {};
		root_after_KOKUSEN = {};
		Heap_before_KEITEIKEN = {};
		Heap_after_KEITEIKEN = {};
		customers_before_KEITEIKEN = {};
		customers_after_KEITEIKEN = {};





		solution << "Line " << line << ": " << str << " ";
		if (str == "LAPSE") // LAPSE <NAME>
		{
			ss >> name;
			solution << name << "\n";
			NOT_LIKE_CODE->LAPSE(name);
			if(name[0] < '0' || name[0] > '9')
			{
				solution << "freq_LAPSE : ";
				for(auto i : freq_LAPSE)
				{
					solution << "{" << i.first << "," << i.second << "} ";
				}
				solution << "\n";
				solution << "result_LAPSE : " << result_LAPSE << "\n";
				solution << "root_LAPSE : " << root_LAPSE << "\n";
			}
		}
		else if (str == "KOKUSEN") // KOKUSEN
		{
			solution << "\n";
			NOT_LIKE_CODE->KOKUSEN();

			solution << "number_KOKUSEN : ";
			for(auto i : number_KOKUSEN)
			{
				solution << i << " ";
			}
			solution << "\n";

			solution << "root_before_KOKUSEN : \n";
			for(auto i :root_before_KOKUSEN)
			{
				solution << "AreaTable " << i << "\n";
			}

			solution << "root_after_KOKUSEN : \n";
			for(auto i : root_after_KOKUSEN)
			{
				solution << "AreaTable " << i << "\n";
			}


		}
		else if (str == "KEITEIKEN") // KEITEIKEN <NUM>
		{
			ss >> num;
			solution << num << "\n";
			NOT_LIKE_CODE->KEITEIKEN(num);



			solution << "Heap_before_KEITEIKEN : ";
			for(auto i : Heap_before_KEITEIKEN)
			{
				solution << "{ID=" << i.first << ",Len=" << i.second << "} ";
			}
			solution << "\n";

			solution << "customers_before_KEITEIKEN : \n";
			for(auto i :customers_before_KEITEIKEN)
			{
				solution << "AreaTable " << i << "\n";
			}	
		


			solution << "Heap_after_KEITEIKEN : ";
			for(auto i : Heap_after_KEITEIKEN)
			{
				solution << "{ID=" << i.first << ",Len=" << i.second << "} ";
			}
			solution << "\n";

			solution << "customers_after_KEITEIKEN : \n";
			for(auto i :customers_after_KEITEIKEN)
			{
				solution << "AreaTable " << i << "\n";
			}	
		}
		else if (str == "HAND") // HAND
		{
			solution << "\n";
			NOT_LIKE_CODE->HAND();
		}		
		else if (str == "LIMITLESS") // LIMITLESS <NUM>
		{
			ss >> num;
			solution << num << "\n";
			NOT_LIKE_CODE->LIMITLESS(num);
		}		
		else if (str == "CLEAVE") // CLEAVE <NUM>
		{
			ss >> num;
			solution << num << "\n";
			NOT_LIKE_CODE->CLEAVE(num);
		}		
		line ++;		
	}

	delete NOT_LIKE_CODE;
}


void simulate(string filename)
{
	//! BỎ hết khối luôn 2 dòng
	simulate_test_case(filename);
	return;


	ifstream ss(filename);
	string str, name;
	int num;

	ss >> str; ss >> MAXSIZE; //* nhập maxsize đầu tiên

	JJK_RESTAURANT_OPERATIONS* NOT_LIKE_CODE = new JJK_RESTAURANT_OPERATIONS();
	// //* xử lí file
	while (ss >> str)
	{
		if (str == "LAPSE") // LAPSE <NAME>
		{
			ss >> name;
			NOT_LIKE_CODE->LAPSE(name);
		}
		else if (str == "KOKUSEN") // KOKUSEN
		{
			NOT_LIKE_CODE->KOKUSEN();
		}
		else if (str == "KEITEIKEN") // KEITEIKEN <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->KEITEIKEN(num);
		}
		else if (str == "HAND") // HAND
		{
			NOT_LIKE_CODE->HAND();
		}		
		else if (str == "LIMITLESS") // LIMITLESS <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->LIMITLESS(num);
		}		
		else if (str == "CLEAVE") // CLEAVE <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->CLEAVE(num);
		}				
	}
	delete NOT_LIKE_CODE;
}

