#include <iostream>
#include <fci.h>


static int i = 0;
static std::string tokens[] = {"begin", "procedure", "Absmax", "(", "a", ")", "Size", ":", "(", "n", ",", "m", ")",  "Result", ":", "(", "y", ")", "Subscripts", ":", "(", "i", ",", "k", ")", "end"};



//value n, m; array a; integer n, m, i, k; real y;
//comment The absolute greatest element of the matrix a, of size n by m,
//is transferred to y, and the subscripts of this element to i and k;
//begin
//        integer p, q;
//y := 0; i := k := 1;
//for p := 1 step 1 until n do
//for q := 1 step 1 until m do
//if abs(a[p, q]) > y then
//begin y := abs(a[p, q]);
//i := p; k := q
//end
//        end Absmax

void salvaEstado(int *j);
void restauraEstado(int j); // Implementar

std::string getToken();
bool token_isIdentifier(std::string token);

bool program();
bool block();
bool compoundStatement();
bool statement();
bool unlabelledBlock();
bool label();
bool blockHead();
bool declaration();
bool compoundTail();
bool blockHeadRecursao();
bool unlabelledCompound();
bool typeDeclaration();
bool localOrOwnType();
bool type();
bool typeList();
bool simpleVariable();
bool arrayDeclaration();
bool upperBound();
bool boundPairList();
bool arrayList();
bool procedureDeclaration();
bool procedureHeading();
bool procedureBody();
bool procedureIdentifier();
bool token_isLetterString(std::string token);
bool parameterDelimiter();
bool formalParameter();
bool formalParameterList();
bool formalParameterListRecursao();
bool formalParameterPart();
bool identifierList();
bool identifierListRecursao();
bool valuePart();
bool specificationPart();
bool unconditionalStatement();
bool conditionalStatement();
bool lowerBound();
bool basicStatement();
bool unlabelledBasicStatement();
bool forStatement();
bool assignmentStatement();
bool procedureStatement();
bool goToStatement();
bool dummyStatement();
bool leftPartList();
bool booleanExpression();
bool arithmeticExpression();
bool leftPart();
bool boundPairListRecursao();
bool leftPartListRecursao();
bool variable();
bool subscriptedVariable();
bool arrayIdentifier();
bool subscriptExpression();
bool subscriptListRecursao();
bool subscriptList();
bool multiplyingOperator();
bool term();
bool termRecursao();
bool token_isNumber(std::string token);
bool decimalNumber();
bool primary();
bool unsignedNumber();
bool actualParameterPart();
bool actualParameterList();
bool actualParameterListRecursao();
bool token_isString(std::string token);
bool actualParameter();
bool expression();
bool designationalExpression();
bool simpleArithmeticExpression();
bool ifClause();
bool simpleBoolean();
bool implication();
bool arrayListRecursao();
bool implicationRecursao();
bool booleanTerm();
bool booleanTermRecursao();
bool booleanFactor();
bool booleanPrimary();
bool booleanSecondary();
bool booleanFactorRecursao();
bool logicalValue();
bool functionDesignator();
bool relation();
bool relationalOperator();
bool simpleBooleanRecursao();
bool addingOperator();
bool simpleArithmeticExpressionRecursao();
bool ifStatement();
bool forClause();
bool forList();
bool forListElement();
bool arraySegment();
bool boundPair();
bool unsignedInteger();

int main() {
    std::cout << "Iniciado, analisador sintatico!" << std::endl;

    return program(); // Verificar se chegou no final do arquivo!!
}

bool program() {
    int j = 0;

    salvaEstado(&j);
    if (block())
        return true;
    restauraEstado(j);

    if (compoundStatement())
        return true;
    restauraEstado(j);

    return false;
}

bool block() {
    int j = 0;

    salvaEstado(&j);
    if (unlabelledBlock())
        return true;
    restauraEstado(j);

    if (label() && 0 == getToken().compare(":") && block())
        return true;
    restauraEstado(j);

    return false;
}

bool statement() {
    int j = 0;

    salvaEstado(&j);
    if (unconditionalStatement())
        return true;
    restauraEstado(j);

    if (conditionalStatement())
        return true;
    restauraEstado(j);

    if (forStatement())
        return true;
    restauraEstado(j);

    return false;
}

bool forStatement() {
    int j = 0;

    salvaEstado(&j);
    if (forClause() &&  statement())
        return true;
    restauraEstado(j);

    if (label() && forStatement())
        return true;
    restauraEstado(j);

    return false;
}

