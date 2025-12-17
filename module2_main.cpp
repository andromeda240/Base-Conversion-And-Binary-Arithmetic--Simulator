#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


bool isValidBinary(string s, int width) {
    if (s.length() != width) return false;
    for (char c : s) {
        if (c != '0' && c != '1') return false;
    }
    return true;
}

bool isValidRepresentation(string rep) {
    return (rep == "unsigned" || rep == "signed_magnitude" ||
            rep == "ones_complement" || rep == "twos_complement");
}

bool isValidOperation(string op) {
    return (op == "add" || op == "sub" || op == "mul" || op == "div");
}

string padding(string a, int len){
    if(a.length() < len) a.insert(0, len-a.length(), '0');
    return a;
}

string add(string a, string b){//takes care of padding in function itself
    string result= "";
    int carry= 0;
    //padding
    int len= max(a.length(), b.length());
    a.insert(0, len-a.length(), '0');
    b.insert(0, len-b.length(), '0');

    for(int i= len-1; i>=0; i--){
        int bit1= a[i] - '0'; //to convert the string bit into integer
        int bit2= b[i] - '0';

        int sum= bit1+bit2+carry;
        result+= (sum%2) + '0';
        carry= sum/2;

    }

    if(carry){
        result+= '1';
    }

    reverse(result.begin(), result.end());//reverse algo
    return result;
}

string ones_complement(string a){
    string result= a;
    for(char &c : result)
        c= (c == '0') ? '1' : '0';
    return result;
}

string twos_complement(string a){
    string one(a.length(), '0'); //to add 1 to ones_complement of a
    one[one.length() -1] = '1';
    return add(ones_complement(a), one);
}

string check_flow(string result, int size){
    if(result.length() > size) return "OVERFLOW";
    else return result;
}

string sub(string a, string b){
    string result="0";
    string b_2s_com= twos_complement(b);
    result= add(a, b_2s_com);

    if(result.length() > a.length()){
        result=result.substr(1);
    } //to check for overflow and discard in 2s complement case

     //to remove leading zeroes
    int pos_0= result.find_first_not_of('0');
    if(pos_0 != string::npos) return result.substr(pos_0);
    else return "0";
}

string mul(string a, string b){
    string result="0";
    int shift=0;

    for(int i=b.length()-1; i>=0;i--){
        if(b[i]=='1'){
            string temp = a+ string(shift, '0');
            result= add(result, temp);
        }
        shift++;
    }

    //to remove leading zeroes
    int pos_0= result.find_first_not_of('0');
    if(pos_0 != string::npos) return result.substr(pos_0);
    else return "0";
}

bool isGreaterOrEqual(string a, string b){
    string A= a, B= b;
    A.erase(0, A.find_first_not_of('0'));
    B.erase(0, B.find_first_not_of('0'));
    if(A.length() != B.length()) return A.length() > B.length();

    return A >= B;
    
}

pair<string, string> div(string a, string b){
    if(b == "0"){
        throw runtime_error("Division by zero");
    }
    string quotient="";
    string remainder="";

    for(int i=0; i<a.length(); i++){
        remainder+= a[i];
        remainder.erase(0, remainder.find_first_not_of('0'));
        if((remainder.empty())) remainder="0";

        if(isGreaterOrEqual(remainder, b)){
            remainder = sub(remainder, b);
            quotient+= "1";
        }
        else{
            quotient+= "0";
        }

        quotient.erase(0, quotient.find_first_not_of('0'));
        if(quotient.empty()) quotient= "0";
        if(remainder.empty()) remainder= "0";

        
    }
    return {quotient, remainder};
}


string unsigned_add(string a, string b){
    string result= add(a,b);
    int len= max(a.length(), b.length());
    if (result.length() > len){
        throw overflow_error("Overflow");
    }

    return result;
}

string unsigned_sub(string a, string b){
    string result;
    if(!isGreaterOrEqual(a, b)){
        throw underflow_error ("Underflow");
    }

    result= sub(a,b);
    return result;
}

string unsigned_mul(string a, string b){
    string result;
    result= mul(a,b);
    return result;
}

pair<string, string> unsigned_div(string a, string b){
    pair<string, string> result= div(a, b);

    return result;
}

string signed_add(string a, string b){
    string result;
    char a_sign= a[0];
    char b_sign= b[0];

    a.erase(0, 1);
    b.erase(0, 1);
    int len= max(a.length(), b.length());
    a= padding(a, len);
    b= padding(b, len);

    if(a_sign == b_sign){
        result= unsigned_add(a, b);
        result= string(1, a_sign)+ result;
    }
    else{
        if(isGreaterOrEqual(a, b)){
            result= unsigned_sub(a, b);
            result= string(1, a_sign)+ result;
        }
        else{
            result= unsigned_sub(b, a);
            result= string(1, b_sign) + result;
        }
    }
    return result;

}

