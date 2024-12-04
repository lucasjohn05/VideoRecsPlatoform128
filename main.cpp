#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;



class Node {

public:
    string videoID;
    string title;
    int views;
    Node* left;
    Node* right;


    Node(string videoID, string title, int views) {
        this->videoID=videoID;
        this->title=title;
        this->views=views;
        this->left= nullptr;
        this->right= nullptr;
    }
};

// Splay Tree Class
class SplayTree {
public:
    Node* root;

    Node* rightrotate(Node* x) {
        Node* y=x-> left;
        x->left=y->right;
        y->right=x;
        return y;
    }


    Node* leftrotate(Node* x) {
        Node* y= x->right;
        x->right =y->left;
        y->left=x;
        return y;

    }


    Node* splay(Node* root, string videoID) {
        //only if the searched video is already in the root
        if (!root) {
            return root;
        }


        if (root->videoID== videoID) {
            return root;
        }

        if (videoID < root->videoID) {
            if (!root->left) {
                return root;
            }
            // zig zig (left left)
            // these zig-zags are based on the id comparing too the root
            if (videoID < root->left->videoID) {
                root->left->left=splay(root->left->left, videoID);
                root=rightrotate(root);
            }


            // zigzag (left right)
            else if (videoID > root->left->videoID) {
                root->left->right =splay(root->left->right, videoID);
                if (root->left->right) {
                    root->left=leftrotate(root->left);
                }
            }
            if (root->left) {
                return rightrotate(root);
            } else {
                return root;
            }
        }



        // Video ID lies in the right subtree
        if (!root->right) {
            return root;
        }

        // zag zig (right left)
        if (videoID < root->right->videoID) {
            root->right->left =splay(root->right->left, videoID);
            if (root->right->left) {
                root->right =rightrotate(root->right);
            }
        }
        // zag zag (right right)
        else if (videoID >root->right->videoID) {
            root->right->right =splay(root->right->right, videoID);
            root=leftrotate(root);
        }
        if (root->right) {
            root=leftrotate(root);
        }
        return root;
    }




    //constructor
    SplayTree() {
        root=nullptr;
    }


    void insert(string videoID, string title, int views) {
        //need new as essentially adding a new node
        if (!root) {
            root =new Node(videoID, title, views);
            return;
        }
        root =splay(root, videoID);
        if (root->videoID==videoID) {
            return;
        }// Video already exists

        Node* newNode=new Node(videoID,title, views);
        if (videoID<root->videoID) {
            newNode->right=root;
            newNode->left=root->left;
            root->left=nullptr;
        } else {
            newNode->left =root;
            newNode->right=root->right;
            root->right=nullptr;
        }
        root=newNode;
    }

    void search(string videoID) {
    //searches by video idea

        root=splay(root, videoID);
        if (root!=nullptr) {
            if (root->videoID==videoID) {
                cout << "Great choice! Video Found: " << root->title << endl << endl;
            }
        }
        else {
            cout<< "Improper ID."<< endl;
        }

    }


    void preorder(Node* node, int& count, int limit) {
        if (!node || count >= limit) {
            return;
        }
        cout << node->videoID << ": " << node->title << " (" << node->views << " views)" << endl;
        count++;
        preorder(node->left, count, limit);
        preorder(node->right, count, limit);
    }



    void printPreorder() {
        int count =0;
        int limit =5;
        preorder(root, count, limit);
    }

    Node* searchtitle(Node* node, string& title) {
        if (!node) {
            return nullptr;
        }
        if (node->title==title) {
            return node;
        }
        Node* desiredtitle =searchtitle(node->left, title);
        if (desiredtitle) {
            return desiredtitle;
        }
        return searchtitle(node->right, title);
    }

    void splayaftertitle(string& title) {
        Node* node =searchtitle(root, title);
        if (node) {
            root =splay(root, node->videoID);
            cout << "Great choice! Video Found: " << root->title << endl<<endl;
        } else {
            cout << "Improper title." << endl<<endl;
        }
    }
};

// Read Dataset and Load into the Tree
void readcsv(string filename, SplayTree& tree) {
    ifstream file(filename);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        string videoID, title, viewsinstring;
        stringstream ss(line);
        // reads the videoID
        getline(ss, videoID, ',');


        // for all titles but if quotes are there to avoid commas-> handles issue of skipping commas when in title
        if (ss.peek()=='"') {
            ss.get();
            getline(ss, title,'"'); //stops at next quotations
            ss.get(); // this skips the comma after
        } else {
            getline (ss, title, ',' ); // when no quotes this will just read
        }

        // Read views
        getline (ss, viewsinstring, ',');

            //making views into integer
            int views=stoi(viewsinstring);
        //immediately puts in the csv into the splay tree. thus last element of data set will be root
            tree.insert(videoID,title,views);

    }

    file.close();
}

int main() {
    SplayTree tree;

    // getting kaggle database file-> this is where to change with smaller excelsheet
    string datasetname = "Tik Kroks Data Set.csv";
    readcsv(datasetname, tree);


    int choice;
    string videoID;
    while (true) {
        cout<<"Videos Recommended For You Based on What You Watch: "<<endl;
        tree.printPreorder();
        cout<<endl;
        cout<< endl<<"Menu:"<<endl;
        cout<< "1. Search for a video by id"<<endl;
        cout<< "2. Search for a video by title"<<endl;
        cout<< "3. Exit"<<endl;
        cout<< "Please select an option: "<<endl;
        cin>> choice;

        if (choice==1) {
            cout << "Enter Video ID you would like to search: ";
            cin >> videoID;
            tree.search(videoID);
        }
        else if (choice==2) {
            cout << "Enter the title of the video: ";
            cin.ignore();
            string title;
            getline(cin, title);
            tree.splayaftertitle(title);
        }
        else if (choice==3) {
            cout << "Thank you for using the Tik Kroks Reccomender!"<< endl;
            return 0;
        }
        else {
            cout<<"Out of range choice. Options are between 1 and 3."<< endl;
        }
    }

    return 0;
}