bool forClause() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("for") && variable() && 0 == getToken().compare(":=") && forList() && 0 == getToken().compare("do"))
        return true;
    restauraEstado(j);

    return false;
}

bool forList() {
    int j = 0;

    salvaEstado(&j);
    if (forListElement())
        return false;
}

bool forListElement() {
    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression())
        return true;
    restauraEstado(j);

    if (arithmeticExpression() && 0 == getToken().compare("step") && arithmeticExpression() && 0 == getToken().compare("until") && arithmeticExpression())
        return true;
    restauraEstado(j);

    if (arithmeticExpression() && 0 == getToken().compare("while") && booleanExpression())
        return true;
    restauraEstado(j);

    return false;
}

bool unconditionalStatement(){
    int j = 0;

    salvaEstado(&j);
    if (basicStatement())
        return true;
    restauraEstado(j);

    if (block())
        return true;
    restauraEstado(j);

    if (conditionalStatement())
        return true;
    restauraEstado(j);


    return false;
}

bool conditionalStatement() {
    int j = 0;

    salvaEstado(&j);
    if (ifStatement())
        return true;
    restauraEstado(j);

    if (ifStatement() && 0 == getToken().compare("else") && statement())
        return true;
    restauraEstado(j);

    if (ifClause() && forStatement())
        return true;
    restauraEstado(j);

    if (label() && 0 == getToken().compare(":") && conditionalStatement())
        return true;
    restauraEstado(j);

    return false;
}

bool ifStatement() {
    int j = 0;

    salvaEstado(&j);
    if (ifClause() && unconditionalStatement())
        return true;
    restauraEstado(j);

    return false;
}

bool basicStatement() {
    int j = 0;

    salvaEstado(&j);
    if (unlabelledBasicStatement())
        return true;
    restauraEstado(j);

    if (label() && 0 == getToken().compare(":") && basicStatement())
        return true;
    restauraEstado(j);


    return false;
}

bool unlabelledBasicStatement() {
    int j = 0;

    salvaEstado(&j);
    if (assignmentStatement())
        return true;
    restauraEstado(j);

    if (goToStatement())
        return true;
    restauraEstado(j);

    if (dummyStatement())
        return true;
    restauraEstado(j);

    if (procedureStatement())
        return true;
    restauraEstado(j);

    return false;
}

bool procedureStatement(){
    int j = 0;

    salvaEstado(&j);
    if (procedureIdentifier() && actualParameterPart())
        return true;
    restauraEstado(j);

    return false;
}

bool dummyStatement() {

    return true;
}

bool goToStatement() {
    // implementar
    return false;
}

bool assignmentStatement() {
    int j = 0;

    salvaEstado(&j);
    if (leftPartList() && arithmeticExpression())
        return true;
    restauraEstado(j);

    if (leftPartList() && booleanExpression())
        return true;
    restauraEstado(j);

    return false;
}

