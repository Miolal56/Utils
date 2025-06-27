#include <bits/stdc++.h>
#define lld long long int
using  namespace std;

// Custom headers
#include "Trie.h"
#include "SegmentTree.h"
#include "FenwickTree.h"
#include "KDTree.h"
#include "BloomFilter.h"
#include "AVLTree.h"
#include "SkipList.h"
#include "Treap.h"
#include "SplayTree.h"
#include "KaryHeap.h"
#include "VanEmdeBoasTree.h"
#include "RadixTree.h"

// Debug controller
#define DEBUG_ALL 1
//***********
#define DEBUG_ALL_TEST 0 || DEBUG_ALL
#define DEBUG_ALL_TEST_CUSTOM 0 || DEBUG_ALL
//***********
#define DEBUG_TRIE 0 || DEBUG_ALL_TEST
#define DEBUG_SEGMENT_TREE 0 || DEBUG_ALL_TEST
#define DEBUG_FENWICK_TREE 0 || DEBUG_ALL_TEST
#define DEBUG_KD_TREE 0 || DEBUG_ALL_TEST
#define DEBUG_BLOOM_FILTER 0 || DEBUG_ALL_TEST
#define DEBUG_CUSTOM_BLOOM_FILTER 0 || DEBUG_ALL_TEST_CUSTOM
#define DEBUG_AVL_TREE 0 || DEBUG_ALL_TEST
#define DEBUG_SKIP_LIST 0 || DEBUG_ALL_TEST
#define DEBUG_TREAP 0 || DEBUG_ALL_TEST
#define DEBUG_SPLAY_TREE 0 || DEBUG_ALL_TEST
#define DEBUG_KARY_HEAP 0 || DEBUG_ALL_TEST
#define DEBUG_BOAS_TREE 0 || DEBUG_ALL_TEST
#define DEBUG_RADIX_TREE 0 || DEBUG_ALL_TEST
//***********

// Method to compare two vectors
int equal(vector<int> &a, vector<int> &b);

// Methods to run every structure
void ProvaTrie();
void ProvaSegmentTree();
void ProvaFenwickTree();
void ProvaKDTree();
void ProvaBloomFilter();
void ProvaCustomBloomFilter();
void ProvaAVLTree();
void ProvaSkipList();
void ProvaTreap();
void ProvaSplayTree();
void ProvaKaryHeap();
void ProvaVanEmdeBoasTree();
void ProvaRadixTree();

// Results of each previous method
vector<int> output;

// Expected results of previous methods
vector<vector<int>> expected_output = {
        {1, 1, 1, 1, 0, 0, 0, 1},
        {1, 4, 9, 78, 35, 1, 4, 20, 479001600, 15120},
        {1, 2, 3, 9, 78, 35, 10, 20},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {3, 6, 7, 9, 12, 17, 19, 21, 25, 26},
        {40, 60, 70, 80},
        {1},
        {9, 8, 5, 6, 4, 7, 3},
        {1, 0, 0},
        {1, 2, 2, 0, 1, 4}
};

// Main method
int main(){
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    string a;
    int initial = 1;
    int end = 13;
    for(int n = initial; n <= end; ++n) {
        switch (n) {
            case 1:
                printf("Trie running...\n");
                ProvaTrie();
                break;
            case 2:
                printf("Segment Tree running...\n");
                ProvaSegmentTree();
                break;
            case 3:
                printf("Fenwick Tree running...\n");
                ProvaFenwickTree();
                break;
            case 4:
                printf("KD-Tree running...\n");
                ProvaKDTree();
                break;
            case 5:
                printf("Bloom Filter running...\n");
                ProvaBloomFilter();
                break;
            case 6:
                printf("Custom Bloom Filter running...\n");
                ProvaCustomBloomFilter();
                break;
            case 7:
                printf("AVL Tree running...\n");
                ProvaAVLTree();
                break;
            case 8:
                printf("Skip List running...\n");
                ProvaSkipList();
                break;
            case 9:
                printf("Treap running...\n");
                ProvaTreap();
                break;
            case 10:
                printf("Splay Tree running...\n");
                ProvaSplayTree();
                break;
            case 11:
                printf("K-ary Heap running...\n");
                ProvaKaryHeap();
                break;
            case 12:
                printf("Radix Tree running...\n");
                ProvaRadixTree();
                break;
            case 13:
                printf("Van Emde Boas Tree running...\n");
                ProvaVanEmdeBoasTree();
                break;
        }
        if(!equal(output, expected_output[n - 1])) {
            printf("FAILURE\n\n");
            cout.flush();
            break;
        } else printf("SUCCESS\n\n");
    }
    return 0;
}

