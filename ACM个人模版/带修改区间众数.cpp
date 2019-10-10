//长度为n的序列 两种操作
//将[l, r]内的数全都赋值为 x。
//查询[l, r]中占主导地位的数字是哪个。 (出现次数一半以上，没有输出-1)
#include <bits/stdc++.h>
using namespace std;
const int N = 200222;
const int M = 200222;
const int K = 1000111;
int RAND() {
    static int seed = 1234567;
    seed = (1LL * seed * 127 + 87665) % 1000000007;
    return seed;
}
struct Domination {
    int x; // who takes [l..r) segment
    int dominator; // who dominates on segment coresponding for given subtree
    int score; // score of dominance
};
ostream& operator<<(ostream& out, const Domination& A) {
    out << "(" << A.dominator << "," << A.score << ")";
    return out;
}
template<class T>
struct Node {
    int left, right;
    int leftSon, rightSon;
 
    int priority;
    T info;
 
    void initializeFromItself();
    void merge(const Node<T>& another);
};
template<>
void Node<int>::initializeFromItself() {
    info = right - left;
}
template<>
void Node<int>::merge(const Node<int>& another) {
    info += another.info;
}
template<>
void Node<Domination>::initializeFromItself() {
    info.dominator = info.x;
    info.score = right - left;
}
template<>
void Node<Domination>::merge(const Node<Domination>& another) {
    if (info.dominator == another.info.dominator) {
        info.score += another.info.score;
    } else if (info.score >= another.info.score) {
        info.score -= another.info.score;
    } else {
        info.dominator = another.info.dominator;
        info.score = another.info.score - info.score;
    }
}
 
 
template<class T>
class NodePool {
public:
    static void init(int size) {
        NodePool<T>::pool.resize(size);
        NodePool<T>::emptyNodes.resize(size);
        for (int i = 0; i < size; ++i) {
            NodePool<T>::emptyNodes[i] = size - i - 1; // for debug
            NodePool<T>::pool[i].priority = RAND();
        }
        random_shuffle(begin(NodePool<T>::pool), end(NodePool<T>::pool));
    }
 
    static Node<T>& at(int pos) {
        return pool[pos];
    }
 
    // returns pointer to created node
    static int createNode(int l, int r) {
        int result = NodePool<T>::emptyNodes.back(); 
        NodePool<T>::emptyNodes.pop_back();
 
        auto& node = NodePool<T>::pool[result];
        node.left = l;
        node.right = r;
        node.leftSon = node.rightSon = -1;
 
        return result;
    }
 
public:
    static vector<int> emptyNodes;
    static vector<Node<T>> pool;
};
 
template<>
vector<int> NodePool<int>::emptyNodes {};
template<>
vector<Node<int>> NodePool<int>::pool {};
template<>
vector<int> NodePool<Domination>::emptyNodes {};
template<>
vector<Node<Domination>> NodePool<Domination>::pool {};
 
template<class T>
void update(Node<T>& node) {
    node.initializeFromItself();
    if (node.leftSon != -1) {
        node.merge(NodePool<T>::at(node.leftSon));
    }
    if (node.rightSon != -1) {
        node.merge(NodePool<T>::at(node.rightSon));
    }
}
 
// takes pointer to two roots
// returns root of merged tree
template<class T>
int merge(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
 
    auto& nodeA = NodePool<T>::at(a);
    auto& nodeB = NodePool<T>::at(b);
 
    if (nodeA.priority > nodeB.priority) {
        nodeA.rightSon = merge<T>(nodeA.rightSon, b);
        update(nodeA);
        return a;
    } else {
        nodeB.leftSon = merge<T>(a, nodeB.leftSon);
        update(nodeB);
        return b;
    }
}
 
// takes root x and number border
// splits in two trees, all keys [0..border) go to tree with root a
// other go to tree with root b
// May add no more than one vertex
template<class T>
void split(int x, int border, int& a, int& b) {
    if (x == -1) {
        a = -1;
        b = -1;
        return;
    }
 
    auto& root = NodePool<T>::at(x);
 
    if (root.left >= border) {
        b = x;
        split<T>(root.leftSon, border, a, root.leftSon);
    } else if (root.right <= border) {
        a = x;
        split<T>(root.rightSon, border, root.rightSon, b);
    } else {
        int wasRight = root.right;
        int wasLeftSon = root.leftSon;
        int wasRightSon = root.rightSon;
 
        int newNode = NodePool<T>::createNode(border, wasRight);
        NodePool<T>::at(newNode).info = root.info;
        NodePool<T>::at(newNode).initializeFromItself();
 
        root.right = border;
        root.rightSon = root.leftSon = -1;
        root.initializeFromItself();
         
        a = merge<T>(wasLeftSon, x);
        b = merge<T>(newNode, wasRightSon);
    }
    if (a != -1)
        update(NodePool<T>::at(a));
    if (b != -1)
        update(NodePool<T>::at(b));
}
 