string signed_sub(string a, string b){
    string result;
    if(b[0] == '0') b[0]= '1';
    else b[0]= '0';
    int len= max(a.length(), b.length());
    a= string(1, a[0])+ padding(a, len-1);
    b= string(1, b[0])+ padding(b, len-1);

    result= signed_add(a, b);
    return result;
}

string pad_to_nearest_2thpower(string a, char ch) {
    int len = a.length();

    int next_pow = pow(2, ceil(log2(len + 1)));
    string result = padding(a, next_pow);

    return result;
}

string signed_mul(string a, string b){
    int len= max(a.length(), b.length());
    string result;
    char a_sign= a[0];
    char b_sign= b[0];

    a.erase(0, 1);
    b.erase(0, 1);

    result= mul(a,b);
    result= pad_to_nearest_2thpower(result, '0');
    result.erase(0,1);

    if(a_sign == b_sign) result= string(1, '0')+ result;
    else result= string(1, '1')+ result;

    return result;
}

pair<string, string> signed_div(string a, string b) {
    int len = max(a.length(), b.length());
    char a_sign = a[0];
    char b_sign = b[0];

    // Remove sign bits for magnitude division
    string mag_a = a.substr(1);
    string mag_b = b.substr(1);

    // Unsigned division
    auto result = div(mag_a, mag_b);
    string Q = padding(result.first, len - 1);
    string R = padding(result.second, len - 1);

    // Add sign bits
    char q_sign = (a_sign != b_sign) ? '1' : '0';
    char r_sign = a_sign;

    return {string(1, q_sign) + Q, string(1, r_sign) + R};
}


string ones_comp_add(string a, string b){
    int len= max(a.length(), b.length());
    string result;
    char a_sign= a[0];
    char b_sign= b[0];

    a= a.insert(0, len-a.length(), a_sign);
    b= b.insert(0, len-b.length(), b_sign);
    string padded_1 = padding ("1", len);
    result= add(a, b); 

    if(result.length() > len){
        result.erase(0,1);
        result= add(result, padded_1);
    }

    if((a_sign == b_sign) && (a_sign != result[0])){
        throw overflow_error("Overflow");
    }
    return result;
}

string ones_comp_sub(string a, string b){
    int max_len= max(a.length(), b.length());
    string result;
    char a_sign= a[0];
    char b_sign= b[0];

    a= a.insert(0, max_len-a.length(), a_sign);
    b= b.insert(0, max_len-b.length(), b_sign);

    b= ones_complement(b);
    result= ones_comp_add(a, b);

    return result;
}

string ones_comp_mul(string a, string b){
    int len= max(a.length(), b.length());
    string result;
    char a_sign= a[0];
    char b_sign= b[0];

    a= a.insert(0, len-a.length(), a_sign);
    b= b.insert(0, len-b.length(), b_sign);

    if(a_sign == '1'){
        a= ones_complement(a);
    }
    if(b_sign == '1'){
        b= ones_complement(b);
    }

    result= mul(a, b);
    result= pad_to_nearest_2thpower(result, '0');

    if(a_sign != b_sign){
        result= ones_complement(result);
    }

    return result;
}

pair<string, string> ones_comp_div(string a, string b){
    int len = max(a.length(), b.length());
    char a_sign = a[0];
    char b_sign = b[0];

    a = a.insert(0, len - a.length(), a_sign);
    b = b.insert(0, len - b.length(), b_sign);

    string mag_a = (a_sign == '1') ? ones_complement(a) : a;
    string mag_b = (b_sign == '1') ? ones_complement(b) : b;

    pair<string, string> result = div(mag_a, mag_b);

    // Pad quotient & remainder to full length
    string Q = padding(result.first, len);
    string R = padding(result.second, len);

    if (a_sign != b_sign) {
        Q = ones_complement(Q);
    }

    // Remainder sign = sign of dividend.
    // Represent remainder as negative only if dividend was negative AND remainder is non-zero.
    if (a_sign == '1' && R != string(len, '0')) {
        R = ones_complement(R);
    }
    // If remainder is zero, keep it as positive zero ("00...0").

    return {Q, R};
}