int equal(vector<int> &a, vector<int> &b){
    if(a.size() != b.size()) return 0;
    int flag = 1;
    for(int i = 0; i < a.size(); ++i){
        if(a[i] != b[i]) {
            flag = 0;
            cout << "At index " << i << " -> expected: " << b[i] << " / received: " << a[i] << "\n";
        }
    }
    return flag;
}

void ProvaTrie(){
    output.clear();
    // Initialize the Trie structure
    char voc[] = {'a', 'b', 'c', 'd', 'e'};

#if DEBUG_TRIE
    printf("Creating structure\n");
#endif

    Trie trie(voc, 5);

#if DEBUG_TRIE
    printf("Start inserting\n");
#endif

    // Insert words inside the Trie
    trie.put("aba");
    trie.put("ab");
    trie.put("ec");
    trie.put("eca");

    // Search if words are inside the Trie
#if DEBUG_TRIE
    printf("%s\n", trie.toString().c_str());
    printf("Start searching:\n");
    printf("%s %d\n", "aba", trie.search("aba"));
    printf("%s %d\n", "ab", trie.search("ab"));
    printf("%s %d\n", "ec", trie.search("ec"));
    printf("%s %d\n", "eca", trie.search("eca"));
    printf("%s %d\n", "ece", trie.search("ece"));
    printf("%s %d\n", "ecam", trie.search("ecam"));
#endif

    output.push_back(trie.search("aba"));
    output.push_back(trie.search("ab"));
    output.push_back(trie.search("ec"));
    output.push_back(trie.search("eca"));
    output.push_back(trie.search("ece"));
    output.push_back(trie.search("ecam"));

    // Remove a word from the Trie
    trie.remove("eca");

#if DEBUG_TRIE
    //Search again inside the Trie
    printf("%s %d\n", "eca", trie.search("eca"));
    printf("%s %d\n", "ec", trie.search("ec"));
    printf("DONE!\n");
#endif

    output.push_back(trie.search("eca"));
    output.push_back(trie.search("ec"));
}

int add(int a, int b){
    return a + b;
}

int multiply(int a, int b){
    return a * b;
}

// driver program to test the above function
void ProvaSegmentTree(){
    output.clear();
    // Initialize the Segment Tree
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    SegmentTree<int> segmentTree(a, add, 0);

    //Do custom calculations using the Segment Tree
#if DEBUG_SEGMENT_TREE
    printf("%s\n", segmentTree.toString().c_str());
    printf("%d\n", segmentTree.get(0, 0));//1
    printf("%d\n", segmentTree.get(3, 3));//4
    printf("%d\n", segmentTree.get(3, 4));//9
    printf("%d\n", segmentTree.get(0, 11));//78
    printf("%d\n", segmentTree.get(4, 8));//35
#endif

    output.push_back(segmentTree.get(0, 0));
    output.push_back(segmentTree.get(3, 3));
    output.push_back(segmentTree.get(3, 4));
    output.push_back(segmentTree.get(0, 11));
    output.push_back(segmentTree.get(4, 8));

    SegmentTree<int> multiplier = SegmentTree(a, multiply, 1);

#if DEBUG_SEGMENT_TREE
    printf("%s\n", multiplier.toString().c_str());
    printf("%d\n", multiplier.get(0, 0));//1
    printf("%d\n", multiplier.get(3, 3));//4
    printf("%d\n", multiplier.get(3, 4));//20
    printf("%d\n", multiplier.get(0, 11));//479001600
    printf("%d\n", multiplier.get(4, 8));//15120
#endif
    output.push_back(multiplier.get(0, 0));
    output.push_back(multiplier.get(3, 3));
    output.push_back(multiplier.get(3, 4));
    output.push_back(multiplier.get(0, 11));
    output.push_back(multiplier.get(4, 8));
}

