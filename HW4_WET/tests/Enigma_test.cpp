#include "../Enigma.h"
#include "../mtmtest.h"
#include "../Exceptions.h"
#include <assert.h>


#define NAME "c++ is sucks"
#define ELEMENTS 3
#define OUTPUT "c++ is sucks (0) 0"

using namespace mtm::escaperoom;

static void testConstructor() {
    ASSERT_NO_THROW(Enigma(NAME,EASY_ENIGMA));
    ASSERT_NO_THROW(Enigma(NAME,MEDIUM_ENIGMA));
    ASSERT_NO_THROW(Enigma(NAME,HARD_ENIGMA));
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    ASSERT_THROWS(EnigmaIllegalSizeParamException,Enigma(NAME,EASY_ENIGMA,2,my_elements));
    ASSERT_NO_THROW(Enigma(NAME,EASY_ENIGMA,ELEMENTS,my_elements));
}

static void testGetName(){
    Enigma e1=Enigma(NAME,EASY_ENIGMA);
    ASSERT_EQUALS(e1.getName(),NAME);
}

static void testGetDifficulty() {
    Enigma e1=Enigma(NAME,EASY_ENIGMA);
    Enigma e2=Enigma(NAME,MEDIUM_ENIGMA);
    Enigma e3=Enigma(NAME,HARD_ENIGMA);
    ASSERT_EQUALS(e1.getDifficulty(),EASY_ENIGMA);
    ASSERT_EQUALS(e2.getDifficulty(),MEDIUM_ENIGMA);
    ASSERT_EQUALS(e3.getDifficulty(),HARD_ENIGMA);
}

static void testOperatorOutput() {
    Enigma e1=Enigma(NAME,EASY_ENIGMA);
    std::stringstream output;
    output << e1;
    ASSERT_TRUE(output.str()==OUTPUT);
}

static void testRemoveElement() {
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    Enigma e1 = Enigma(NAME, EASY_ENIGMA,ELEMENTS, my_elements);
    ASSERT_THROWS(EnigmaElementNotFoundException,e1.removeElement("YEHEZKEL"));
    ASSERT_NO_THROW(e1.removeElement("IDO"));
    ASSERT_THROWS(EnigmaElementNotFoundException,e1.removeElement("IDO"));
    ASSERT_NO_THROW(e1.removeElement("SHLOMI"));
    ASSERT_THROWS(EnigmaElementNotFoundException,e1.removeElement("SHLOMI"));
    ASSERT_NO_THROW(e1.removeElement("MTM"));
    ASSERT_THROWS(EnigmaNoElementsException,e1.removeElement("MTM"));
}

static void testAddElement() {
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    Enigma e1 = Enigma(NAME, EASY_ENIGMA,ELEMENTS, my_elements);
    ASSERT_NO_THROW(e1.addElement("YEHEZKEL"));
    ASSERT_NO_THROW(e1.removeElement("YEHEZKEL"));
    ASSERT_NO_THROW(e1.addElement("YEHEZKEL"));
    ASSERT_NO_THROW(e1.addElement("YEHEZKEL"));
    ASSERT_NO_THROW(e1.addElement("DABI"));
    ASSERT_NO_THROW(e1.addElement("234112"));
}
static void testCopyConstructor() {
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    Enigma e1=Enigma(NAME,EASY_ENIGMA,ELEMENTS,my_elements);
    Enigma e2(e1);
    ASSERT_EQUALS(e2.getName(),NAME);
    ASSERT_EQUALS(e2.getDifficulty(),EASY_ENIGMA);
    ASSERT_NO_THROW(e2.removeElement("IDO"));
    ASSERT_THROWS(EnigmaElementNotFoundException,e2.removeElement("IDO"));
    ASSERT_NO_THROW(e2.removeElement("SHLOMI"));
    ASSERT_THROWS(EnigmaElementNotFoundException,e2.removeElement("SHLOMI"));
    ASSERT_NO_THROW(e2.removeElement("MTM"));
    ASSERT_THROWS(EnigmaNoElementsException,e2.removeElement("MTM"));
    ASSERT_NO_THROW(e1.removeElement("IDO"));
    ASSERT_THROWS(EnigmaElementNotFoundException,e1.removeElement("IDO"));
    ASSERT_NO_THROW(e1.removeElement("SHLOMI"));
    ASSERT_THROWS(EnigmaElementNotFoundException,e1.removeElement("SHLOMI"));
    ASSERT_NO_THROW(e1.removeElement("MTM"));
    ASSERT_THROWS(EnigmaNoElementsException,e1.removeElement("MTM"));
}

