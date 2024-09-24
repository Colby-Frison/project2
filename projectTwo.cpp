#include <iostream>
#include <string>

using namespace std;

/****************************************************************************************************
 * * * * * * * * * * * * * * Colby Frison ~ Data structures CS-2413 * * * * * * * * * * * * * * * * * 
 * 
 * This program is a little all over the place, but it still works and is relativley organized so who
 * cares. The program takes in an input that sates the amount of chips, then the actaul chips, then 
 * the number of operations, followed by what operations it is doing. These chips consist of an input 
 * and output along with the actually math ones so: addition, subtraction, mulitplication, division, 
 * and lastly negation. All of the math chips take in two inputs besides the negation one, which ony 
 * takes one input. Also the output chips is a little weird as it doesnt actually output anyhting,
 * it just kind of displays what it recieves as its one input. 
 * 
 * I'll explain what the main methods due throughout the program as well. 
****************************************************************************************************/

//chip class
class Chip {
private:

    //chip identifiers
    char chipType;     
    string id;  
        
    //chips
    Chip* input1;      
    Chip* input2;      
    Chip* output;     

    //important vars for computation 
    double inputValue; 
    double outputValue;
    bool isComputed;   

public:

    //constructor
    Chip(char type, const string& id);

    //setters
    void setInput1(Chip* inputChip);
    void setInput2(Chip* inputChip);//can be null
    void setOutput(Chip* inputChip);
    void setInputValue(double value);

    //chip getters
    Chip* getInput1() const;
    Chip* getInput2() const;
    Chip* getOutput() const;

    //other getter
    char getType() const;
    string getId() const;
    double getOutputValue() const;

    //important methods
    void compute();
    void display() const;

};

//constructor assign type and id, assign else to default
Chip::Chip(char type, const string& id) : chipType(type), id(id), input1(nullptr), input2(nullptr), inputValue(0), outputValue(0), isComputed(false) {}

//setters
void Chip::setInput1(Chip* inputChip) {
    input1 = inputChip;
}
void Chip::setInput2(Chip* inputChip) {
    input2 = inputChip;
}
void Chip::setOutput(Chip* chip) { 
    output = chip; 
}
void Chip::setInputValue(double value) {
    inputValue = value;
    isComputed = false; // Reset computed status when input value changes
}

//chip getters
Chip* Chip::getInput1() const {
    return input1;
}
Chip* Chip::getInput2() const {
    return input2;
}
Chip* Chip::getOutput() const { 
    return output; 
}

//other getters
char Chip::getType() const{
    return chipType;
}
string Chip::getId() const {
    return id;
}


/***************************
 * The compute class is one of the important methods in the program, 
 * it has the responsiblity of actually doing the math of the chips.
 * This is done through a simple switch case that changes what 
 * operation is done based on the chip type.
 * 
 * the comments throughout are a little all over the place. Some of 
 * the comments are for description, others were for debugging I never
 * deleted, I still kept those just to show how debuging worked through
 * my process.
****************************/
void Chip::compute() {
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

/***************************
 * 
****************************/
void Chip::display() const {
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
            sourceChip->setOutput(destChip);

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
            //destChip->setInput1(nullptr);

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
    cout << "***** Showing the connections that were established" << endl;
    
    // First, display input chips
    for (int i = 0; i < numChips; ++i) {
        if (allChips[i]->getType() == 'I') {
            allChips[i]->display();
        }
    }

    // Second, display logic chips (A, S, M, N, D)
    for (int i = 0; i < numChips; ++i) {
        if (allChips[i]->getType() != 'I' && allChips[i]->getType() != 'O') {
            allChips[i]->display();
        }
    }

    // Finally, display output chips
    for (int i = 0; i < numChips; ++i) {
        if (allChips[i]->getType() == 'O') {
            allChips[i]->display();
        }
    }

    // Cleanup allocated memory
    for (int i = 0; i < numChips; ++i) {
                delete allChips[i];
    }
    delete[] allChips;

    return 0;
}
