#include <iostream>
#include <string>

using namespace std;

/*****************************************************************************************************
 * * * * * * * * * * * * * * Colby Frison ~ Data structures CS-2413 * * * * * * * * * * * * * * * * * 
 * 
 * * * * * * * * * * * * * * * * * Part 2 starts at line 357 * * * * * * * * * * * * * * * * * * * * *
 * 
 * * * * * * * * * * * * * * * * * Part 3 starts at line 651 * * * * * * * * * * * * * * * * * * * * *
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
 * 
*****************************************************************************************************/

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

    //other getters
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
double Chip::getOutputValue() const{
    return outputValue;
}


/***********************************************************************
 * The compute class is one of the important methods in the program, 
 * it has the responsiblity of actually doing the math of the chips.
 * This is done through a simple switch case that changes what 
 * operation is done based on the chip type.
 * 
 * the comments throughout are a little all over the place. Some of 
 * the comments are for description, others were for debugging I never
 * deleted, I still kept those just to show how debuging worked through
 * my process.
***********************************************************************/
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
            // make sure the operation isnt trying to divide by 0 for obvious reasons
            if (input2->getOutputValue() != 0) {
                outputValue = input1->getOutputValue() / input2->getOutputValue();
            } else { // if its 0 throw an error
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
            outputValue = inputValue;  // Input chip just holds its input value
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
            cout << "Unknown chip type!" << endl; // throws error for unknown chip type
    }

    isComputed = true;  // Mark as computed to avoid re-computation
}


/********************************************************************************
 * Display method is not super complicated, it just prints out the message in 
 * accoradnce to the project description. The input and output chips have their 
 * own special cases, but the other chips have the same outputs. So tahts what 
 * the main three statements are for. Then within the statemnets it checks to 
 * make sure there is acutally a chip to read from, as if there is not, it would 
 * cause a seggmentation error. It then just calls the getter for the output.
**********************************************************************************/
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


/********************************************************************************
 * This is a helper method that just finds agiven chip based on the id in the
 * full 'chips' array. This is just to make the main method a little simpler.
*********************************************************************************/
Chip* findChipById(Chip* chips[], int numChips, const string& chipId) {
    for (int i = 0; i < numChips; ++i) {
        if (chips[i]->getId() == chipId) {
            return chips[i];
        }
    }
    return nullptr; // Return nullptr if no chip with the given ID is found
}  


/*****************************************************************************************
 * This is the main method, it just has the responsibilty of reading inputs, then calling 
 * compute and dispaly methods to get the proper output. Mainly done by changing the way 
 * the file line is read based on what chip is being used. Then at the end when displaying 
 * it runs checks to see what chip is being displayed so it can print in the right order.
 * The first tow don't warrant this solution, but since the output chip on the third one 
 * this had to be implemeneted.
 ****************************************************************************************/
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