string twos_comp_add(string a, string b){
    int len= max(a.length(), b.length());
    string result;
    char a_sign= a[0];
    char b_sign= b[0];

    a= a.insert(0, len-a.length(), a_sign);
    b= b.insert(0, len-b.length(), b_sign);
    result= add(a,b);
    if(result.length()>len) result.erase(0,1);
    
    if((a_sign == b_sign) && (result[0]!= a_sign)){
        throw overflow_error("Overflow");
    }

    return result;
}

string twos_comp_sub(string a, string b){
    int len= max(a.length(), b.length());
    string result;
    char a_sign= a[0];
    char b_sign= b[0];

    a= a.insert(0, len-a.length(), a_sign);
    b= b.insert(0, len-b.length(), b_sign);
    b= twos_complement(b);
    result= twos_comp_add(a, b);

    return result;
}

string twos_comp_mul(string a, string b){
    int len= max(a.length(), b.length());
    string result;
    char a_sign= a[0];
    char b_sign= b[0];

    a= a.insert(0, len-a.length(), a_sign);
    b= b.insert(0, len-b.length(), b_sign);

    if(a_sign == '1'){
        a= twos_complement(a);
    }
    if(b_sign == '1'){
        b= twos_complement(b);
    }

    result= mul(a, b);
    result= pad_to_nearest_2thpower(result, '0');

    if(a_sign != b_sign){
        result= twos_complement(result);
    }

    return result;
}

pair<string, string> twos_comp_div(string a, string b) {
    int len = max(a.length(), b.length());
    char a_sign = a[0];
    char b_sign = b[0];

    a = a.insert(0, len - a.length(), a_sign);
    b = b.insert(0, len - b.length(), b_sign);

    string mag_a = (a_sign == '1') ? twos_complement(a) : a;
    string mag_b = (b_sign == '1') ? twos_complement(b) : b;

    auto result = div(mag_a, mag_b);
    string Q = padding(result.first, len);
    string R = padding(result.second, len);

    if (a_sign != b_sign) {
        Q = twos_complement(Q);
    }

    if (a_sign == '1' && R != string(len, '0')) {
        R = twos_complement(R);
    }

    return {Q, R};
}


string binary_arithmetic(string num1, string num2, string rep_type, string op, int bit_width) {
    // Ensure both numbers have the correct bit width
    if (num1.length() != bit_width || num2.length() != bit_width) {
        return "Error: Bit width mismatch";
    }

    try {
        if (rep_type == "unsigned") {
            if (op == "add") return unsigned_add(num1, num2);
            else if (op == "sub") return unsigned_sub(num1, num2);
            else if (op == "mul") return unsigned_mul(num1, num2);
            else if (op == "div") {
                if (num2 == string(bit_width, '0')) return "Error: Division by zero";
                auto res = unsigned_div(num1, num2);
                return "Quotient: " + res.first + " Remainder: " + res.second;
            }
        }
        else if (rep_type == "signed_magnitude") {
            if (op == "add") return signed_add(num1, num2);
            else if (op == "sub") return signed_sub(num1, num2);
            else if (op == "mul") return signed_mul(num1, num2);
            else if (op == "div") {
                if (num2.substr(1) == string(bit_width - 1, '0')) return "Error: Division by zero";
                auto res = signed_div(num1, num2);
                return "Quotient: " + res.first + " Remainder: " + res.second;
            }
        }
        else if (rep_type == "ones_complement") {
            if (op == "add") return ones_comp_add(num1, num2);
            else if (op == "sub") return ones_comp_sub(num1, num2);
            else if (op == "mul") return ones_comp_mul(num1, num2);
            else if (op == "div") {
                if (num2.substr(1) == string(bit_width - 1, '0')) return "Error: Division by zero";
                auto res = ones_comp_div(num1, num2);
                return "Quotient: " + res.first + " Remainder: " + res.second;
            }
        }
        else if (rep_type == "twos_complement") {
            if (op == "add") return twos_comp_add(num1, num2);
            else if (op == "sub") return twos_comp_sub(num1, num2);
            else if (op == "mul") return twos_comp_mul(num1, num2);
            else if (op == "div") {
                if (num2.substr(1) == string(bit_width - 1, '0')) return "Error: Division by zero";
                auto res = twos_comp_div(num1, num2);
                return "Quotient: " + res.first + " Remainder: " + res.second;
            }
        }
        else {
            return "Error: Unknown representation type";
        }
    }
    catch (overflow_error &e) { //for throw
        return string("Error: ") + e.what();
    }
    catch (underflow_error &e) {
        return string("Error: ") + e.what();
    }
    catch (runtime_error &e) {
        return string("Error: ") + e.what();
    }

    return "Error: Unknown operation";
}

