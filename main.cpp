#include <iostream>
#include <vector>
#include <cmath>

float note;
int coeff;
bool isCreatingTable;
bool isNotePossible;
std::string answer;
std::vector<float> notesList{};
float noteSum;
float averageNote;
float minimumNote;
float maximumNote;

int convertedNote;
std::vector<float> evenNotesList{};
std::vector<float> oddNotesList{};
std::vector<float> decimalNotesList{};

// Calculate the weighted average of the notes
void table_calculate() {
    // Add all notes to the sum of notes for the calculation
    for (int i = 0; i <= notesList.size()-1; i++) {
        noteSum += notesList[i];
    }
    // Calculate the average
    averageNote = noteSum / notesList.size();
    // Calculate the minimum, take the first value and compare it with the rest
    minimumNote = notesList[0];
    for (int i = 1; i <= notesList.size()-1; i++) {
        if (notesList[i] < minimumNote) {
            minimumNote = notesList[i];
        }
    }
    // Do the same for the maximum
    maximumNote = notesList[0];
    for (int i = 1; i <= notesList.size()-1; i++) {
        if (notesList[i] > maximumNote) {
            maximumNote = notesList[i];
        }
    }
    // Identify even or odd numbers, using modulo remainder 0 to find them
    for (int i = 0; i <= notesList.size()-1; i++) {
        // Check if a number is decimal or not, to decide whether to apply modulo
        if (!(std::fmod(notesList[i],1.0) != 0.0)) {
            convertedNote = static_cast<int>(notesList[i]);
            if (convertedNote%2==0) {
                // If it's even, add it to its list
                evenNotesList.push_back(notesList[i]);
            }
            else {
                // If it's odd, add it to its list
                oddNotesList.push_back(notesList[i]);
            }
        }
        else {
            // If it's decimal, add it to its list
            decimalNotesList.push_back(notesList[i]);
        }

    }

    std::cout << "Sum of notes: "           << noteSum              << std::endl;
    std::cout << "Number of notes: "        << notesList.size()     << std::endl;
    std::cout << "Average of notes: "       << averageNote          << std::endl;
    std::cout << "Minimum note: "           << minimumNote          << std::endl;
    std::cout << "Maximum note: "           << maximumNote          << std::endl;
    std::cout << "Even notes: ";
    for (int i = 0; i <= evenNotesList.size()-1; i++) {
        if (std::empty(evenNotesList)) {
            // Don't loop if there are no values, avoid crash
            break;
        }
        std::cout << evenNotesList[i] << ", ";
    }
    std::cout << std::endl;
    // Add values from the respective arrays to display them to the user
    std::cout << "Odd notes: ";
    for (int i = 0; i <= oddNotesList.size()-1; i++) {
        if (std::empty(oddNotesList)) {
            // Don't loop if there are no values, avoid crash
            break;
        }
        std::cout << oddNotesList[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Decimal notes: ";
    for (int i = 0; i <= decimalNotesList.size()-1; i++) {
        if (std::empty(decimalNotesList)) {
            // Don't loop if there are no values, avoid crash
            break;
        }
        std::cout << decimalNotesList[i] << ", ";
    }
    std::cout << std::endl;
}

// Function for creating values
void table_creation() {
    isCreatingTable = true;
    // Normal infinite loop, adds values to the array as long as desired
    while (isCreatingTable) {
        isNotePossible = true;

        // Ask for notes input, y to finish the program
        std::cout << "Enter (y) when you are done entering notes: ";
        std::cout << "Enter a note between 0 and 20: ";
        std::cin >> answer;

        // Check if the input is different from y to continue the loop
        if (answer != "y") {
            // Try to convert the input string to a float for the note
            try {
                note = std::stof(answer);
            }
            // Handle error if the user enters neither y nor a note
            catch (const std::invalid_argument& e) {
                std::cout << "Invalid value, please try again" << std::endl;
                // Do not finish the loop to request new input
                isNotePossible = false;
            }
            // Handle notes that exceed the requested range
            if (!(note>=0 && note<=20)) {
                std::cout << "Impossible note, please try again" << std::endl;
                // Do not finish the loop to request new input
                isNotePossible = false;
            }
        }
        else {
            table_calculate();
            break;
        }
        // If the note is correct, ask for the coefficient
        if (isNotePossible) {
            std::cout << "Enter a coefficient (integers only): ";
            std::cin >> coeff;
        }
        // If the coefficient is impossible, do not finish the loop to restart
        if (coeff<0) {
            std::cout << "The coefficient is not possible, please try again" << std::endl;
            isNotePossible = false;
        }
        // If both the note and its coefficient are okay, add them here
        if (isNotePossible) {
            // Loop to add the number of notes based on the coefficient
            for (int i = 0; i < coeff; i++) {
                notesList.push_back(note);
            }
            // Display the list to inform the user of the entered notes
            std::cout << "Here is the current list (per coefficient 1): ";
            for (int i = 0; i <= notesList.size()-1; i++) {
                std::cout << notesList[i] << ", ";
            }
            std::cout << std::endl;
        }
        std::cin.clear();
    }
}

int main() {
    notesList.clear();
    evenNotesList.clear();
    oddNotesList.clear();
    std::cout << "Average Calculator: " << std::endl;
    table_creation();
    std::cout << "Do you want to continue? (y/other)";
    std::cin.clear();
    std::cin >> answer;
    if (answer=="y") {
        main();
    }
    else {
        return 0;
    }
    return 0;
}