void ProvaFenwickTree(){
    output.clear();
    // Initialize the Fenwick Tree
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    FenwickTree<int> fenwickTree(a, 12, 0);

    // Do calculations using the Fenwick Tree
#if DEBUG_FENWICK_TREE
    printf("%s\n", fenwickTree.toString().c_str());
    printf("%d\n", fenwickTree.getSum(0, 0));//1
    printf("%d\n", fenwickTree.getSum(1, 1));//2
    printf("%d\n", fenwickTree.getSum(2, 2));//3
    printf("%d\n", fenwickTree.getSum(3, 4));//9
    printf("%d\n", fenwickTree.getSum(0, 11));//78
    printf("%d\n", fenwickTree.getSum(4, 8));//35
    fenwickTree.updateBIT(4, 10);
    printf("%d\n", fenwickTree.getSum(4, 4));//10
    printf("%d\n", fenwickTree.getSum(3, 5));//20
    fenwickTree.updateBIT(4, 5);
#endif

    output.push_back(fenwickTree.getSum(0, 0));
    output.push_back(fenwickTree.getSum(1, 1));
    output.push_back(fenwickTree.getSum(2, 2));
    output.push_back(fenwickTree.getSum(3, 4));
    output.push_back(fenwickTree.getSum(0, 11));
    output.push_back(fenwickTree.getSum(4, 8));
    fenwickTree.updateBIT(4, 10);
    output.push_back(fenwickTree.getSum(4, 4));
    output.push_back(fenwickTree.getSum(3, 5));
    fenwickTree.updateBIT(4, 5);
}

void ProvaKDTree(){
    output.clear();
    // Initialize the KD-Tree
    array<int, 2> a[5] = {{3, 6}, {2, 2}, {4, 7}, {1, 3}, {2, 4}};
    KDTree<int, 2> tree(a, 5);

    // Insert new points into the KDTree
    array<int, 2> tmp = {5, 4};
    tree.insert(tmp);
    tmp = {7, 2};
    tree.insert(tmp);

    // Search for specific points in the KDTree
#if DEBUG_KD_TREE
printf("%s\n", tree.toString().c_str());
    printf("Searching for point (2, 4): ");
    printf((tree.search(array<int, 2> {2, 4}) ? "Found\n" : "Not found\n"));

    printf("Searching for point (6, 3): ");
    printf((tree.search(array<int, 2> {6, 3}) ? "Found\n" : "Not found\n"));

    printf("Searching for point (4, 7): ");
    printf((tree.search(array<int, 2> {4, 7}) ? "Found\n" : "Not found\n"));
#endif

    output.push_back(tree.search(array<int, 2> {2, 4}));
    output.push_back(tree.search(array<int, 2> {6, 3}));
    output.push_back(tree.search(array<int, 2> {4, 7}));

    tree.remove(array<int, 2>{4, 7});

#if DEBUG_KD_TREE
    printf("Searching for point (4, 7): ");
    printf((tree.search(array<int, 2> {4, 7}) ? "Found\n" : "Not found\n"));
#endif

    output.push_back(tree.search(array<int, 2> {4, 7}));

    tree.insert(array<int, 2>{4, 7});

#if DEBUG_KD_TREE
    printf("Searching for point (4, 7): ");
    printf((tree.search(array<int, 2> {4, 7}) ? "Found\n" : "Not found\n"));
#endif

    output.push_back(tree.search(array<int, 2> {4, 7}));
}

