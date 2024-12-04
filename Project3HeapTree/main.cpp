#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node {
private:
    int viewCount;
    string videoID;
    string videoTitle;

public:
    Node(int views, string ID, string title) {
        viewCount = views;
        videoID = ID;
        videoTitle = title;
    }

    int getViews() {
        return viewCount;
    }

    string getID() {
        return videoID;
    }

    string getTitle() {
        return videoTitle;
    }

    void incrementViews() {
        viewCount++;
    }
};

void percolateUp(vector<Node>& heap, int child) {
    int parent = (child - 1) / 2;
    if (child > 0 && heap.at(child).getViews() > heap.at(parent).getViews()) {
        swap(heap.at(child), heap.at(parent));
        percolateUp(heap, parent);
    }
}

void percolateDown(vector<Node>& heap, int heapSize, int parent) {
    int left = (2 * parent) + 1;
    int right = (2 * parent) + 2;
    // The parent index is initially equal to 0
    int maxIndex = parent;

    if (right < heapSize && heap.at(right).getViews() > heap.at(maxIndex).getViews())
        maxIndex = right;
    if (left < heapSize && heap.at(left).getViews() > heap.at(maxIndex).getViews())
        maxIndex = left;

    if (maxIndex != parent) {
        swap(heap[maxIndex], heap[parent]);
        percolateDown(heap, heapSize, maxIndex);
    }
}

void insertNode(vector<Node>& heap, Node insertedVideo) {
    heap.push_back(insertedVideo);
    percolateUp(heap, heap.size() - 1);
}

int main() {
    Node video1 = Node(10, "2jgk", "MEOW");
    Node video2 = Node(5, "3jgo", "WOOF");
    Node video3 = Node(15, "3jlo", "MOO");
    Node video4 = Node(20, "3flo", "RAWR");
    Node video5 = Node(3, "3flo", "GRRR");
    Node video6 = Node(100, "3fro", "HEHEHEHAW");
    Node video7 = Node(0, "3flk", ":(");
    Node video8 = Node(12, "3fre", "what");
    Node video9 = Node(12, "4jnd", "huh");
    Node video10 = Node(100, "odg4", "t");
    vector<Node> heap;
    insertNode(heap, video1);
    insertNode(heap, video2);
    insertNode(heap, video3);
    insertNode(heap, video4);
    insertNode(heap, video5);
    insertNode(heap, video6);
    insertNode(heap, video7);
    insertNode(heap, video8);
    insertNode(heap, video9);
    insertNode(heap, video10);
    for (int i = 0; i < heap.size(); i++){
        cout << heap.at(i).getTitle() << " (" << heap.at(i).getViews() << " views)" << endl;
    }



    return 0;
}
