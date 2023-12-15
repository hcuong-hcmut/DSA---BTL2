#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<list>
#include <utility> 
#include <algorithm>
#include <sstream>
using namespace std;

class Node{
public:
    int weight;
    char c;
    int height;
    Node* left;
    Node* right;
    
    friend class HuffTree_AVL;
public:
    Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr): height(1), weight(weight), c(c), left(left), right(right) {}
};

//* cân bằng node yêu cầu xét mất cân bằng loại nào rồi quay nhưng count >= 3 thì dừng
//* trường hợp LL -> tính là count được cộng thêm 1
//* trường hợp RR -> tính là count được cộng thêm 1
//* trường hợp RL -> tính là count được cộng thêm 2
//* trường hợp LR -> tính là count được cộng thêm 2
//* nếu trường hợp LL cũng là LR -> xét như Trường hợp LL
//* nếu trường hợp RL cũng là RR -> xét như Trường hợp RR
//* yêu cầu dùng height để xử lí -> cấm dùng tính height đệ quy :<< độ phức tạp hơi mệt đó
//^ chú ý vì RL LR tính 2 lần nên khi count = 2 mà phải xử lí 1 này thì -> làm 1 lần rồi dừng

Node* rotateRight(Node* root) 
{
    //TODO
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
    //TODO
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
    //TODO
    if(node == NULL) return 0;
    return (node->left == NULL ? 0 : node->left->height) - (node->right == NULL ? 0 : node->right->height);
}

Node* balanceNode(Node* node, int& count) 
{
    //TODO
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

//* tiến hành đệ quy theo preOrder -> nếu count >= 3 thì dừng lại không cân bằng nữa
Node* balanceTree(Node* node, int& count)
{
    //TODO
    if (node == nullptr || count >= 3) {
        // If the node is null or the count is 3 or more, return the node as is.
        return node;
    }

    // Balance the current node
    node = balanceNode(node, count);

    if (node->left && count < 3) node->left = balanceTree(node->left, count);
    if (node->right && count < 3) node->right = balanceTree(node->right, count);

    return node;
}

Node* buildHuff(vector<pair<char, int>> freq)
{
    //* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
    //TODO: này không làm được đăng kí môn đi nha
    vector<Node*> build;
    for (auto& f : freq) {
        build.push_back(new Node(f.second, f.first));
    }
    // Sort by descending weight
    
    while(build.size() > 1)
    {
        //TODO: lấy ra node nhỏ nhất thứ nhất và nhỏ nhất thứ 2 (phần tử cuối vector)
        //TODO: tạo ra node nới có con bên trái là node nhỏ nhất và bên phải là node nhỏ nhất thứ 2 -> cập nhật weight, height của node mới
        //^ chú ý : cập nhật height, weight
        // Step 2: Extract the two nodes with the smallest weight.
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
    }		
    return build[0];
}



//*********** code bên dưới không bận tâm ***************************
bool areHuffmanTreesEqual(const Node* tree1, const Node* tree2);
void printHuffmanTree(const Node* tree);
std::string huffmanTreeToString(const Node* tree) ;
int main()
{
    //* test 1
    {
        vector<pair<char, int>> v = {{'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0', 
                                 new Node(2, 'c'),
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 1 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 1 \n";
    }

    //* test 2
    {
        vector<pair<char, int>> v = {{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 2 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 2 \n";
    }

    //* test 3
    {
        vector<pair<char, int>> v = {{'d',6}, {'c', 3}, {'b', 1}, {'a', 1}};
        Node* root = new Node(5, '\0',
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')),
                                new Node(11, '\0',
                                    new Node(3, 'c'),
                                    new Node(6, 'd')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 3 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 3 \n";
    }
    
    //* test 4
    {
        vector<pair<char, int>> v = {{'d',5}, {'c', 3}, {'b', 1}, {'a', 1}};
        Node* root = new Node(2, '\0',
                                new Node(10, '\0',
                                    new Node(5, 'd'),
                                    new Node(1, 'a')),
                                new Node(5, '\0',
                                    new Node(1, 'b'),
                                    new Node(3, 'c')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 4 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 4 \n";
    }


    //* test 5
    {
        vector<pair<char, int>> v = {{'d',5}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(2, '\0',
                                new Node(4, '\0',
                                    new Node(2, 'c'),
                                    new Node(1, 'a')),
                                new Node(9, '\0',
                                    new Node(1, 'b'),
                                    new Node(5, 'd')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 5 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 5 \n";
    }


    //* test 6
    {
        vector<pair<char, int>> v = {{'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(14, '\0',
                                    new Node(2, '\0',
                                        new Node(1, 'a'),
                                        new Node(1, 'b')),
                                    new Node(10, 'e')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 6 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 6 \n";
    }

    // //* test 7
    {
        vector<pair<char, int>> v = {{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[24]([10,e],[20,f]))";
        
        if(output_you != result)
        {
            cout << "fail test 7 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 7 \n";
    }

    // //* test 8
    {
        vector<pair<char, int>> v = {{'g', 20},{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[34]([24]([10,e],[20,f]),[20,g]))";
        
        if(output_you != result)
        {
            cout << "fail test 8 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 8 \n";
    }


    // //* test 9
    {
        vector<pair<char, int>> v = {{'h', 21}, {'g', 20},{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[34]([24]([10,e],[20,f]),[35]([20,g],[21,h])))";
        
        if(output_you != result)
        {
            cout << "fail test 9 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 9 \n";
    }
}

std::string huffmanTreeToString(const Node* tree) {
    std::stringstream ss;

    if (tree == nullptr) {
        return "";
    }

    if (tree->c) {
        ss << "[" << tree->weight << "," << tree->c << "]";
    } else {
        ss << "[" << tree->weight << "]";
    }

    if (tree->left != nullptr || tree->right != nullptr) {
        ss << "(";
        ss << huffmanTreeToString(tree->left);
        ss << ",";
        ss << huffmanTreeToString(tree->right);
        ss << ")";
    }

    return ss.str();
}


void printHuffmanTree(const Node* tree) {
    if (tree == nullptr) {
        return;
    }
    if(tree->c) std::cout << "[" << tree->weight << "," << tree->c << "]";
    else std::cout << "[" << tree->weight << "]";
    
    if (tree->left != nullptr || tree->right != nullptr) {
        std::cout << "(";
        printHuffmanTree(tree->left);
        std::cout << ",";
        printHuffmanTree(tree->right);
        std::cout << ")";
    }
}

bool areHuffmanTreesEqual(const Node* tree1, const Node* tree2) {
    // Nếu cả hai cây đều rỗng (nullptr), coi chúng là giống nhau
    if (tree1 == nullptr && tree2 == nullptr) {
        return true;
    }

    // Nếu chỉ một trong hai cây rỗng, coi chúng khác nhau
    if (tree1 == nullptr || tree2 == nullptr) {
        return false;
    }

    // So sánh giá trị và cấu trúc của hai nút
    return (tree1->weight == tree2->weight) &&
           (tree1->c == tree2->c) &&
           areHuffmanTreesEqual(tree1->left, tree2->left) &&
           areHuffmanTreesEqual(tree1->right, tree2->right);
}