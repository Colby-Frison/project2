#include <iostream>
#include <string>

using namespace std;

class Chip {
private:
    char chipType;     // Type of the chip (A: Addition, S: Subtraction, etc.)
    string id;         // Unique identifier for the chip
    Chip* input1;      // Pointer to the first input chip
    Chip* input2;      // Pointer to the second input chip (can be NULL)
    Chip* output;  // Output connection (chip this one feeds into)
    double inputValue; // For input chips
    double outputValue; // Result after computation
    bool isComputed;   // To avoid redundant computations

public:
    // Constructor
    Chip(char type, const string& id) : chipType(type), id(id), input1(nullptr), input2(nullptr), inputValue(0), outputValue(0), isComputed(false) {}

    // Set the first input chip
    void setInput1(Chip* inputChip) {
        input1 = inputChip;
    }

    // Set the second input chip (can be NULL)
    void setInput2(Chip* inputChip) {
        input2 = inputChip;
    }

    void setOutput(Chip* chip) { output = chip; }

    // Set the input value for input chips
    void setInputValue(double value) {
        inputValue = value;
        isComputed = false; // Reset computed status when input value changes
    }

    // Getters for input1 and input2
    Chip* getInput1() const {
        return input1;
    }

    Chip* getInput2() const {
        return input2;
    }

    Chip* getOutput() const { return output; }

    char getType() const{
        return chipType;
    }

    // Getter for id
    string getId() const {
        return id;
    }



    double getOutputValue() const;

    // Perform the computation based on the chip type
    //some comments in here are for debugging and others are actuall comments its lowkey a mess 
    //  I apologize
    void compute() {
        if (isComputed) return;  // Prevent re-computation

        switch (chipType) {
            case 'A': // Addition
                input1->compute();
                input2->compute();
                outputValue = input1->getOutputValue() + input2->getOutputValue();
                //cout << id << " computed: " << outputValue << endl;
                break;
            case 'S': // Subtraction
                input1->compute();
                input2->compute();
                outputValue = input1->getOutputValue() - input2->getOutputValue();
                //cout << id << " computed: " << outputValue << endl;
                break;
            case 'M': // Multiplication
                input1->compute();
                input2->compute();
                outputValue = input1->getOutputValue() * input2->getOutputValue();
                //cout << id << " computed: " << outputValue << endl;
                break;
            case 'D': // Division
                input1->compute();
                input2->compute();
                if (input2->getOutputValue() != 0) {
                    outputValue = input1->getOutputValue() / input2->getOutputValue();
                } else {
                    cout << "Error: Division by zero!" << endl;
                    outputValue = 0;
                }
                //cout << id << " computed: " << outputValue << endl;
                break;
            case 'N': // Negation
                input1->compute();
                outputValue = -input1->getOutputValue();
                //cout << id << " computed: " << outputValue << endl;
                break;
            case 'I': // Input chip
                outputValue = inputValue;  // Input chip simply holds its input value
                //cout << id << " input value: " << outputValue << endl;
                break;
            case 'O': // Output chip
                if (input1 != nullptr) {
                    input1->compute();  // Ensure input chip is computed before outputting
                    outputValue = input1->getOutputValue(); // Just pass the value for display
                }
                //cout << "I am output chip " << id << ", and the value I received is " << outputValue << endl;
                break;
            default:
                cout << "Unknown chip type!" << endl;
        }
        isComputed = true;  // Mark as computed to avoid re-computation
    }

    // Display connections
    // Display connections
    // Display method to show chip connections
    void display() const {
        // Handle input chips (type 'I')
        if (chipType == 'I') {
            cout << id << ", Output = ";
            if (output) {
                cout << output->getId() << endl;  // Safely access the output chip ID
            } else {
                cout << "None" << endl;
            }
        }
        // Handle output chips (type 'O')
        else if (chipType == 'O') {
            cout << id << ", Input 1 = ";
            if (input1) {
                cout << input1->getId() << endl;  // Safely access the input chip ID
            } else {
                cout << "None" << endl;
            }
        }
        // Handle logic chips (e.g., AND, OR, NOT)
        else {
            cout << id << ", Input 1 = ";
            if (input1) {
                cout << input1->getId() << ", ";
            } else {
                cout << "None, ";
            }
            cout << "Input 2 = ";
            if (input2) {
                cout << input2->getId() << ", ";
            } else {
                cout << "None, ";
            }
            cout << "Output = ";
            if (output) {
                cout << output->getId() << endl;
            } else {
                cout << "None" << endl;
            }
        }
    }
};

double Chip::getOutputValue() const{
    return outputValue;
}

Chip* findChipById(Chip* chips[], int numChips, const string& chipId) {
    for (int i = 0; i < numChips; ++i) {
        if (chips[i]->getId() == chipId) {
            return chips[i];
        }
    }
    return nullptr; // Return nullptr if no chip with the given ID is found
}

int main() {
    int numChips, numCommands;

    // Read the number of chips
    cin >> numChips;

    // Create an array of pointers to Chip objects
    Chip** allChips = new Chip*[numChips];

    // Create each chip and store it in the array
    for (int i = 0; i < numChips; ++i) {
        string chipId;
        cin >> chipId;

        char chipType = chipId[0];  // First character determines the type
        //cout << "Creating chip " << chipId << endl;  // Debug print
        allChips[i] = new Chip(chipType, chipId);
    }

    // Read the number of commands
    cin >> numCommands;

    // Execute commands to connect chips or set values
    for (int i = 0; i < numCommands; ++i) {
        char commandType;
        string sourceId, destId;
        double value;

        cin >> commandType; // Only read once per command

        if (commandType == 'A') {
            cin >> sourceId >> destId;
            Chip* sourceChip = findChipById(allChips, numChips, sourceId);
            Chip* destChip = findChipById(allChips, numChips, destId);

            if (sourceChip == nullptr) {
                cout << "Error: Could not find the source chip with ID: " << sourceId << endl;
            } else if (destChip == nullptr) {
                cout << "Error: Could not find the destination chip with ID: " << destId << endl;
            } else {
                // Assign the source chip to the destination's input
                if (destChip->getInput1() == nullptr) {
                    destChip->setInput1(sourceChip);
                } else {
                    destChip->setInput2(sourceChip);
                }
            }
        } else if (commandType == 'I') {
            cin >> sourceId >> value;
            Chip* sourceChip = findChipById(allChips, numChips, sourceId);
            if (sourceChip == nullptr) {
                cout << "Error: Could not find the source chip with ID: " << sourceId << endl;
            } else {
                // Set the input value for the input chip
                sourceChip->setInputValue(value);
                //cout << "Input chip " << sourceId << " received value: " << value << endl;
            }
        } else if (commandType == 'O') {
            cin >> destId;
            Chip* destChip = findChipById(allChips, numChips, destId);

            if (destChip == nullptr) {
                cout << "Error: Could not find the destination chip with ID: " << destId << endl;
            } else {
                // Compute and the output
                cout << "Computation Starts" << endl;
                destChip->compute();
                cout << "The output value from this circuit is " << destChip->getOutputValue() << endl;
            }
        }
    }

    // Display connections
    cout << "***** Showing the connections that were established *****" << endl;
    for (int i = 0; i < numChips; ++i) {
        allChips[i]->display();
    }

    // Cleanup allocated memory
    for (int i = 0; i < numChips; ++i) {
                delete allChips[i];
    }
    delete[] allChips;

    return 0;
}
