#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

class LoviaInterpreter {
private:
    unordered_map<string, int> variables;

public:
    void execute(const vector<string>& lines) {
        for (size_t i = 0; i < lines.size(); i++) {
            string line = lines[i];
            stringstream ss(line);
            string command;
            ss >> command;

            if (command == "say") {
                string output;
                getline(ss, output);
                output = output.substr(1); // Remove leading space
                cout << output << endl;
            }
            else if (command == "set") {
                string varName, to;
                int value;
                ss >> varName >> to >> value;
                if (to == "to") {
                    variables[varName] = value;
                }
            }
            else if (command == "repeat") {
                int times;
                string temp;
                ss >> times >> temp;
                if (temp == "times:") {
                    vector<string> loopBody;
                    i++; // Move to next line
                    while (i < lines.size() && lines[i] != ":end") {
                        loopBody.push_back(lines[i]);
                        i++;
                    }
                    for (int j = 0; j < times; j++) {
                        execute(loopBody);
                    }
                }
            }
        }
    }
};

int main() {
    vector<string> code = {
        "set x to 10",
        "say Hello, Lovia!",
        "repeat 3 times:",
        "    say Loop iteration!",
        ":end",
        "say Goodbye!"
    };
    
    LoviaInterpreter interpreter;
    interpreter.execute(code);
    
    return 0;
}
