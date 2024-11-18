#include "ExpressionTree.h"

#define DEBUG() std::cout << "Debug print, line: " << __LINE__ << std::endl; 

#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

int total_tests = 0;
int correct_tests = 0;

template <class T, class U>
void checkTest(string test, T is, U expected) {

    total_tests++;
    if (is == expected) {
        correct_tests++;
        cout << "Passed " << test << endl;
    }
    else {
        cout << "****Failed**** " << test << endl;
        cout << "        Actual: " << is << " Expected: " << expected << endl;
    }

}

int main() {

    string expression;
    ostringstream out;
    string result;

    ExpressionTree et1;
    et1.printParseTreeInOrder(out);
    checkTest("Test 1", out.str(), "");
    checkTest("Test 2", et1.getResult(), 0);

    out.str("");
    out.clear();
    ExpressionTree* et = new ExpressionTree("(4+7)");
    et->printParseTreeInOrder(out);
    checkTest("Test 3", out.str(), "4+7");
    out.str("");
    out.clear();
    et->printParseTreePostOrder(out);
    checkTest("Test 4", out.str(), "4 7 +");
    checkTest("Test 5", et->getResult(), 11);

    out.str("");
    out.clear();
    expression = "(543+321)";
    et->setExpression(expression);
    et->printParseTreePostOrder(out);
    checkTest("Test 6", out.str(), "543 321 +");
    checkTest("Test 7", et->getResult(), 864);

    out.str("");
    out.clear();
    expression = "(7-4)";
    et->setExpression(expression);
    et->printParseTreeInOrder(out);
    checkTest("Test 8", out.str(), "7-4");
    checkTest("Test 9", et->getResult(), 3);

    out.str("");
    out.clear();
    expression = "((2-5)-5)";
    et->setExpression(expression);
    et->printParseTreePostOrder(out);
    checkTest("Test 10", out.str(), "2 5 - 5 -");
    checkTest("Test 11", et->getResult(), -8);

    out.str("");
    out.clear();
    expression = "(4^3)";
    et->setExpression(expression);
    et->printParseTreeInOrder(out);
    checkTest("Test 12", out.str(), "4^3");
    checkTest("Test 13", et->getResult(), 64);

    out.str("");
    out.clear();
    expression = "(5*(6/2))";
    et->setExpression(expression);
    et->printParseTreePostOrder(out);
    checkTest("Test 14", out.str(), "5 6 2 / *");
    checkTest("Test 15", et->getResult(), 15);

    out.str("");
    out.clear();
    expression = "(((((3+12)-7)*120)/(2+3))^3)";
    et->setExpression(expression);
    et->printParseTreeInOrder(out);
    checkTest("Test 16", out.str(), "3+12-7*120/2+3^3");
    checkTest("Test 17", et->getResult(), 7077888);

    out.str("");
    out.clear();
    expression = "(((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3^4)+1)/2))";
    et->setExpression(expression);
    et->printParseTreePostOrder(out);
    checkTest("Test 18", out.str(), "9 2 110 30 2 / - * + 8 * 1000 + 2 / 3 4 ^ 1 + 2 / +");
    checkTest("Test 19", et->getResult(), 1337);


    out.str("");
    out.clear();
    ExpressionTree* et2 = new ExpressionTree(*et);
    et2->printParseTreeInOrder(out);
    checkTest("Test 20", out.str(), "9+2*110-30/2*8+1000/2+3^4+1/2");
    checkTest("Test 21", et2->getResult(), 1337);

    out.str("");
    out.clear();
    ExpressionTree et3 = *et;
    et3.printParseTreePostOrder(out);
    checkTest("Test 22", out.str(), "9 2 110 30 2 / - * + 8 * 1000 + 2 / 3 4 ^ 1 + 2 / +");
    checkTest("Test 23", et3.getResult(), 1337);

    out.str("");
    out.clear();
    et2->setExpression("(5*(6/2))");
    et2->printParseTreeInOrder(out);
    checkTest("Test 24", out.str(), "5*6/2");
    checkTest("Test 25", et2->getResult(), 15);

    out.str("");
    out.clear();
    et->printParseTreePostOrder(out);
    checkTest("Test 26", out.str(), "9 2 110 30 2 / - * + 8 * 1000 + 2 / 3 4 ^ 1 + 2 / +");
    checkTest("Test 27", et->getResult(), 1337);

    delete et;
    et = NULL;
    delete et2;
    et2 = NULL;

    out.str("");
    out.clear();
    et3.printParseTreeInOrder(out);
    checkTest("Test 28", out.str(), "9+2*110-30/2*8+1000/2+3^4+1/2");
    checkTest("Test 29", et3.getResult(), 1337);

    out.str("");
    out.clear();
    et3.setExpression("");
    et3.printParseTreePostOrder(out);
    checkTest("Test 30", out.str(), "");
    checkTest("Test 31", et3.getResult(), 0);

    cout << "************************************\n\n";

    cout << "Passed" << correct_tests << "/" << total_tests << endl;
    cout << "Score:" << (float)correct_tests / total_tests * 60.0 << endl;

    return 0;
}