void ProvaBloomFilter(){
    output.clear();
    //Initialize the Bloom Filter
    BloomFilter<string, 5, 20, 2> bloomFilter;
    vector<string> words = {"Hello", "World!", "This is a", "Bloom Filter", "Example"};

#if DEBUG_BLOOM_FILTER
    printf("The best bitmap size is %lf.\n", bloomFilter.getBestM(bloomFilter.falsePositive()));
    printf("The best number of hash functions is %lf.\n", bloomFilter.getBestK());

    printf("False positive probability:\n\t- with all data: %lf %%\n\t- with one element: %lf %%\n", bloomFilter.falsePositive()*100, bloomFilter.falsePositive(1)*100);
    bloomFilter.insert(words[0]);
    printf("%s\n", bloomFilter.toString().c_str());
    printf("Contains \"%s\"? %s\n", words[0].c_str(), bloomFilter.contains(words[0])? "yes": "no");
    printf("Contains \"%s\"? %s\n", words[1].c_str(), bloomFilter.contains(words[1])? "yes": "no");
    output.push_back(bloomFilter.contains(words[0]));
    output.push_back(bloomFilter.contains(words[1]));
    bloomFilter.insert(words[1]);
    bloomFilter.insert(words[2]);
    bloomFilter.insert(words[3]);
    bloomFilter.insert(words[4]);
    printf("%s\n", bloomFilter.toString().c_str());
    printf("Contains \"%s\"? %s\n", words[1].c_str(), bloomFilter.contains(words[1])? "yes": "no");
    printf("Contains \"%s\"? %s\n", "Bacon", bloomFilter.contains("Bacon")? "yes": "no");
#else
    bloomFilter.insert(words[0]);
    output.push_back(bloomFilter.contains(words[0]));
    output.push_back(bloomFilter.contains(words[1]));
    bloomFilter.insert(words[1]);
    bloomFilter.insert(words[2]);
    bloomFilter.insert(words[3]);
    bloomFilter.insert(words[4]);
#endif

    output.push_back(bloomFilter.contains(words[1]));
    output.push_back(bloomFilter.contains("bacon"));
}

vector<size_t> stringCode(const string &s){
    vector<size_t> results(2);
    size_t total = 0;
    for(char c : s) total += c;
    results[0] = total % 20;
    results[1] = (s[0] * s[1] * s[2]) % 20;
    return results;
}

void ProvaCustomBloomFilter(){
    output.clear();
    //Initialize the Custom Bloom Filter
    BloomFilter<string, 5, 20, 2, stringCode> bloomFilter;
    vector<string> words = {"Hello", "World!", "This is a", "Bloom Filter", "Example"};

#if DEBUG_CUSTOM_BLOOM_FILTER
    printf("The best bitmap size is %lf.\n", bloomFilter.getBestM(bloomFilter.falsePositive()));
    printf("The best number of hash functions is %lf.\n", bloomFilter.getBestK());

    printf("False positive probability:\n\t- with all data: %lf %%\n\t- with one element: %lf %%\n", bloomFilter.falsePositive()*100, bloomFilter.falsePositive(1)*100);
    bloomFilter.insert(words[0]);
    printf("Contains \"%s\"? %s\n", words[0].c_str(), bloomFilter.contains(words[0])? "yes": "no");
    printf("Contains \"%s\"? %s\n", words[1].c_str(), bloomFilter.contains(words[1])? "yes": "no");
    output.push_back(bloomFilter.contains(words[0]));
    output.push_back(bloomFilter.contains(words[1]));
    bloomFilter.insert(words[1]);
    bloomFilter.insert(words[2]);
    bloomFilter.insert(words[3]);
    bloomFilter.insert(words[4]);
    printf("Contains \"%s\"? %s\n", words[1].c_str(), bloomFilter.contains(words[1])? "yes": "no");
    printf("Contains \"%s\"? %s\n", "Bacon", bloomFilter.contains("Bacon")? "yes": "no");
#else
    bloomFilter.insert(words[0]);
    output.push_back(bloomFilter.contains(words[0]));
    output.push_back(bloomFilter.contains(words[1]));
    bloomFilter.insert(words[1]);
    bloomFilter.insert(words[2]);
    bloomFilter.insert(words[3]);
    bloomFilter.insert(words[4]);
#endif

    output.push_back(bloomFilter.contains(words[1]));
    output.push_back(bloomFilter.contains("bacon"));
}

