#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

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
    float averageRating;
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
    vector<Product*> registerProduct;
    vector<Product*> purchaseProduct;
public:
    Member();
    Member(string mName, int ssn, string id, string pwd);
    ~Member();
    string getName();
    void addPurchaseProduct();
    vector<Product*> listPurchaseProduct();
};

class SearchProductUI
{
public:
    string enterProductName();
    void displayProductDetails(int productIndex);
};

class SearchProduct
{
public:
    SearchProduct();
    int searchProductDetails(string searchKeyword);
};

class PurchaseProductUI
{
public:
    void printPurchaseCompleteMessage();
};

class PurchaseProduct
{
public:
    PurchaseProduct();

};

class CheckPurchaseHistoryUI
{
public:
    void displayPurchaseHistory(vector<Product*> productList);
};

class CheckPurchaseHistory
{
public:
    CheckPurchaseHistory();
};

class EvaluateRatingUI
{
public:
    string selectProduct();
    int enterRating();
    void PrintEvaluateCompleteMessage(int selectedProduct);
};

class EvaluateRating
{
public:
    EvaluateRating();
};

// 전역 변수 선언
vector<Member> memberTable;
vector<Product> productTable;
int loginMember;
int searchedProduct;

// 클래스 구현부
string SearchProductUI::enterProductName()
{
    string productName;
    cin >> productName;
    return productName;
}
void SearchProductUI::displayProductDetails(int productIndex)
{
    if (productIndex == -1) cout << "조건에 맞는 상품이 없습니다." << endl;
    else
    {
        string salerID = productTable[productIndex].getSalerID();
        string productName = productTable[productIndex].getProductName();
        string productionCompanyName = productTable[productIndex].getProductionCompanyName();
        int price = productTable[productIndex].getPrice();
        int stock = productTable[productIndex].getStock();
        float averageRating = productTable[productIndex].getAverageRating();
        searchedProduct = productIndex;
        cout << "> " << salerID << " " << productName << " " << productionCompanyName << " " << price << " " << stock << " " << averageRating << endl;
    }
}

SearchProduct::SearchProduct()
{
    SearchProductUI* searchProductUI = new SearchProductUI();
    string searchKeyword = searchProductUI->enterProductName();
    int productIndex = searchProductDetails(searchKeyword);
    searchProductUI->displayProductDetails(productIndex);
    delete searchProductUI;
}
int SearchProduct::searchProductDetails(string searchKeyword)
{
    for (int i = 0; i < productTable.size(); i++)
    {
        if (productTable[i].getProductName() == searchKeyword && productTable[i].getStock() > 0)
        {
            return i;
        }
    }
    return -1;
}

void PurchaseProductUI::printPurchaseCompleteMessage()
{
    cout << "> " << productTable[searchedProduct].getSalerID() << " " << productTable[searchedProduct].getProductName() << endl;
}

PurchaseProduct::PurchaseProduct()
{
    PurchaseProductUI* purchaseProductUI = new PurchaseProductUI;
    productTable[searchedProduct].purchaseProduct();
    memberTable[loginMember].addPurchaseProduct();
    purchaseProductUI->printPurchaseCompleteMessage();
    delete purchaseProductUI;
}

void CheckPurchaseHistoryUI::displayPurchaseHistory(vector<Product*> productList)
{
    for (int i = 0; i < productList.size(); i++)
    {
        cout << "> " << productList[i]->getSalerID() << " " << productList[i]->getProductName() << " " << productList[i]->getProductionCompanyName();
        cout << " " << productList[i]->getPrice() << " " << productList[i]->getStock() << " " << productList[i]->getAverageRating() << endl;
    }
}

bool compare(Product* a, Product* b)
{
    return a->getProductName() < b->getProductName();
}
CheckPurchaseHistory::CheckPurchaseHistory()
{
    CheckPurchaseHistoryUI* cphUI = new CheckPurchaseHistoryUI;
    vector<Product*> purchaseProductList = memberTable[loginMember].listPurchaseProduct();
    sort(purchaseProductList.begin(), purchaseProductList.end(), compare);
    cphUI->displayPurchaseHistory(purchaseProductList);
    delete cphUI;
}

string EvaluateRatingUI::selectProduct()
{
    string productName;
    cin >> productName;
    return productName;
}
int EvaluateRatingUI::enterRating()
{
    int rating;
    cin >> rating;
    return rating;
}
void EvaluateRatingUI::PrintEvaluateCompleteMessage(int selectedProduct)
{
    cout << "> " << productTable[selectedProduct].getSalerID() << " " << productTable[selectedProduct].getProductName() << " " << productTable[selectedProduct].getAverageRating() << endl;
}

EvaluateRating::EvaluateRating()
{
    EvaluateRatingUI* erUI = new EvaluateRatingUI;
    int rating;
    string selectedProduct;
    selectedProduct = erUI->selectProduct();
    rating = erUI->enterRating();
    for (int i = 0; i < productTable.size(); i++)
    {
        if (productTable[i].getProductName() == selectedProduct)
        {
            productTable[i].addRating(rating);
            erUI->PrintEvaluateCompleteMessage(i);
            break;
        }
    }
    delete erUI;
}

Product::Product()
{
}
Product::Product(string pName, string pCName, int pr, int st)
{
    salerID = memberTable[loginMember].getName();
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
void Member::addPurchaseProduct()
{
    purchaseProduct.push_back(&productTable[searchedProduct]);
}
vector<Product*> Member::listPurchaseProduct()
{
    return purchaseProduct;
}

void doTask();

int main() {
    //ifstream cin;
    //ofstream cout;
    //cin.open(INPUT_FILE_NAME);
    //cout.open(OUTPUT_FILE_NAME);

    memberTable.push_back(Member("CWS", 123, "qwe", "pwd123"));
    productTable.push_back(Product("aa", "aaa", 100, 10));
    productTable.push_back(Product("bb", "bbb", 200, 20));
    productTable.push_back(Product("cc", "ccc", 300, 30));


    doTask();

    //cin.close();
    //cout.close();
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
                    cout << "1.1. 회원가입" << endl;
                    // ...
                    cout << endl;
                    break;
                }
                case 2:
                {
                    cout << "1.2. 회원탈퇴" << endl;
                    // ...
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
                    // ...
                    cout << endl;
                    break;
                }
                case 2:
                {
                    cout << "2.2. 로그아웃" << endl;
                    // ...
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
                    // ...
                    cout << endl;
                    break;
                }
                case 2:
                {
                    cout << "3.2. 등록 상품 조회" << endl;
                    // ...
                    cout << endl;
                    break;
                }
                case 3:
                {
                    cout << "3.3. 판매 완료 상품 조회" << endl;
                    // ...
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

                    SearchProduct* sp = new SearchProduct;
                    delete sp;

                    cout << endl;
                    break;
                }
                case 2:
                {
                    cout << "4.2. 상품 구매" << endl;
                    
                    PurchaseProduct* pp = new PurchaseProduct;
                    delete pp;

                    cout << endl;
                    break;
                }
                case 3:
                {
                    cout << "4.3. 상품 구매 내역 조회" << endl;
                    
                    CheckPurchaseHistory* cph = new CheckPurchaseHistory;
                    delete cph;

                    cout << endl;
                    break;
                }
                case 4:
                {
                    cout << "4.4. 상품 구매만족도 평가" << endl;
                    
                    EvaluateRating* evaluateRating = new EvaluateRating;
                    delete evaluateRating;

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
                    // ...
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