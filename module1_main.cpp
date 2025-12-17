    #include <iostream>
    #include <string>
    #include <cctype>
    #include <algorithm>
    #include <stdexcept>
    #include <cmath>
    #include <fstream>
    #include <sstream>
    #include <vector>
    using namespace std;

    int charToValue(char c){
        if(isdigit(c))return c -'0';
        if(isalpha(c)) return tolower(c) - 'a' + 10;
        return -1;
    }

    char valueToChar(int value){
        if(value<10) return '0'+value;
        return 'A'+(value-10);
    }
    //checking validity
    //1.base
    bool valid_base(int base){
        if(base>= 2 && base<=20) return true;
        else return false;  
    }
    //2.number validity for base
    bool valid_num_base(string number, int base){
        bool dot_seen = false;
        for(char c: number){
            if(c == '-') continue;
            if(c == '.'){
                if(dot_seen) return false; // more than one dot
                dot_seen = true;
                continue;
            }
            int digit = charToValue(c);
            if(digit < 0 || digit >= base) return false;
        }
        return true;
    }


    //converting number in base1 to decimal in base10 assuming everything is valid
    float convert_b1_decimal(string number, int base1){
        bool is_neg= false;
        if(number[0]=='-'){
            is_neg=true;
            number=number.substr(1);
        }
        
        
        float decimal=0;
        int i = number.find('.') == string::npos ? number.length() - 1 : number.find('.') - 1;
        for(char c : number){
            if(c == '.'){
                i=-1;
                continue;
            }
            decimal+= charToValue(c)*pow(base1, i);
            i--;
        }
        return is_neg ? -decimal : decimal;
    }

    //converting decimal to base2, use append or pushback
    string convert_dec_b2(float decimal, int base2){
        bool is_neg=false;
        if(decimal < 0){
            is_neg=true;
            decimal= - decimal;
        }
        /*string str= to_string(decimal);int pos=str.find('.');
        string int_part=str.substr(0,pos), frac_part='0'+str.substr(pos);
        int integer= stoi(int_part);
        float fraction= stof(frac_part);*/
        int integer = static_cast<int>(floor(decimal)); // integer part
        float fraction = decimal - integer;             // fractional part
        
        //for integer part
        string result_int;
        if(integer ==0) result_int="0";
        
        while(integer>0){
            int rem= integer % base2;
            result_int.push_back(valueToChar(rem));
            integer/=base2;
        }
        reverse(result_int.begin(), result_int.end());//algo to reverse 
        
        
        //for fractional part
        string result_frac;
        int precision=10;//setting max precision

        while(precision--){
            fraction*=base2;
            int digit= static_cast<int>(fraction);
            result_frac.push_back(valueToChar(digit));
            fraction-=digit;
        }

        string result;
        result= result_frac.empty() ? result_int : (result_int+"."+result_frac);
        return is_neg? ("-" + result) : result;
    }

    string convert_base(string num, int base1, int base2){
        if(!valid_base(base1)) return "ERROR! Supported base range is 2-20";
        if(!valid_base(base2)) return "ERROR! Supported base range is 2-20";
        if (!valid_num_base(num, base1)) return "ERROR! Invalid digits for the given base.";

        float decimal= convert_b1_decimal(num, base1);
        return convert_dec_b2(decimal,base2);
    }


bool is_integer_string(const string& s) {
    return s.find('.') == string::npos;
}

bool fractional_match(float a, float b) {
    return fabs(a - b) <= 1e-6;
}

void process_csv() {
    ifstream infile("base_conversion_input.csv");
    ofstream outfile("base_conversion_output.csv");

    if (!infile.is_open()) {
        cerr << "Error: Could not open input CSV file.\n";
        return;
    }
    if (!outfile.is_open()) {
        cerr << "Error: Could not create output CSV file.\n";
        return;
    }

    outfile << "number,base_1,base_2,output1,output2,match,error\n";

    string line;
    getline(infile, line); // skip header

    while (getline(infile, line)) {
        stringstream ss(line);
        string num_str, b1_str, b2_str;
        getline(ss, num_str, ',');
        getline(ss, b1_str, ',');
        getline(ss, b2_str, ',');

        string number = num_str;
        int base1 = stoi(b1_str);
        int base2 = stoi(b2_str);

        string output1, output2, error_msg;
        bool match = false;

        output1 = convert_base(number, base1, base2);
        if (output1.rfind("ERROR!", 0) == 0) {
            error_msg = output1;
            outfile << number << "," << base1 << "," << base2 << ",,,False," << error_msg << "\n";
            continue;
        }

        output2 = convert_base(output1, base2, base1);
        if (output2.rfind("ERROR!", 0) == 0) {
            error_msg = output2;
            outfile << number << "," << base1 << "," << base2 << "," << output1 << ",,False," << error_msg << "\n";
            continue;
        }

        if (is_integer_string(number) && is_integer_string(output2)) {
            match = (number == output2);
        } else {
            float orig = convert_b1_decimal(number, base1);
            float back = convert_b1_decimal(output2, base1);
            match = fractional_match(orig, back);
        }

        outfile << number << "," << base1 << "," << base2 << ","
                << output1 << "," << output2 << ","
                << (match ? "True" : "False") << ","
                << error_msg << "\n";
    }

    infile.close();
    outfile.close();

    cout << "Processing complete. Output saved to base_conversion_output.csv\n";
}

void process_custom() {
    string number;
    int base1, base2;

    cout << "Enter number: ";
    cin >> number;
    cout << "Enter base to convert from (2-20): ";
    cin >> base1;
    cout << "Enter base to convert to (2-20): ";
    cin >> base2;

    string output1 = convert_base(number, base1, base2);
    if (output1.rfind("ERROR!", 0) == 0) {
        cout << output1 << "\n";
        return;
    }


    cout << "conversion (" << base1 << " -> " << base2 << "): " << output1 << "\n";
    /*bool match;
    if (is_integer_string(number) && is_integer_string(output2)) {
        match = (number == output2);
    } else {
        float orig = convert_b1_decimal(number, base1);
        float back = convert_b1_decimal(output2, base1);
        match = fractional_match(orig, back);
    }

    cout << "First conversion (" << base1 << " -> " << base2 << "): " << output1 << "\n";
    cout << "Roundtrip back (" << base2 << " -> " << base1 << "): " << output2 << "\n";
    cout << "Match: " << (match ? "True" : "False") << "\n";*/
}

//test_suite
struct TestCase {
    string number;
    int base1;
    int base2;
};

void test_suite() {
    vector<TestCase> tests = {
        {"83.5", 10, 2},
        {"1111", 2, 10},
        {"7A", 16, 8},
        {"2A", 10, 2},
        {"9220.4", 10, 15},
        {"123.25", 10, 21}
    };

    cout << "\n===== Running Test Suite =====\n";

    for (size_t i = 0; i < tests.size(); ++i) {
        string result = convert_base(tests[i].number, tests[i].base1, tests[i].base2);

        cout << "Test " << (i + 1) << ": "
             << tests[i].number << " (Base " << tests[i].base1
             << " -> Base " << tests[i].base2 << ") -> ";
        cout << result << "\n";
    }

    cout << "===== Test Suite Complete =====\n";
}

int main() {
    cout << "Choose mode:\n";
    cout << "1. Process from CSV file (base_conversion_input.csv)\n";
    cout << "2. Enter custom input\n";
    cout << "3. Run test suite\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        process_csv();
    } else if (choice == 2) {
        process_custom();
    } else if (choice == 3) {
        test_suite();
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}