void ProvaAVLTree(){
    output.clear();
    AVLTree avlTree = AVLTree<int>();
#if DEBUG_AVL_TREE
    printf("Contains %d? %s", 0, avlTree.search(0) ? "Yes\n" : "No\n");
    output.push_back(avlTree.search(0));
    avlTree.insert(1);
    printf("Structure: %s\n", avlTree.toString().c_str());
    avlTree.insert(2);
    printf("Structure: %s\n", avlTree.toString().c_str());
    avlTree.insert(3);
    printf("Structure: %s\n", avlTree.toString().c_str());
    avlTree.insert(4);
    printf("Structure: %s\n", avlTree.toString().c_str());
    printf("Contains %d? %s", 2, avlTree.search(2) ? "Yes\n" : "No\n");
    printf("Contains %d? %s", 4, avlTree.search(4) ? "Yes\n" : "No\n");
    printf("Contains %d? %s", 5, avlTree.search(5) ? "Yes\n" : "No\n");
    output.push_back(avlTree.search(2));
    output.push_back(avlTree.search(4));
    output.push_back(avlTree.search(5));
#else
    output.push_back(avlTree.search(0));
    avlTree.insert(1);
    avlTree.insert(2);
    avlTree.insert(3);
    avlTree.insert(4);
    output.push_back(avlTree.search(2));
    output.push_back(avlTree.search(4));
    output.push_back(avlTree.search(5));
#endif
}

void ProvaSkipList(){
    output.clear();
    SkipList lst = SkipList<int>(2, 0.5);

    lst.insertElement(21);
    lst.insertElement(9);
    lst.insertElement(7);
    lst.insertElement(6);
    lst.insertElement(3);
    lst.insertElement(19);
    lst.insertElement(26);
    lst.insertElement(17);
    lst.insertElement(12);
    lst.insertElement(25);
#if DEBUG_SKIP_LIST
    printf("%s", lst.toString().c_str());
    output = lst.getData()[0];
#else
    output = lst.getData()[0];
#endif
}

void ProvaTreap(){
    Treap<int> treap;

    treap.insert(50);
    treap.insert(30);
    treap.insert(20);
    treap.insert(40);
    treap.insert(70);
    treap.insert(60);
    treap.insert(80);

#if DEBUG_TREAP
    printf("Inorder traversal of the given tree \n");
    treap.inorder();

    printf("\nDelete 20\n");
    treap.deleteNode(20);
    printf("Inorder traversal of the modified tree\n");
    treap.inorder();

    printf("\nDelete 30\n");
    treap.deleteNode(30);
    cout << "Inorder traversal of the modified tree \n";
    treap.inorder();

    cout << "\nDelete 50\n";
    treap.deleteNode(50);
    cout << "Inorder traversal of the modified tree \n";
    treap.inorder();
#else
    treap.deleteNode(20);
    treap.deleteNode(30);
    treap.deleteNode(50);
#endif

    output = treap.getVector();
}

void ProvaSplayTree() {
    output.clear();
    SplayTree splayTree(100);
    splayTree.insert(50);
    splayTree.insert(200);
    splayTree.insert(40);
    splayTree.insert(30);
    splayTree.insert(20);
    splayTree.insert(70);

    output.push_back(splayTree.search(20));

#if DEBUG_SPLAY_TREE
    printf("Found 20: %s\n", output.at(0) ? "Yes" : "No");
    printf("%s\n", splayTree.toString().c_str());
#endif
}

void ProvaKaryHeap() {
    int capacity = 100;
    int k = 3;

    KaryHeap<int> karyHeap(k, capacity);

    karyHeap.insert(4);
    karyHeap.insert(5);
    karyHeap.insert(6);
    karyHeap.insert(7);
    karyHeap.insert(8);
    karyHeap.insert(9);
    karyHeap.insert(10);

#if DEBUG_KARY_HEAP
    printf("\nHeap is: %s\n", karyHeap.toString().c_str());

    karyHeap.insert(3);

    printf("\nHeap after inserting: %s\n", karyHeap.toString().c_str());

    printf("\nExtracted max is %d\n", karyHeap.extractMax());

    printf("\nHeap after extract max: %s\n", karyHeap.toString().c_str());
#else
    karyHeap.insert(3);
    karyHeap.extractMax();
#endif

    output =  karyHeap.getHeapAsVector();
}

