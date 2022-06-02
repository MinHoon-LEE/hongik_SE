#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

ifstream cin(INPUT_FILE_NAME);
ofstream cout(OUTPUT_FILE_NAME);

// 클래스 선언부
class Product
{
private:
    string salerID;
    string productName;
    string productionCompanyName;
    int price;
    int stock;
    int soldQuantity;
    float averageRating;    //Q&A에 정수로 표현하면 된다고 답변.
    int sumRating;
    int ratingCount;
public:
    Product();
    Product(string pName, string pCName, int pr, int st);
    ~Product();
    string getSalerID();
    string getProductName();
    string getProductionCompanyName();
    int getPrice();
    int getStock();
    int getSoldQuantity();
    int getTotalPrice(); //판매 총액
    float getAverageRating();
    void purchaseProduct();
    void addRating(int rating);
};

class Member
{
private:
    string name;
    int SSN;
    string ID;
    string password;
    vector<Product*> purchaseProduct;
public:
    Member();
    Member(string mName, int ssn, string id, string pwd);
    ~Member();
    int getSSN();
    string getID();
    string getPassword();
    string getName();
    void addPurchaseProduct();
    vector<Product*> listPurchaseProduct();
};

class RegisterProductUI
{
private:
public:
    void enterPrintNewProduct();
    void printNewProduct();
};
class RegisterProduct
{
private:
public:
    RegisterProduct();
};

//판매 중인 의류 조회
class CheckProductSellingUI
{
private:
public:
    void printProductSellingUI();
};
class CheckProductSelling
{
private:
public:
    CheckProductSelling();
};

//판매 완료 상품 조회 
class CheckProductSoldUI
{
private:
public:
    void printProductSoldUI();
};
class CheckProductSold
{
private:
public:
    CheckProductSold();
};

//판매 내역 통계 출력
class PrintStatUI
{
private:
public:
    void printStatUI();
};
class PrintStat
{
private:
public:
    PrintStat();
};

// 전역 변수 선언
vector<Member> memberTable;
vector<Product*> productTable;
int loginMember;
int searchedProduct;

bool compare(Product* a, Product* b)
{
    return a->getProductName() < b->getProductName();
}

//판매할 의류 등록
void RegisterProductUI::enterPrintNewProduct()
{
    string productName;
    string productionCompanyName;
    int price;
    int stock;

    cin >> productName >> productionCompanyName >> price >> stock;
    Product* p = new Product(productName, productionCompanyName, price, stock);
    productTable.push_back(p);
}
void RegisterProductUI::printNewProduct()
{
    cout << "> " << productTable.back()->getProductName() << " " << productTable.back()->getProductionCompanyName() << " " << productTable.back()->getPrice() << " " << productTable.back()->getStock() << endl;
}
RegisterProduct::RegisterProduct()
{
    RegisterProductUI* regProUI = new RegisterProductUI;
    regProUI->enterPrintNewProduct(); //입력

    regProUI->printNewProduct();//출력


    delete regProUI;
}

//판매 중인 의류 조회
void CheckProductSellingUI::printProductSellingUI()
{
    //판매 중인 의류 출력
    const size_t tableSize = productTable.size();
    for (int i = 0; i < tableSize; i++) {
        if (productTable[i]->getSalerID() == memberTable[loginMember].getID() && productTable[i]->getStock() > 0)
        {
            cout << "> " << productTable[i]->getProductName() << " " << productTable[i]->getProductionCompanyName() << " " << productTable[i]->getPrice() << " " << productTable[i]->getStock() << endl;
        }
    }
}
CheckProductSelling::CheckProductSelling()
{
    CheckProductSellingUI* cPSUI = new CheckProductSellingUI();
    cPSUI->printProductSellingUI();
    delete cPSUI;
}

//판매 완료 상품 조회
void CheckProductSoldUI::printProductSoldUI()
{
    //판매 완료된 의류 출력
    const size_t tableSize = productTable.size();
    for (int i = 0; i < tableSize; i++) {
        if (productTable[i]->getSalerID() == memberTable[loginMember].getID() && productTable[i]->getStock() == 0)
        {
            cout << "> " << productTable[i]->getProductName() << " " << productTable[i]->getProductionCompanyName() << " " << productTable[i]->getPrice() << " " << productTable[i]->getSoldQuantity() << " " << productTable[i]->getAverageRating() << endl;
        }
    }
}
CheckProductSold::CheckProductSold()
{
    CheckProductSoldUI* cPSoUI = new CheckProductSoldUI();
    sort(productTable.begin(), productTable.end(), compare);
    cPSoUI->printProductSoldUI();
    delete cPSoUI;
}
//판매 내역 통계 출력
void PrintStatUI::printStatUI()
{
    const size_t tableSize = productTable.size();
    for (int i = 0; i < tableSize; i++) {
        if (productTable[i]->getSalerID() == memberTable[loginMember].getID() && productTable[i]->getSoldQuantity() > 0)
        {
            cout << "> " << productTable[i]->getProductName() << " " << productTable[i]->getTotalPrice() << " " << productTable[i]->getAverageRating() << endl;
        }
    }
}
PrintStat::PrintStat()
{
    PrintStatUI* PSUI = new PrintStatUI();
    PSUI->printStatUI();
    delete PSUI;
}

