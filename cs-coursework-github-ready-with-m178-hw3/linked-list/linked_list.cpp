#include <iostream>
#include <conio.h>  
using namespace std;

class Node {
public:
    char data;
    Node* next;
    Node(char c, Node* n) : data(c), next(n) {}
};

int main()
{
    Node* s = nullptr;
    Node* tail = nullptr;
    char c;


    while (true) {
        c = _getch();
        cout << c;

        Node* newnode = new Node(c, nullptr);

        if (s == nullptr) {
            s = newnode;
            tail = newnode;
        }
        else {
            tail->next = newnode;
            tail = newnode;
        }

        if (c == 'q') break;
    }

    cout << endl;


    int count = 0;
    for (Node* p = s; p != nullptr; p = p->next) count++;


    Node* slow = s;
    Node* fast = (s != nullptr) ? s->next : nullptr;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    cout << "number of nodes = " << count << endl;
    if (slow != nullptr)
        cout << "Middle node is: " << slow->data << endl;


    cout << "Linked list: ";
    for (Node* p = s; p != nullptr; p = p->next) cout << p->data;
    cout << endl;


    Node* p = s;
    while (p != nullptr) {
        Node* nxt = p->next;
        delete p;
        p = nxt;
    }

    return 0;
}