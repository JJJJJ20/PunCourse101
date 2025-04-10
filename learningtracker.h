// ✅ ProgressNode for Linked List
struct ProgressNode {
    Progress* progress;
    ProgressNode* next;
    ProgressNode(Progress* p) : progress(p), next(nullptr) {}
};

// ✅ LearningTracker class
class LearningTracker {
private:
    ProgressNode* head;

public:
    LearningTracker() : head(nullptr) {}

    ~LearningTracker() {
        ProgressNode* current = head;
        while (current) {
            ProgressNode* temp = current;
            current = current->next;
            delete temp->progress;
            delete temp;
        }
    }

    // ✅ Add new progress to the list
    void add_progress(Progress* p) {
        ProgressNode* newNode = new ProgressNode(p);
        if (!head) head = newNode;
        else {
            ProgressNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // ✅ Display all progress in the list
    void display_progress() const {
        if (!head) {
            cout << "\n📭 No progress recorded.\n";
            return;
        }

        cout << "\n📘 Your Course Progress:\n";
        ProgressNode* current = head;
        while (current) {
            current->progress->print();
            current = current->next;
        }
    }
};