void ProvaVanEmdeBoasTree() {
    output.clear();
    VanEmdeBoasTree vanEmdeBoasTree = VanEmdeBoasTree(8);

    // Inserting Keys
    vanEmdeBoasTree.insert(1);
    vanEmdeBoasTree.insert(0);
    vanEmdeBoasTree.insert(2);
    vanEmdeBoasTree.insert(4);

#if DEBUG_BOAS_TREE
    // Before deletion
    cout << "Conte el valor 2: " << vanEmdeBoasTree.contains(2) << endl;
    cout << "Predecessor de 4: " << vanEmdeBoasTree.predecessor(4) << endl;
    cout << "Successor de 1: " << vanEmdeBoasTree.successor(1) << endl;
    output.push_back(vanEmdeBoasTree.contains(2));
    output.push_back(vanEmdeBoasTree.predecessor(4));
    output.push_back(vanEmdeBoasTree.successor(1));

    cout << "Eliminam el valor 2 de l'estructura\n";
#else
    output.push_back(vanEmdeBoasTree.contains(2));
    output.push_back(vanEmdeBoasTree.predecessor(4));
    output.push_back(vanEmdeBoasTree.successor(1));
#endif

    // Delete only if the key is present
    if (vanEmdeBoasTree.contains(2))
        vanEmdeBoasTree.remove(2);

#if DEBUG_BOAS_TREE
    // After deletion
    cout << "Conte el valor 2: " << vanEmdeBoasTree.contains(2) << endl;
    cout << "Predecessor de 4: " << vanEmdeBoasTree.predecessor(4) << endl;
    cout << "Successor de 1: " << vanEmdeBoasTree.successor(1) << endl;
    printf("%s\n", vanEmdeBoasTree.toString().c_str());
    output.push_back(vanEmdeBoasTree.contains(2));
    output.push_back(vanEmdeBoasTree.predecessor(4));
    output.push_back(vanEmdeBoasTree.successor(1));
#else
    output.push_back(vanEmdeBoasTree.contains(2));
    output.push_back(vanEmdeBoasTree.predecessor(4));
    output.push_back(vanEmdeBoasTree.successor(1));
    cout << "Predecessor de 0: " << vanEmdeBoasTree.predecessor(0) << endl;
    cout << "Sucessor de 4: " << vanEmdeBoasTree.successor(4) << endl;
#endif
}

void ProvaRadixTree() {
    output.clear();
    RadixTree radixTree;

#if DEBUG_RADIX_TREE
    radixTree.insert("home");
    printf("home added\n");
    printf("Final tree:\n%s", radixTree.toString().c_str());
    radixTree.insert("casualitat");
    printf("casualitat added\n");
    printf("Final tree:\n%s", radixTree.toString().c_str());
    radixTree.insert("casualitat");
    printf("casualitat added\n");
    printf("Final tree:\n%s", radixTree.toString().c_str());
    radixTree.insert("casada");
    printf("casada added\n");
    printf("Final tree:\n%s", radixTree.toString().c_str());
    radixTree.insert("casualitats");
    printf("casualitats added\n");
    printf("Final tree:\n%s", radixTree.toString().c_str());
    radixTree.insert("caminar");
    printf("caminar added\n");
    printf("Final tree:\n%s", radixTree.toString().c_str());
    output.push_back(radixTree.search("caminar"));
    output.push_back(radixTree.search("cXminar"));
    output.push_back(radixTree.search("cas"));
    cout << "Contains word \"caminar\": " << (output[0] ? "Yes" : "No") << '\n';
    cout << "Contains word \"cXminar\": " << (output[1] ? "Yes" : "No") << '\n';
    cout << "Contains word \"cas\": " << (output[2] ? "Yes" : "No") << '\n';
#else
    radixTree.insert("home");
    radixTree.insert("casualitat");
    radixTree.insert("casualitat");
    radixTree.insert("casada");
    radixTree.insert("casualitats");
    radixTree.insert("caminar");
    output.push_back(radixTree.search("caminar"));
    output.push_back(radixTree.search("cXminar"));
    output.push_back(radixTree.search("cas"));
#endif
    radixTree.clear();
}