// Handles CSV input/output
void runCSVMode() {
    string inputFile = "binary_arithmetic_input.csv";
    string outputFile = "binary_arithmetic_output.csv";

    ifstream infile(inputFile);
    ofstream outfile(outputFile);

    if (!infile.is_open()) {
        cerr << "Error opening input file\n";
        return;
    }
    if (!outfile.is_open()) {
        cerr << "Error opening output file\n";
        return;
    }

    string header;
    getline(infile, header); // Skip header
    outfile << "num1,num2,representation,operation,bit_width,result,overflow,error\n";

    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string num1, num2, rep, op, width_str;
        getline(ss, num1, ',');
        getline(ss, num2, ',');
        getline(ss, rep, ',');
        getline(ss, op, ',');
        getline(ss, width_str, ',');

        int width = stoi(width_str);
        string result;
        string overflowFlag = "False";
        string errorMsg = "";

        try {
            result = binary_arithmetic(num1, num2, rep, op, width);
            if (result.find("Error: Overflow") != string::npos) {
                overflowFlag = "True";
                errorMsg = "Overflow detected";
                result = "";
            } 
            else if (result.find("Error:") != string::npos) {
                errorMsg = result.substr(6);
                result = "";
            }
        } catch (overflow_error &e) {
            overflowFlag = "True";
            errorMsg = "Overflow detected";
            result = "";
        } catch (underflow_error &e) {
            errorMsg = "Underflow detected";
            result = "";
        } catch (runtime_error &e) {
            errorMsg = e.what();
            result = "";
        }

        outfile << num1 << "," << num2 << "," << rep << "," << op << ","
                << width << "," << result << "," << overflowFlag << "," << errorMsg << "\n";
    }

    infile.close();
    outfile.close();
    cout << "Processing complete. Output saved to " << outputFile << "\n";
}

// Handles manual interactive input
void runCustomMode() {
    string num1, num2, rep, op;
    int width;

    cout << "Enter bit width: ";
    cin >> width;

    do {
        cout << "Enter first binary number (" << width << " bits): ";
        cin >> num1;
        if (!isValidBinary(num1, width)) {
            cout << "Invalid input! Please enter a " << width << "-bit binary number.\n";
        }
    } while (!isValidBinary(num1, width));

    do {
        cout << "Enter second binary number (" << width << " bits): ";
        cin >> num2;
        if (!isValidBinary(num2, width)) {
            cout << "Invalid input! Please enter a " << width << "-bit binary number.\n";
        }
    } while (!isValidBinary(num2, width));

    do {
        cout << "Enter representation type (unsigned, signed_magnitude, ones_complement, twos_complement): ";
        cin >> rep;
        if (!isValidRepresentation(rep)) {
            cout << "Invalid representation! Try again.\n";
        }
    } while (!isValidRepresentation(rep));

    do {
        cout << "Enter operation (add, sub, mul, div): ";
        cin >> op;
        if (!isValidOperation(op)) {
            cout << "Invalid operation! Try again.\n";
        }
    } while (!isValidOperation(op));

    cout << "\nResult: " << binary_arithmetic(num1, num2, rep, op, width) << "\n";
}

//test_suite
struct TestCase {
    string num1;
    string num2;
    string rep_type;
    string op;
    int bit_width;
};

void test_suite() {
    vector<TestCase> tests = {
        {"0110", "0011", "unsigned", "add", 4},
        {"01010", "00010", "twos_complement", "sub", 5},
        {"000101", "000010", "signed_magnitude", "mul", 6},
        {"1111", "0001", "ones_complement", "div", 4},
        {"10011111", "00101100", "twos_complement", "add", 8},
        {"0010", "0000", "unsigned", "div", 4}
    };

    cout << "\n===== Running Test Suite =====\n";

    for (size_t i = 0; i < tests.size(); ++i) {
        cout << "Test " << (i+1) << ": "
             << "num1=" << tests[i].num1 << ", num2=" << tests[i].num2
             << ", rep=" << tests[i].rep_type << ", op=" << tests[i].op
             << ", bit_width=" << tests[i].bit_width << "\n";

        string result = binary_arithmetic(tests[i].num1, tests[i].num2, tests[i].rep_type, tests[i].op, tests[i].bit_width);

        cout << "Output: " << result << "\n\n";
    }

    cout << "===== Test Suite Complete =====\n";
}

// Main menu
int main() {
    cout << "Select mode:\n";
    cout << "1. CSV mode (read/write files)\n";
    cout << "2. Custom mode (manual input)\n";
    cout << "3. Run test suite\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        runCSVMode();
    } 
    else if (choice == 2) {
        runCustomMode();
    } 
    else if(choice == 3){
        test_suite();
    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