Product::Product()
{
}
Product::Product(string pName, string pCName, int pr, int st)
{
    salerID = memberTable[loginMember].getID();
    productName = pName;
    productionCompanyName = pCName;
    price = pr;
    stock = st;
    soldQuantity = 0;
    averageRating = 0;
    sumRating = 0;
    ratingCount = 0;
}
Product::~Product()
{
}
string Product::getSalerID()
{
    return salerID;
}
string Product::getProductName()
{
    return productName;
}
string Product::getProductionCompanyName()
{
    return productionCompanyName;
}
int Product::getPrice()
{
    return price;
}
int Product::getStock()
{
    return stock;
}
int Product::getSoldQuantity()
{
    return soldQuantity;
}
float Product::getAverageRating()
{
    return averageRating;
}
void Product::purchaseProduct()
{
    stock--;
    soldQuantity++;
}
void Product::addRating(int rating)
{
    sumRating += rating;
    ratingCount++;
    averageRating = (float)sumRating / ratingCount;
    averageRating = round(averageRating);
}
int Product::getTotalPrice()
{
    return soldQuantity * price;
}

Member::Member()
{
}
Member::Member(string mName, int ssn, string id, string pwd)
{
    name = mName;
    SSN = ssn;
    ID = id;
    password = pwd;
}
Member::~Member()
{
}
string Member::getName()
{
    return name;
}

string Member::getID()
{
    return ID;
}
string Member::getPassword()
{
    return password;
}
int Member::getSSN()
{
    return SSN;
}


void Member::addPurchaseProduct()
{
    purchaseProduct.push_back(productTable[searchedProduct]);
}
vector<Product*> Member::listPurchaseProduct()
{
    return purchaseProduct;
}




void doTask();

int main() {

    doTask();

    cin.close();
    cout.close();
}

void doTask()
{
    // 메뉴 파싱을 위한 level 구분을 위한 변수
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;

    while (!is_program_exit)
    {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        cin >> menu_level_1 >> menu_level_2;

        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1)
        {
        case 1:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                cout << "1.1 회원가입" << endl;

                //SignUp* signUp = new SignUp();
                //delete signUp;

                cout << endl;
                break;
            }
            case 2:
            {
                cout << "1.2. 회원탈퇴" << endl;

                //WithDrawal* withDrawal = new WithDrawal();
                //delete withDrawal;

                cout << endl;
                break;
            }
            }
            break;
        }
        case 2:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                cout << "2.1. 로그인" << endl;

                //LogIn* logIn = new LogIn();
                //delete logIn;

                cout << endl;
                break;
            }
            case 2:
            {
                cout << "2.2. 로그아웃" << endl;

                //LogOut* logOut = new LogOut();
                //delete logOut;

                cout << endl;
                break;
            }
            }
            break;
        }
        case 3:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                cout << "3.1. 판매 의류 등록" << endl;
                RegisterProduct* rp = new RegisterProduct;
                delete rp;

                cout << endl;
                break;
            }
            case 2:
            {
                cout << "3.2. 등록 상품 조회" << endl;
                CheckProductSelling* cps = new CheckProductSelling;
                delete cps;

                cout << endl;
                break;
            }
            case 3:
            {
                cout << "3.3. 판매 완료 상품 조회" << endl;
                CheckProductSold* cpso = new CheckProductSold;
                delete cpso;

                cout << endl;
                break;
            }
            }
            break;
        }
        case 4:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                cout << "4.1. 상품 정보 검색" << endl;

                //SearchProduct* sp = new SearchProduct;
                //delete sp;

                cout << endl;
                break;
            }
            case 2:
            {
                cout << "4.2. 상품 구매" << endl;

                //PurchaseProduct* pp = new PurchaseProduct;
                //delete pp;

                cout << endl;
                break;
            }
            case 3:
            {
                cout << "4.3. 상품 구매 내역 조회" << endl;

                //CheckPurchaseHistory* cph = new CheckPurchaseHistory;
                //delete cph;

                cout << endl;
                break;
            }
            case 4:
            {
                cout << "4.4. 상품 구매만족도 평가" << endl;

                //EvaluateRating* evaluateRating = new EvaluateRating;
                //delete evaluateRating;

                cout << endl;
                break;
            }
            }
            break;
        }
        case 5:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                cout << "5.1. 판매 상품 통계" << endl;
                PrintStat* ps = new PrintStat;
                delete ps;

                cout << endl;
                break;
            }
            }
            break;
        }
        case 6:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                cout << "6.1. 종료" << endl;
                is_program_exit = 1;
                cout << endl;
                break;
            }
            }
            break;
        }
        }
    }
}