bool leftPartList() {
    int j = 0;

    salvaEstado(&j);
    if (leftPart() && leftPartListRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool leftPartListRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (leftPart() && leftPartListRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool leftPart() {
    int j = 0;

    salvaEstado(&j);
    if (variable() && 0 == getToken().compare(":") && 0 == getToken().compare("="))
        return true;
    restauraEstado(j);

    if (procedureIdentifier() && 0 == getToken().compare(":") && 0 == getToken().compare("="))
        return true;
    restauraEstado(j);

    return false;
}

bool variable() {
    int j = 0;

    salvaEstado(&j);
    if (simpleVariable())
        return true;
    restauraEstado(j);

    if (subscriptedVariable())
        return true;
    restauraEstado(j);

    return false;
}

bool subscriptedVariable() {
    int j = 0;

    salvaEstado(&j);
    if (arrayIdentifier() && 0 == getToken().compare("[") && subscriptList() && 0 == getToken().compare("]"))
        return true;
    restauraEstado(j);

    return false;
}

bool subscriptList() {
    int j = 0;

    salvaEstado(&j);
    if (subscriptExpression() && subscriptListRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool subscriptExpression() {
    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression())
        return true;
    restauraEstado(j);

    return false;
}

bool subscriptListRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare(",") && subscriptExpression() && subscriptListRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool arrayIdentifier() {
    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getToken()))
        return true;
    restauraEstado(j);

    return false;
}

bool booleanExpression() {
    int j = 0;

    salvaEstado(&j);
    if (simpleBoolean())
        return true;
    restauraEstado(j);

    if (ifClause() && simpleBoolean() && 0 == getToken().compare("else") && booleanExpression())
        return true;
    restauraEstado(j);

    return false;
}

bool simpleBoolean() {
    int j = 0;

    salvaEstado(&j);
    if (implication() && simpleBooleanRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool simpleBooleanRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("===") && implication() && simpleBooleanRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool implication() {
    int j = 0;

    salvaEstado(&j);
    if (booleanTerm() && implicationRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool implicationRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("naosei") && booleanTerm() && implicationRecursao())
        return true;
    restauraEstado(j);
    return true;
}

bool booleanTerm() {
    int j = 0;

    salvaEstado(&j);
    if (booleanFactor() && booleanTermRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool booleanTermRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("or") && booleanFactor() && booleanTermRecursao())
        return true;
    restauraEstado(j);


    return true;
}

bool booleanFactor() {
    int j = 0;

    salvaEstado(&j);
    if (booleanSecondary() && booleanFactorRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool booleanFactorRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("and") && booleanSecondary() && booleanFactorRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool booleanSecondary() {
    int j = 0;

    salvaEstado(&j);
    if (booleanPrimary())
        return true;
    restauraEstado(j);

    if (0 == getToken().compare("¬") && booleanPrimary())
        return true;

    return false;
}

bool booleanPrimary() {
    int j = 0;

    salvaEstado(&j);
    if (logicalValue())
        return true;
    restauraEstado(j);

    if (variable())
        return true;
    restauraEstado(j);

    if (functionDesignator())
        return true;
    restauraEstado(j);

    return false;
}

bool logicalValue() {
    int j = 0;

    salvaEstado(&j);
    std::string t = getToken();

    if (t.compare("true") || t.compare("false"))
        return true;
    restauraEstado(j);

    if (relation())
        return true;

    return false;
}

bool relation() {
    int j = 0;

    salvaEstado(&j);
    if (simpleArithmeticExpression() && relationalOperator() && simpleArithmeticExpression())
        return true;
    restauraEstado(j);


    return false;
}

bool relationalOperator() {
    int j = 0;

    salvaEstado(&j);
    std::string token = getToken();

    if (0 == token.compare("<") || 0 == token.compare("<=") || 0 == token.compare("=") || 0 == token.compare("#") || 0 == token.compare(">") || 0 == token.compare(">="))
        return true;

    return false;
}

bool arithmeticExpression() {
    int j = 0;

    salvaEstado(&j);
    if (simpleArithmeticExpression())
        return true;
    restauraEstado(j);

    if (ifClause() && simpleArithmeticExpression() && 0 == getToken().compare("else") && arithmeticExpression())
        return true;
    restauraEstado(j);

    return false;
}

bool ifClause() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("if") && booleanExpression() && 0 == getToken().compare("then"))
        return true;
    restauraEstado(j);

    return false;
}

bool simpleArithmeticExpression() {
    int j = 0;

    salvaEstado(&j);
    if (term() && simpleArithmeticExpressionRecursao())
        return true;
    restauraEstado(j);

    if (addingOperator() && term() && simpleArithmeticExpressionRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool simpleArithmeticExpressionRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (addingOperator() && term() && simpleArithmeticExpressionRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool addingOperator() {
    int j = 0;

    salvaEstado(&j);
    std::string t = getToken();

    if (t.compare("+") || t.compare("-"))
        return true;
    restauraEstado(j);

    return false;
}

bool term() {
    int j = 0;

    salvaEstado(&j);
    if (primary() && termRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool termRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (multiplyingOperator() && primary() && termRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool primary() {
    int j = 0;

    salvaEstado(&j);
    if (unsignedNumber())
        return true;
    restauraEstado(j);

    if (variable())
        return true;
    restauraEstado(j);

    //if (fu)
    // implementar

    if (0 == getToken().compare("(") && arithmeticExpression() && 0 == getToken().compare(")"))
        return true;
    restauraEstado(j);

    return false;
}

bool functionDesignator() {
    int j = 0;

    salvaEstado(&j);
    if (procedureIdentifier() && actualParameterPart())
        return true;
    restauraEstado(j);

    return false;
}

bool actualParameterPart() {
    int j = 0;

    salvaEstado(&j);

    if (0 == getToken().compare("(") && actualParameterList() && 0 == getToken().compare(")"))

        return true;
}

bool actualParameterList() {
    int j = 0;

    salvaEstado(&j);

    if (actualParameter() && actualParameterListRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool actualParameterListRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (parameterDelimiter() && actualParameter())
        return true;
    restauraEstado(j);

    return true;
}

bool actualParameter() {
    int j = 0;

    salvaEstado(&j);
    if (token_isString(getToken()))
        return true;
    restauraEstado(j);

    if (expression())
        return true;
    restauraEstado(j);

    return false;
}

bool expression() {
    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression())
        return true;
    restauraEstado(j);

    if (booleanExpression())
        return true;
    restauraEstado(j);

    if (designationalExpression())
        return true;
    restauraEstado(j);

    return false;
}

bool designationalExpression() {
    int j = 0;

    //implementar
    return false;
}

bool unsignedNumber() {
    int j = 0;

    salvaEstado(&j);

    if (decimalNumber())
        return true;
    restauraEstado(j);

    return false;
}

bool decimalNumber() {
    int j = 0;

    salvaEstado(&j);
    if (token_isNumber(getToken()))
        return true;
    restauraEstado(j);

    return false;
}

bool multiplyingOperator() {
    int j = 0;

    salvaEstado(&j);
    std::string op = getToken();

    if (op.compare("*") || op.compare("/"))
        return true;
    restauraEstado(j);


    return false;
}

bool unlabelledBlock() {
    int j = 0;

    salvaEstado(&j);
    if (blockHead() && 0 == getToken().compare(";") && compoundTail())
        return true;
    restauraEstado(j);

    return false;
}

bool compoundTail() {
    int j = 0;

    salvaEstado(&j);
    if (statement() && 0 == getToken().compare("end"))
        return true;
    restauraEstado(j);

    if (statement() && 0 == getToken().compare(";") && compoundTail())
        return true;
    restauraEstado(j);

    return false;
}


bool compoundStatement() {
    int j = 0;

    salvaEstado(&j);
    if (unlabelledCompound())
        return true;
    restauraEstado(j);

    if (label() && 0 == getToken().compare(":") && compoundStatement())
        return true;
    restauraEstado(j);

    return false;
}


bool blockHead() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("begin") && declaration() && blockHeadRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool blockHeadRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare(";") && declaration() && blockHeadRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool unlabelledCompound() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("begin") && compoundTail())
        return true;
    restauraEstado(j);

    return false;
}

bool declaration() {

    int j = 0;

    salvaEstado(&j);
    if (typeDeclaration())
        return true;
    restauraEstado(j);

    if (arrayDeclaration())
        return true;
    restauraEstado(j);

    if (procedureDeclaration())
        return true;
    restauraEstado(j);

    return false;
}

bool typeDeclaration() {

    int j = 0;

    salvaEstado(&j);
    if (localOrOwnType() && typeList())
        return true;
    restauraEstado(j);

    return false;
}
bool localOrOwnType() {
    int j = 0;

    salvaEstado(&j);
    if (type())
        return true;
    restauraEstado(j);

    if (getToken() == "own" && type())
        return true;
    restauraEstado(j);

    return false;
}

bool type() {
    int j = 0;

    salvaEstado(&j);
    std::string token = getToken();

    if (0 == token.compare("real") || 0 == token.compare("integer") || 0 == token.compare("boolean"))
        return true;
    restauraEstado(j);

    return false;
}

bool typeList() {
    int j = 0;

    salvaEstado(&j);
    if (simpleVariable() || (simpleVariable() && 0 == getToken().compare(",") && typeList()))
        return true;
    restauraEstado(j);

    return false;
}

bool simpleVariable() {
    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getToken()))
        return true;
    restauraEstado(j);

    return false;
}

bool arrayDeclaration() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("array") && arrayList())
        return true;
    restauraEstado(j);

    if (localOrOwnType() && 0 == getToken().compare("array") && arrayList())
        return true;
    restauraEstado(j);

    return false;
}

bool arrayList() {
    int j = 0;

    salvaEstado(&j);
    if (arraySegment() && arrayListRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool arrayListRecursao() {
    int j = 0;

    if (0 == getToken().compare(",") && arraySegment() && arrayListRecursao())
        return true;
    restauraEstado(j);

    return true;
}


bool arraySegment() {
    int j = 0;

    salvaEstado(&j);
    if (arrayIdentifier())
        return true;
    restauraEstado(j);

    if (0 == getToken().compare("[") && boundPairList() && 0 == getToken().compare("]"))
        return true;
    restauraEstado(j);

    if (arrayIdentifier() && 0 == getToken().compare(",") && arraySegment())
        return true;
    restauraEstado(j);

    return false;
}

bool boundPairList() {
    int j = 0;

    salvaEstado(&j);
    if (boundPair() && boundPairListRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool boundPairListRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare(",") && boundPair() && boundPairListRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool boundPair() {
    int j = 0;

    salvaEstado(&j);
    if (lowerBound() && 0 == getToken().compare(":") && upperBound())
        return true;
    restauraEstado(j);

    return false;
}

bool lowerBound() {
    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression())
        return true;
    restauraEstado(j);

    return false;
}

bool upperBound() {
    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression())
        return true;
    restauraEstado(j);

    return false;
}



bool procedureDeclaration() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("procedure") && procedureHeading() && procedureBody())
        return true;
    restauraEstado(j);

    if (type() && 0 == getToken().compare("procedure") && procedureHeading() && procedureBody())
        return true;
    restauraEstado(j);

    return false;
}

bool procedureHeading() {
    int j = 0;

    salvaEstado(&j);
    if (procedureIdentifier() && formalParameterPart() && 0 == getToken().compare(";") && valuePart() && specificationPart())
        return true;
    restauraEstado(j);

    return false;
}

bool valuePart() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("value") && identifierList() && 0 == getToken().compare(";"))
        return true;
    restauraEstado(j);

    return true;
}

bool specificationPart() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare("string"))
        return true;
    restauraEstado(j);

    if (type())
        return true;
    restauraEstado(j);

    if (0 == getToken().compare("array"))
        return true;
    restauraEstado(j);

    if (type() && 0 == getToken().compare("array"))
        return true;
    restauraEstado(j);

    if (0 == getToken().compare("label"))
        return true;
    restauraEstado(j);

    if (0 == getToken().compare("switch"))
        return true;
    restauraEstado(j);

    if (0 == getToken().compare("procedure"))
        return true;
    restauraEstado(j);

    if (type() && 0 == getToken().compare("procedure"))
        return true;
    restauraEstado(j);

    return true;
}

