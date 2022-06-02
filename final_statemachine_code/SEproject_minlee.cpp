#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// Ŭ���� �����
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
    int getSSN();
    string getID();
    string getPassword();
    string getName();
    void addPurchaseProduct();
    vector<Product*> listPurchaseProduct();
};


//////////minlee///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////minlee///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////minlee///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////minlee/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SignUpUI
{
private:
public:
    SignUpUI();
    Member putInformation();
    void showSignUpMessage(Member memeber);
};

class SignUp
{
private:
public:
    SignUp();
    void insertInformation(Member member);
};


class LogInUI
{
private:
public:
    LogInUI();
    Member putIdPwd();
    void showLogInMessage(Member member, int tmp);
};

class LogIn
{
private:
public:
    LogIn();
    int insertIdPwd(Member member);
};


class LogOutUI
{
private:
public:
    LogOutUI();
    void showLogOutMessage();
};

class LogOut
{
private:
public:
    LogOut();
    void logout();
};

class WithDrawalUI
{
private:
public:
    WithDrawalUI();
    void showWithDrawalMessage();
};

class WithDrawal
{
private:
public:
    WithDrawal();
    void withdrawMember();
};

//////////minlee///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////minlee///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////minlee///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////minlee///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

// ���� ���� ����
vector<Member> memberTable;
vector<Product> productTable;
int loginMember;
int searchedProduct;

// Ŭ���� ������

/////////////////// Minlee////////////////////
/////////////////// MInlee////////////////////
// /////////////////// MInlee////////////////////
// /////////////////// MInlee////////////////////
/////////////////// MInlee////////////////////
SignUpUI::SignUpUI()
{

}

Member SignUpUI::putInformation()
{
    string name;
    int SSN;
    string ID;
    string password;

    cin >> name >> SSN >> ID >> password;
    Member* member = new Member(name, SSN, ID, password);
    return *member;
}

SignUp::SignUp()
{
    SignUpUI* signUpUI = new SignUpUI();
    Member newMember = signUpUI->putInformation();
    //�߰� 
    insertInformation(newMember);
    signUpUI->showSignUpMessage(newMember);
    delete signUpUI;
}

void SignUp::insertInformation(Member newMember)
{
    memberTable.push_back(newMember);
}

void SignUpUI::showSignUpMessage(Member member)
{
    cout << member.getName() << " ";
    cout << member.getSSN() << " ";
    cout << member.getID() << " ";
    cout << member.getPassword() << endl;
}

LogInUI::LogInUI()
{

}

LogIn::LogIn()
{
    LogInUI* logInUI = new LogInUI();
    Member checkMember = logInUI->putIdPwd();
    int tmp;
    tmp = insertIdPwd(checkMember);
    logInUI->showLogInMessage(checkMember, tmp);
    delete logInUI;
}

int LogIn::insertIdPwd(Member checkMember)
{
    int i;
    int tmp;
    tmp = 0;
    //����//
    for (i = 0; i < memberTable.size(); i++)
    {
        if (memberTable[i].getID() == checkMember.getID() && memberTable[i].getPassword() == checkMember.getPassword())
        {
            loginMember = i;
            tmp = 1;
        }
    }
    //����// 

    return tmp;

}

Member LogInUI::putIdPwd()
{
    string id;
    string password;
    cin >> id >> password;
    Member* member = new Member("0", 0, id, password);
    return *member;
}

void LogInUI::showLogInMessage(Member member, int tmp)
{
    if (tmp == 1)
    {
        cout << member.getID() << " " << member.getPassword();
    }

    else
    {
        cout << "�߸��� �α��� �����Դϴ�.";
    }

    cout << endl;
}


LogOut::LogOut()
{
    LogOutUI* logOutUI = new LogOutUI();
    logout();
    logOutUI->showLogOutMessage();
}
LogOutUI::LogOutUI()
{

}

void LogOut::logout()
{

}

void LogOutUI::showLogOutMessage()
{
    cout << memberTable[loginMember].getID() << endl;
}


WithDrawal::WithDrawal()
{
    WithDrawalUI* withDrawalUI = new WithDrawalUI();
    withdrawMember();
    withDrawalUI->showWithDrawalMessage();
}

WithDrawalUI::WithDrawalUI()
{

}

void WithDrawalUI::showWithDrawalMessage()
{
    cout << memberTable[loginMember].getID() << endl;
}

void WithDrawal::withdrawMember()
{
    memberTable.erase(memberTable.begin() + loginMember);
}


/////////////////// MInlee////////////////////
/////////////////// MInlee////////////////////
/////////////////// MInlee////////////////////
/////////////////// MInlee////////////////////
/////////////////// MInlee////////////////////



string SearchProductUI::enterProductName()
{
    string productName;
    cin >> productName;
    return productName;
}
void SearchProductUI::displayProductDetails(int productIndex)
{
    if (productIndex == -1) cout << "���ǿ� �´� ��ǰ�� �����ϴ�." << endl;
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

///////////minlee ///////////
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
//////////minlee////////////


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
    // �޴� �Ľ��� ���� level ������ ���� ����
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;

    while (!is_program_exit)
    {
        // �Է����Ͽ��� �޴� ���� 2���� �б�
        cin >> menu_level_1 >> menu_level_2;

        // �޴� ���� �� �ش� ���� ����
        switch (menu_level_1)
        {
        case 1:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                cout << "1.1 ȸ������" << endl;
                cout << endl;

                SignUp* signUp = new SignUp();
                delete signUp;
                break;
            }
            case 2:
            {
                cout << "1.2. ȸ��Ż��" << endl;
                // ...
                cout << endl;
                WithDrawal* withDrawal = new WithDrawal();
                delete withDrawal;
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
                cout << "2.1. �α���" << endl;
                // ...
                cout << endl;

                LogIn* logIn = new LogIn();
                delete logIn;
                break;
            }
            case 2:
            {
                cout << "2.2. �α׾ƿ�" << endl;
                // ...
                cout << endl;

                LogOut* logOut = new LogOut();
                delete logOut;
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
                    cout << "3.1. �Ǹ� �Ƿ� ���" << endl;
                    // ...
                    cout << endl;
                    break;
                }
                case 2:
                {
                    cout << "3.2. ��� ��ǰ ��ȸ" << endl;
                    // ...
                    cout << endl;
                    break;
                }
                case 3:
                {
                    cout << "3.3. �Ǹ� �Ϸ� ��ǰ ��ȸ" << endl;
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
                    cout << "4.1. ��ǰ ���� �˻�" << endl;

                    SearchProduct* sp = new SearchProduct;
                    delete sp;

                    cout << endl;
                    break;
                }
                case 2:
                {
                    cout << "4.2. ��ǰ ����" << endl;
                    
                    PurchaseProduct* pp = new PurchaseProduct;
                    delete pp;

                    cout << endl;
                    break;
                }
                case 3:
                {
                    cout << "4.3. ��ǰ ���� ���� ��ȸ" << endl;
                    
                    CheckPurchaseHistory* cph = new CheckPurchaseHistory;
                    delete cph;

                    cout << endl;
                    break;
                }
                case 4:
                {
                    cout << "4.4. ��ǰ ���Ÿ����� ��" << endl;
                    
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
                    cout << "5.1. �Ǹ� ��ǰ ���" << endl;
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
                    cout << "6.1. ����" << endl;
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