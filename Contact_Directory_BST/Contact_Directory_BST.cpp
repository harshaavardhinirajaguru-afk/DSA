#include <iostream>
#include <string>
using namespace std;

struct Contact {
    string name;
    string phone;
    Contact *left, *right;
};

Contact* createNode(string name, string phone) {
    Contact* temp = new Contact;
    temp->name = name;
    temp->phone = phone;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert Contact
Contact* insert(Contact* root, string name, string phone) {
    if (root == NULL)
        return createNode(name, phone);

    if (name < root->name)
        root->left = insert(root->left, name, phone);
    else if (name > root->name)
        root->right = insert(root->right, name, phone);
    else
        cout << "Contact already exists.\n";

    return root;
}

// Search Contact
Contact* search(Contact* root, string name) {
    if (root == NULL || root->name == name)
        return root;

    if (name < root->name)
        return search(root->left, name);

    return search(root->right, name);
}

// Find Minimum Node
Contact* findMin(Contact* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Delete Contact
Contact* deleteContact(Contact* root, string name) {
    if (root == NULL)
        return root;

    if (name < root->name)
        root->left = deleteContact(root->left, name);

    else if (name > root->name)
        root->right = deleteContact(root->right, name);

    else {
        if (root->left == NULL) {
            Contact* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Contact* temp = root->left;
            delete root;
            return temp;
        }

        Contact* temp = findMin(root->right);
        root->name = temp->name;
        root->phone = temp->phone;
        root->right = deleteContact(root->right, temp->name);
    }

    return root;
}

// Display Contacts Alphabetically
void inorder(Contact* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "Name  : " << root->name << endl;
        cout << "Phone : " << root->phone << endl;
        cout << "------------------------\n";
        inorder(root->right);
    }
}

int main() {
    Contact* root = NULL;
    int choice;
    string name, phone;

    do {
        cout << "\n===== CONTACT DIRECTORY =====\n";
        cout << "1. Insert Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Display Contacts\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Phone: ";
            cin >> phone;
            root = insert(root, name, phone);
            break;

        case 2: {
            cout << "Enter Name to Search: ";
            cin >> name;
            Contact* result = search(root, name);

            if (result != NULL) {
                cout << "\nContact Found\n";
                cout << "Name  : " << result->name << endl;
                cout << "Phone : " << result->phone << endl;
            }
            else
                cout << "Contact Not Found.\n";
            break;
        }

        case 3:
            cout << "Enter Name to Delete: ";
            cin >> name;
            root = deleteContact(root, name);
            cout << "Delete operation completed.\n";
            break;

        case 4:
            cout << "\n===== CONTACT LIST =====\n";
            inorder(root);
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