template<class T>
void traverse(int x, void callback(int)) {
    if (x == -1) return;
    const auto& v = NodePool<T>::at(x);
    if (v.leftSon != -1) traverse<T>(v.leftSon, callback);
    callback(x);
    if (v.rightSon != -1) traverse<T>(v.rightSon, callback);
}
 
 
int IT;
int used[K];
int roots[K];
int dominationRoot = -1;
 
int leftBorder, rightBorder;
void deleter(int x) {
    int who = NodePool<Domination>::at(x).info.x;
    if (used[who] == IT) return;
    used[who] = IT;
 
    int lessRoot, root, moreRoot;
 
    split<int>(roots[who], leftBorder, lessRoot, root);
    split<int>(root, rightBorder, root, moreRoot);
     
    // one might return all nodes from root
    // with one more traverse, but we're contesters
 
    roots[who] = merge<int>(lessRoot, moreRoot);
}
 
char w[11];
 
int main() {
 
    NodePool<int>::init(N + 3 * M);
    NodePool<Domination>::init(N + 3 * M);
    int n;
    scanf("%d",&n);
    memset(roots, -1, sizeof(roots));
 
    for (int i = 1; i <= n; ++i) {
        int x;scanf("%d",&x);
        int newNode = NodePool<Domination>::createNode(i, i + 1);
        NodePool<Domination>::at(newNode).info.x = x;
        NodePool<Domination>::at(newNode).initializeFromItself();
        dominationRoot = merge<Domination>(dominationRoot, newNode);
 
        newNode = NodePool<int>::createNode(i, i + 1);
        NodePool<int>::at(newNode).initializeFromItself();
        roots[x] = merge<int>(roots[x], newNode);
    }
    int m;scanf("%d",&m);
    while (m--) {
        scanf("%s",w);
        if (w[0] == 's') {
            int l, r, x; // set x on [l, r]
            scanf("%d%d%d",&l,&r,&x);
            ++r;
 
            int lessRoot, root, moreRoot;
            split<Domination>(dominationRoot, l, lessRoot, root); // +1 domination node
            split<Domination>(root, r, root, moreRoot); // +1 domination node
             
            ++IT;
            leftBorder = l; rightBorder = r;
            traverse<Domination>(root, deleter);
            root = NodePool<Domination>::createNode(l, r); // +1 domination node
            NodePool<Domination>::at(root).info.x = x;
            NodePool<Domination>::at(root).initializeFromItself();
            dominationRoot = merge<Domination>(lessRoot, root);
            dominationRoot = merge<Domination>(dominationRoot, moreRoot);
            split<int>(roots[x], l, lessRoot, moreRoot); // +1 int node (actually no, but let's assume)
            root = NodePool<int>::createNode(l, r); // +1 int node
            NodePool<int>::at(root).initializeFromItself();
             
            roots[x] = merge<int>(lessRoot, root);
            roots[x] = merge<int>(roots[x], moreRoot);
        } else {
            int l, r; scanf("%d%d",&l,&r);
            ++r;
             
            int lessRoot, root, moreRoot;
            split<Domination>(dominationRoot, l, lessRoot, root); // +1 domination node
            split<Domination>(root, r, root, moreRoot); // +1 domination node
            int candidate = NodePool<Domination>::at(root).info.dominator;
            dominationRoot = merge<Domination>(lessRoot, root);
            dominationRoot = merge<Domination>(dominationRoot, moreRoot);
            split<int>(roots[candidate], l, lessRoot, root);
            split<int>(root, r, root, moreRoot);
            int count = NodePool<int>::at(root).info;
            roots[candidate] = merge<int>(lessRoot, root);
            roots[candidate] = merge<int>(roots[candidate], moreRoot);
            if (count + count > r - l) {
                printf("%d\n",candidate);
            } else {
                puts("-1");
            }
        }
    }
    return 0;
}