bool identifierList() {
    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getToken()) && identifierListRecursao())
        return true;

    restauraEstado(j);
    return false;
}

bool identifierListRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare(",") && token_isIdentifier(getToken()) && identifierListRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool procedureIdentifier() {
    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getToken()))
        return true;
    restauraEstado(j);

    return false;
}

bool formalParameterPart() {
    int j = 0;

    salvaEstado(&j);

    if (0 == getToken().compare("(") && formalParameterList() && 0 == getToken().compare(")"))
        return true;
    restauraEstado(j);

    return true;
}

bool formalParameterList() {
    int j = 0;

    salvaEstado(&j);
    if (formalParameter() && formalParameterListRecursao())
        return true;
    restauraEstado(j);

    return false;
}

bool formalParameterListRecursao() {
    int j = 0;

    salvaEstado(&j);
    if (parameterDelimiter() && formalParameter() && formalParameterListRecursao())
        return true;
    restauraEstado(j);

    return true;
}

bool parameterDelimiter() {
    int j = 0;

    salvaEstado(&j);
    if (0 == getToken().compare(","))
        return true;
    restauraEstado(j);

    if (0 == getToken().compare(")") && token_isLetterString(getToken()) && 0 == getToken().compare(":") && 0 == getToken().compare("("))
        return true;
    restauraEstado(j);

    return false;
}

bool token_isLetterString(std::string token){
    return true;
}

bool formalParameter() {
    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getToken()))
        return true;
    restauraEstado(j);

    return false;
}

bool procedureBody() {
    int j = 0;

    salvaEstado(&j);
    if (statement())
        return true;
    restauraEstado(j);

    return false;
}

bool label() {
    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getToken()))
        return true;
    restauraEstado(j);

    if (unsignedInteger())
        return true;
    restauraEstado(j);

    return false;
}

bool unsignedInteger() {
    int j = 0;

    salvaEstado(&j);
    if (token_isNumber(getToken()))
        return true;
    restauraEstado(j);

    return false;
}

void salvaEstado(int *j) {

    *j = i;

    return;
}

void restauraEstado(int j) {
    i = j;
    return;
}

std::string getToken() {

    std::string a = tokens[i];
    i++;

    return a;
}

bool token_isIdentifier(std::string token) {
    // implementar
    return token == "a" || token == "n" || token == "m" || token == "y" || token == "i" || token == "k" || token == "Absmax";
}

bool token_isNumber(std::string token) {
    //implementar
    return true;
}

bool token_isString(std::string token) {
    //implementar
    return true;
}