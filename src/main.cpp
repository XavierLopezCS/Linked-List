// 136 - Lab5
using namespace std;
#include <iostream>

template <typename T>
class Node {
private:
    T data;
    Node* next;
public:
    Node(T val) : data(val), next(nullptr) {}
    T getData() const { return data; }
    void setData(T val) { data = val; }
    Node* getNext() const { return next; }
    void setNext(Node* node) { next = node; }
};

//=========================================

template <typename T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList() : head(nullptr) {};

    void insertAtStart(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->setNext(head);
        head = newNode;
    }

    //=========================================

    void insertAtEnd(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }

            current->setNext(newNode);
        }
    }

    //=========================================

    void print() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->getData() << " ";
            current = current->getNext();
        }
        cout << endl;
    }

    //=========================================

    T getFirst() const {
        if (head != nullptr) {
            return head->getData();
        }
        throw logic_error("List is empty");
    }

    //=========================================

    void deleteByValue(T val) {
        if (head != nullptr) {
            if (head->getData() == val) {
                Node<T>* temp = head;
                head = head->getNext();
                delete temp;
            }
            else {
                Node<T>* current = head;
                while (current->getNext() != nullptr &&
                    current->getNext()->getData() != val) {
                    current = current->getNext();
                }
                if (current->getNext() != nullptr) {
                    Node<T>* temp = current->getNext();
                    current->setNext(current->getNext()->getNext());
                    delete temp;
                }
            }
        }
    }


    //=========================================

    bool search(T val) {
        bool found = false;
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->getData() == val) {
                found = true;
                break;
            }
            current = current->getNext();
        }
        return found;
    }

    //=========================================

    int getSize() const {
        int count = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            count++;
            current = current->getNext();
        }
        return count;
    }

    void splitList(LinkedList<T>& firstHalf, LinkedList<T>& secondHalf) {
        int size = getSize();
        int mid = size / 2;

        Node<T>* current = head;
        for (int i = 0; i < mid; i++) {
            firstHalf.insertAtEnd(current->getData());
            current = current->getNext();
        }
        while (current != nullptr) {
            secondHalf.insertAtEnd(current->getData());
            current = current->getNext();
        }
    }

    LinkedList<T> mergeSorted(const LinkedList<T>& other) const {
        LinkedList<T> result;
        Node<T>* a = head;
        Node<T>* b = other.head;

        while (a != nullptr && b != nullptr) {
            if (a->getData() < b->getData()) {
                result.insertAtEnd(a->getData());
                a = a->getNext();
            }
            else {
                result.insertAtEnd(b->getData());
                b = b->getNext();
            }
        }
        while (a != nullptr) {
            result.insertAtEnd(a->getData());
            a = a->getNext();
        }

        while (b != nullptr) {
            result.insertAtEnd(b->getData());
            b = b->getNext();
        }

        return result;
    }

    template <typename T>
    friend LinkedList<T> mergeSortedFriend(const LinkedList<T>& l1, const LinkedList<T>& l2);
};

template <typename T>
LinkedList<T> mergeSortedFriend(const LinkedList<T>& l1, const LinkedList<T>& l2) {
	LinkedList<T> result;
	Node<T>* a = l1.head;
	Node<T>* b = l2.head;

	while (a != nullptr && b != nullptr) {
		if (a->getData() < b->getData()) {
			result.insertAtEnd(a->getData());
			a = a->getNext();
		}
		else {
			result.insertAtEnd(b->getData());
			b = b->getNext();
		}
	}

	while (a != nullptr) {
		result.insertAtEnd(a->getData());
		a = a->getNext();
	}

	while (b != nullptr) {
		result.insertAtEnd(b->getData());
		b = b->getNext();
	}

	return result;
}



int main(){
    LinkedList<int> l1, l2;

	l1.insertAtEnd(1);
	l1.insertAtEnd(3);
	l1.insertAtEnd(5);

	l2.insertAtEnd(2);
	l2.insertAtEnd(4);
	l2.insertAtEnd(6);

    cout << "List 1: ";
	l1.print();
    cout << "List 2: ";
	l2.print();

    //Member
    LinkedList<int> merged = l1.mergeSorted(l2);
    cout << "Merged (member): ";
    merged.print();

    //Friend
    LinkedList<int> mergedFriend = mergeSortedFriend(l1, l2);
    cout << "Merged (friend): ";
    mergedFriend.print();

    // Size
	cout << "Size of merged list: " << merged.getSize() << endl;

    // Split
    LinkedList<int> firstHalf, secondHalf;
	merged.splitList(firstHalf, secondHalf);
	cout << "First Half: ";
    firstHalf.print();
    cout << "Second Half: ";
	secondHalf.print();

    return 0;

};
