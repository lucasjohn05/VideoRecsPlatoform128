#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
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

void heapifyUp(vector<Node>& heap, int child) {
    int parent = (child - 1) / 2;
    if (child > 0 && heap.at(child).getViews() > heap.at(parent).getViews()) {
        swap(heap.at(child), heap.at(parent));
        heapifyUp(heap, parent);
    }
}

void insertNode(vector<Node>& heap, Node insertedVideo) {
    heap.push_back(insertedVideo);
    heapifyUp(heap, heap.size() - 1);
}

bool searchAndIncrement(vector<Node>& heap, const string& searchTerm, bool byTitle) {
    for (int i = 0; i < heap.size(); ++i) {
        bool match = byTitle ? (heap.at(i).getTitle() == searchTerm) : (heap.at(i).getID() == searchTerm);
        if (match) {
            heap.at(i).incrementViews();
            heapifyUp(heap, i);
            return true;
        }
    }
    return false;  // Video not found
}

void readCSV(const string& filename, vector<Node>& heap) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Skip the header row (if it exists)
    getline(file, line);

    // Read each line in the CSV file
    while (getline(file, line)) {
        stringstream ss(line);
        string videoID, videoTitle;
        int viewCount;

        getline(ss, videoID, ',');
        getline(ss, videoTitle, ',');
        ss >> viewCount;

        Node newNode(viewCount, videoID, videoTitle);
        insertNode(heap, newNode);
    }

    file.close();
}

int main() {
    vector<Node> heap;

    string filename = "Tik Kroks Data Set.csv";
    readCSV(filename, heap);

    while (true) {
        cout << "Popular videos:" << endl;
        for (int i = 0; i < 5 && i < heap.size(); i++) {
            cout << heap.at(i).getTitle() << " (" << heap.at(i).getViews() << " views)" << endl;
        }

        string searchTerm;
        int option;

        cout << "\nSelect an option:\n";
        cout << "1. Search by Video Title\n";
        cout << "2. Search by Video ID\n";
        cout << "3. Exit\n";
        cout << "Enter option:\n";
        cin >> option;
        cin.ignore();

        if (option == 3) {
            break;
        } else if ((option != 1) && (option != 2)) {
            cout << "Invalid option.\n";
        } else {
            cout << "Enter search term:\n";
            getline(cin, searchTerm);

            bool byTitle = (option == 1);

            bool found = searchAndIncrement(heap, searchTerm, byTitle);

            if (found) {
                cout << "Video watched!\n\n";
            } else {
                cout << "Video not found.\n\n";
            }
        }
    }

    return 0;
}