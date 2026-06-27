#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<string> undoStack;
stack<string> redoStack;
string text = "";

void typeText(string str)
{
    undoStack.push(text);
    text += str;

    while (!redoStack.empty())
        redoStack.pop();
}

void undo()
{
    if (undoStack.empty())
    {
        cout << "Nothing to Undo!\n";
        return;
    }

    redoStack.push(text);
    text = undoStack.top();
    undoStack.pop();
}

void redo()
{
    if (redoStack.empty())
    {
        cout << "Nothing to Redo!\n";
        return;
    }

    undoStack.push(text);
    text = redoStack.top();
    redoStack.pop();
}

void display()
{
    cout << "\nCurrent Text: " << text << endl;
}

int main()
{
    int choice;
    string input;

    do
    {
        cout << "\n===== Undo-Redo Text Editor =====";
        cout << "\n1. Type Text";
        cout << "\n2. Undo";
        cout << "\n3. Redo";
        cout << "\n4. Display";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter text: ";
            getline(cin, input);
            typeText(input);
            break;

        case 2:
            undo();
            break;

        case 3:
            redo();
            break;

        case 4:
            display();
            break;

        case 5:
            cout << "Exiting...";
            break;

        default:
            cout << "Invalid Choice!";
        }

    } while (choice != 5);

    return 0;
}