static void testOperatorAssignment() {
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    Enigma e1=Enigma(NAME,EASY_ENIGMA,ELEMENTS,my_elements);
    ASSERT_NO_THROW(e1==e1);
    set<string> my_elements2;
    my_elements2.insert("c is better");
    my_elements2.insert("c is much better");
    Enigma e2=Enigma("temp",MEDIUM_ENIGMA,2,my_elements2);
    e2=e1;
    ASSERT_EQUALS(e2.getName(),NAME);
    ASSERT_EQUALS(e2.getDifficulty(),EASY_ENIGMA);
    ASSERT_NO_THROW(e2.removeElement("IDO"));
    ASSERT_THROWS(EnigmaElementNotFoundException,e2.removeElement("IDO"));
    ASSERT_NO_THROW(e2.removeElement("SHLOMI"));
    ASSERT_THROWS(EnigmaElementNotFoundException,e2.removeElement("SHLOMI"));
    ASSERT_NO_THROW(e2.removeElement("MTM"));
    ASSERT_THROWS(EnigmaNoElementsException,e2.removeElement("MTM"));
}

static void testOperatorEqual() {
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    Enigma e1=Enigma(NAME,EASY_ENIGMA,ELEMENTS,my_elements);
    Enigma e2=Enigma(NAME,EASY_ENIGMA);
    ASSERT_TRUE(e1==e2);
    ASSERT_TRUE(e2==e1);
    ASSERT_EQUALS(e1,e2);

}

static void testOperatorNOTEqual() {
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    Enigma e1 = Enigma(NAME, EASY_ENIGMA, ELEMENTS,my_elements);
    Enigma e2 = Enigma(NAME, MEDIUM_ENIGMA, ELEMENTS,my_elements);
    Enigma e3 = Enigma("temp", EASY_ENIGMA, ELEMENTS,my_elements);
    ASSERT_TRUE(e1!=e2);
    ASSERT_TRUE(e3!=e2);
    ASSERT_TRUE(e1!=e3);
    ASSERT_NOT_EQUAL(e1,e3);
    ASSERT_NOT_EQUAL(e2,e3);
    ASSERT_NOT_EQUAL(e2,e1);
}

static void testOperatorBigger() {
    Enigma e1=Enigma(NAME,EASY_ENIGMA);
    Enigma e2=Enigma(NAME,MEDIUM_ENIGMA);
    Enigma e3=Enigma(NAME,HARD_ENIGMA);
    ASSERT_TRUE(e2>e1);
    ASSERT_TRUE(e3>e1);
    ASSERT_TRUE(e3>e2);

}

static void testOperatorSmaller() {
    Enigma e1 = Enigma(NAME, EASY_ENIGMA);
    Enigma e2 = Enigma(NAME, MEDIUM_ENIGMA);
    Enigma e3 = Enigma(NAME, HARD_ENIGMA);
    ASSERT_TRUE(e1<e2);
    ASSERT_TRUE(e1 < e3);
    ASSERT_TRUE(e2 < e3);
}

static void testareEqualyComplex() {
    set<string> my_elements1;
    my_elements1.insert("IDO");
    my_elements1.insert("SHLOMI");
    my_elements1.insert("MTM");
    set<string> my_elements2;
    my_elements2.insert("YEHEZKEL");
    my_elements2.insert("DABI");
    my_elements2.insert("234122");
    Enigma e1 = Enigma(NAME, EASY_ENIGMA,ELEMENTS,my_elements1);
    Enigma e2 = Enigma("temp", EASY_ENIGMA,ELEMENTS,my_elements2);
    Enigma e3 = Enigma(NAME, EASY_ENIGMA);
    Enigma e4 = Enigma(NAME, HARD_ENIGMA);
    ASSERT_TRUE(e1.areEqualyComplex(e2));
    ASSERT_TRUE(e2.areEqualyComplex(e1));
    ASSERT_TRUE(!e1.areEqualyComplex(e3));
    ASSERT_TRUE(!e1.areEqualyComplex(e4));
    ASSERT_TRUE(!e2.areEqualyComplex(e3));
}

int main() {
    RUN_TEST(testConstructor);
    RUN_TEST(testGetName);
    RUN_TEST(testGetDifficulty);
    RUN_TEST(testOperatorOutput);
    RUN_TEST(testRemoveElement);
    RUN_TEST(testAddElement);
    RUN_TEST(testCopyConstructor);
    RUN_TEST(testOperatorAssignment);
    RUN_TEST(testOperatorEqual);
    RUN_TEST(testOperatorNOTEqual);
    RUN_TEST(testOperatorBigger);
    RUN_TEST(testOperatorSmaller);
    RUN_TEST(testareEqualyComplex);
}