/*******************************************************************************************
 * * * * * * * * * * * * * * * * * * Part2 * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * I started by creating a general outline of the full program, so I inserted the Chip 
 * class and main method provided in the instructions. I then declared all the helper 
 * methods in the Chip class besides the display and compute, I then described the 
 * function of the program as a whole, along with what each portion should do in comments.
 * I then used chatgpt to help implement the display, computer, and main methods.
 * 
 * First I asked for an outline on how to do it in accordance to the instructions, i then 
 * made all implimentations I could. At this point I dont think I had any errors, but the
 * code definetly did not function as intended. 
 * 
 * I then provided an exmaple input and output, and asked it to tell me how I can change 
 * my code to get the desired output, after some changes and many errors. The program was 
 * pretty much done at this point and most questions were related to syntax or small errors.
 * 
 * * * * * * * * * * * * * * * Here is the chat logs * * * * * * * * * * * * * * * * * * * *
 * Link: https://chatgpt.com/share/66f35c8b-e304-800d-9cd9-ecde00889168 
 * 
transcription of logs

My question:

**instructions for project**
I dont wanna paste them here as its a lot of text

create an outline for the program

---------------------------------------------------------------------------

ChatGPT said:
ChatGPT
Here's a structured outline for your C++ project implementing the Chip class and the associated functionalities described in the project instructions. This outline breaks down the tasks into logical components to guide your implementation.

Outline for Chip Circuit Simulation Program
1. Class Definition: Chip
Private Members:

char chipType: Stores the type of the chip (e.g., 'A', 'S', 'M', 'N', 'D').
string id: Unique identifier for the chip.
Chip* input1: Pointer to the first input chip.
Chip* input2: Pointer to the second input chip (can be NULL).
Chip* output: Pointer to the output chip (can be NULL, especially for output chips).
double inputValue: Holds the value for input chips.
Public Methods:

Constructor:
Chip(char type, const string& id): Initializes a chip with a specific type and ID.
Setters:
void setInput1(Chip* inputChip): Sets the first input chip.
void setInput2(Chip* inputChip): Sets the second input chip (can be NULL).
void setOutput(Chip* outputChip): Sets the output chip (can be NULL).
Computation:
void compute(): Performs the arithmetic operation based on the chip type.
Display:
void display() const: Displays the chip's information.
Getters:
string getId() const: Returns the chip ID.
Additional Methods (if necessary):

Method to set input value for input chips.
2. Main Program Structure
Include Necessary Headers:

cpp
Copy code
#include <iostream>
#include <string>
using namespace std;
Main Function:

cpp
Copy code
int main() {
    int numChips;
    cin >> numChips;

    // Step 1: Create an array of Chip pointers
    Chip** allChips = new Chip*[numChips];

    // Step 2: Read chip IDs and create Chip objects
    for (int i = 0; i < numChips; i++) {
        string id;
        cin >> id;  // Read the chip ID
        // Determine chip type based on the first character
        char type = id[0];
        allChips[i] = new Chip(type, id);  // Create Chip object and store it in the array
    }

    // Step 3: Read and process commands to connect chips
    int numCommands;
    cin >> numCommands;

    for (int i = 0; i < numCommands; i++) {
        string command;
        cin >> command;  // Read the command

        if (command[0] == 'A') {
            // Connection command: A inputChip outputChip
            string inputId1, inputId2;
            cin >> inputId1 >> inputId2;

            // Find input chips in allChips array and connect them
            Chip* inputChip1 = nullptr;
            Chip* inputChip2 = nullptr;

            // Loop to find chips by ID
            for (int j = 0; j < numChips; j++) {
                if (allChips[j]->getId() == inputId1) {
                    inputChip1 = allChips[j];
                }
                if (allChips[j]->getId() == inputId2) {
                    inputChip2 = allChips[j];
                }
            }

            // Set connections
            allChips[j]->setInput1(inputChip1);
            if (inputChip2) {
                allChips[j]->setInput2(inputChip2);
            }

        } else if (command[0] == 'O') {
            // Output command: O outputChip
            string outputId;
            cin >> outputId;

            // Find the output chip and call compute
            for (int j = 0; j < numChips; j++) {
                if (allChips[j]->getId() == outputId) {
                    allChips[j]->compute();  // Perform computation
                }
            }
        }
    }

    // Step 4: Show the connections established
    cout << "***** Showing the connections that were established *****" << endl;
    for (int i = 0; i < numChips; i++) {
        allChips[i]->display();  // Display information about each chip
    }

    // Clean up dynamic memory
    for (int i = 0; i < numChips; i++) {
        delete allChips[i];
    }
    delete[] allChips;

    return 0;
}
3. Input Processing
Handle redirected input, which provides the configuration and values for the chips.
Read the initial chip configuration and connections.
4. Computation Logic
Implement the compute() method based on chip type:
Addition (A): Adds two input values.
Subtraction (S): Subtracts the second input from the first.
Multiplication (M): Multiplies two input values.
Negation (N): Negates the input value.
Division (D): Divides the first input by the second.
Output (O): Displays the final computed value.
5. Testing
Use various input scenarios to ensure that all chips operate correctly and the connections are established as expected.
Test edge cases such as missing inputs or invalid commands.
Conclusion
This outline provides a clear path for implementing the Chip class and managing the connections and computations of the chips in your circuit simulation program. Each section can be expanded into detailed code implementations as you develop your project.

---------------------------------------------------------------------------------------------------

my question:
can you explain how I should go about writing the dispaly and compute methods

------------------------------------------------------------------------------------------------------

ChatGPT said:
Certainly! Here’s how to approach writing the display and compute methods for the Chip class in your C++ project.

1. Display Method
The display method is responsible for showing the current state of a chip, including its type, ID, inputs, and outputs. It should give a clear overview of how the chip fits into the circuit.

Implementation Steps:
Determine Chip Type: Check the type of the chip (addition, subtraction, etc.) to format the display message accordingly.
Display Chip Information: Include the ID and the values of the input chips if applicable. For the output chip, display the value received.
Example Implementation:
cpp
Copy code
void Chip::display() const {
    // Display chip ID and type
    cout << "Chip ID: " << id << ", Type: " << chipType;

    // Display input connections
    if (chipType == 'I') {
        // Input chip: Display the input value
        cout << ", Input Value = " << inputValue;
    } else if (input1) {
        // For other chips, display input chip IDs
        cout << ", Input 1 = " << (input1 ? input1->getId() : "None");
        if (input2) {
            cout << ", Input 2 = " << input2->getId();
        } else {
            cout << ", Input 2 = None";
        }
    }

    // For output chip, display the connected output chip ID
    if (chipType == 'O') {
        cout << ", Output from = " << (output ? output->getId() : "None");
    }

    cout << endl; // New line for better readability
}
2. Compute Method
The compute method performs the arithmetic operation specific to the chip type and updates the output accordingly. This method will be critical for the functionality of your circuit.

Implementation Steps:
Input Handling: Retrieve the values from the input chips.
Perform the Operation: Based on the chip type, carry out the arithmetic operation.
Set Output: If the chip produces an output, set the output value accordingly.
Example Implementation:
cpp
Copy code
void Chip::compute() {
    switch (chipType) {
        case 'A': // Addition
            if (input1 && input2) {
                outputValue = input1->inputValue + input2->inputValue;
            }
            break;

        case 'S': // Subtraction
            if (input1 && input2) {
                outputValue = input1->inputValue - input2->inputValue;
            }
            break;

        case 'M': // Multiplication
            if (input1 && input2) {
                outputValue = input1->inputValue * input2->inputValue;
            }
            break;

        case 'D': // Division
            if (input1 && input2 && input2->inputValue != 0) {
                outputValue = input1->inputValue / input2->inputValue;
            } else {
                cout << "Error: Division by zero" << endl;
                return;
            }
            break;

        case 'N': // Negation
            if (input1) {
                outputValue = -input1->inputValue;
            }
            break;

        case 'O': // Output chip (this would normally not perform a compute)
            cout << "I am output chip number " << id 
                 << ", and the value I received is " << inputValue << endl;
            return;

        default:
            cout << "Error: Unknown chip type" << endl;
            return;
    }

    // If the chip produces an output, you can set it in an output chip (if applicable)
    if (output) {
        output->inputValue = outputValue; // Pass the computed value to the output chip
    }
}
Summary
Display Method: Clearly shows the chip's ID, type, inputs, and any relevant output information.
Compute Method: Implements the logic for each chip type, handling arithmetic operations and passing output values to connected chips.
Additional Considerations
Error Handling: Make sure to include error checks, such as division by zero or null pointers for input chips.
Integration: Ensure the compute() method is called in the correct sequence in the main program so that the outputs are calculated in the right order. This might involve cascading the computations through the chain of chips until you reach the output chip.
This structure will help ensure that your program runs correctly and produces the expected results!

-------------------------------------------------------------------------------------------------------

There are probably a few other but I think I must have been on guest mode because I cannot find the logs

I remember specifially one issue I had was not being able to figure out how to display in the proper order for test3

and the solution it gave was just 3 if statements one for I one for O and one for neither so it was in the right order.

 * * * * * * * * * * * * * * * * * * * * Part 2 - Done* * * * * * * * * * * * * * * * * * * * * * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * Part 3 * * * * * * * * * * * * * * * * * * * * * * * 
 * 
 * The debugging and testing process of the development of this program was pretty simple. The most basic 
 * forms of test was just the inputs provided by the porject description page, I was able to use these tests 
 * to make sure my program was running as intened. To make sure the outputs were the exact same I used a
 * program that checked to make sure they were equal. beyond just test I had various debug lines throughout 
 * the code that helped ensure the write things were happening. For instance in the compute class I had print
 * statements that displayed what was being computed at each step, along with that in the main method I had 
 * various different debug lines, one of them displayed what chips were created, the other dispaleyed when 
 * an input was recieved.
 * 
 * One noteable issue I encountered was with input3, in this input the output chip was listed first instead 
 * of last, this caused an issue in my ouput where the output chip was listed as the first operation, which 
 * is obviuosly wrong. To fix this issue I used a set of if statements in the portion of the main method were 
 * I displaeyd the outputs. These if statements simply displayed inputs first then operational chips then the 
 * output chip. This ensured the proper output order.
 * 
 * Another issue I had that I felt very stupid about was when I was first making the display method. For some 
 * reason I couldn't figure out there was a seggmentation error when trying to call the getId method to print 
 * the id. I eventually figured out I forgot to set the output chip when declaring chips in the main method. It
 * was an easy fix but it took an embarassingly long time to figure out.
 * 
 * In terms of other tests I didnt really have any, I just made sure it worked with the three provided. But its
 * not like I only made sure it worked with these three. For instance, I had multipule catches in place to ensure 
 * nothing blew up in the program. For instance everytime something may be null i always check to make sure it 
 * isnt before calling for it. Or in the division section, you obviously cant divide by 0, so i make sure the 
 * input val != 0. I couldnt think of any other fail cases so I think thats all i implemented, I gaurentee 
 * I left something out, but thats all i can remember. 
 * 
 * Lastly for optimization I didnt really put too much thought into it until now. For the compute method I have
 * a series of switches cases as there are 7 differnet possibilities and im pretty sure swithc is faster than 7 
 * if statements. For the other methods that implement a lot of swithc cases I don't think it was super applicable
 * as it is usually a far less intense process. There are probably numerous other optimizations I can make throughout 
 * the program, but due to the realtive simplicity of the task it isnt worth the time to scrutinize it. I did make 
 * sure to properly delete all the chips and the arr at the end of the program if were counting that as opitmiaztion.
 * 
 * So in short, I used the provided inputs and matching outputs to ensure program was working. Along with various
 * debugg statements throughout to trouble shoot before the program was fully runnable. Some issues I had were 
 * with: getting id for display, ordering chip outputs properly, and matching output perfectly. Some optimization
 * was used in the form of switch cases, but this wasnt taken to the extreme due to the relative lightness of
 * the program.
 * 
 * * * * * * * * * * * * * * * * * * * * * Part 3 - Done * * * * * * * * * * * * * * * * * * * * *
 * 
 */