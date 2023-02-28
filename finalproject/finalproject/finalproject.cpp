
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

struct Node{ // struct to create node
    int data; 
    struct Node* next; 
    struct Node* prev; 
};

class Inventory {

protected:
    int ProductID[15]{}, ItemQty[15]{}, ReorderPt[15]{};
    float ItemPrice[15] = { 295.00, 228.00, 55.00, 120.00, 252.00, 165.00, 220.00, 900.00, 192.00, 300.00, 750.00, 120.00, 540.00, 150.00, 435.00 }, totalcost{};
    string Description[15] = {"Notebook (60 Leaves)", "Pad Paper (80 Leaves)", "Clear Ruler 1 ft", "Mongol Pencil #2", "Elmer's Glue Small",
                               "Plastic Envelope Short", "Scissors Stainless (M)", "Illustration Board 1/4", "Permanent Marker Pilot",
                               "Crayola 8 Pcs", "Art Paper 500 Sheets", "Eraser", "HBW Ballpen", "Double Sided Tape", "A4 BondPaper (20 Sheets)"}, 
           SupplierName[15] = {"MAR Merchandise", "JB Merchandising Inc.", "MAR Merchandise", "EPLUS Stationary", "Manuel Stationary, Inc", 
                            "Bonus Merchandising, Inc", "Office Warehouse Store", "EPLUS Stationary", "EPLUS Stationary", "MAR Merchandise",
                            "Bonus Merchandising, Inc", "Bonus Merchandising, Inc", "JB Merchandising Inc.", "JB Merchandising Inc.", "MAR Merchandise"}, 
           Category[15] = {"Paper & Pads", "Paper & Pads", "Teaching & Art", "Writing & Correction", "Teaching & Art", "Filing Supplies", "General Supplies",
                        "Paper & Pads", "Writing & Correction", "Writing & Correction", "Paper & Pads", "Writing & Correction", "Writing & Correction",
                        "Packing Supplies", "Paper & Pads"}, 
           UOM[15] = {"10 pcs per Qty", "10 pcs per Qty", "12 pcs per Qty", "12 pcs per Qty", "12 pcs per Qty", "25 pcs per Qty", "12 pcs per Qty", 
                   "3 ream per Qty", "12 pcs per Qty", "12 pcs per Qty", "3 ream per Qty", "30 pcs per Qty", "98 pcs per Qty", "12 pcs per Qty",
                   "3 ream per Qty"};

    
public: 

    Inventory() {

        for (int i = 0; i < 15; i++) {

            ProductID[i] = i + 1;
            ItemQty[i] = 50;

            if (ItemPrice[i] < 200) {
                ReorderPt[i] = 5;
            }
            else if (ItemPrice[i] >= 200 && ItemPrice[i] <= 500) {
                ReorderPt[i] = 10;
            }
            else if (ItemPrice[i] > 500) {
                ReorderPt[i] = 15;
            }

        }
        ifstream readFile("MasterInventory.txt"); 
        if (readFile.is_open()) {
            readFile.close();
        }
        else {
            ofstream writeFile("MasterInventory.txt", ios::trunc);
            writeFile << left << setw(20) << "Product ID" << setw(20) << "Description" << setw(25) << "\tSupplier Name" << setw(24) << "Item Price" << setw(25) << "\tItem Qty" << setw(35) << "Reorder Point (ROP)" << setw(24) << "\tCategory" << setw(30) << "Unit of Measurement (UOM)" << endl << endl;

            for (int i = 0; i < 15; i++) {
                writeFile << "P-" << setw(20) << ProductID[i] << setw(25) << Description[i] << setw(30) << SupplierName[i] << "P" << setw(30) << ItemPrice[i] << setw(30) << ItemQty[i] << setw(30) << ReorderPt[i] << setw(30) << Category[i] << setw(30) << UOM[i] << endl;
            }

            ofstream writeFile2("OutofStockLog.txt", ios::trunc);
            writeFile2 << "No out of stock product.";

            ofstream writeFile3("QuantityInventory.txt", ios::trunc);
            for (int i = 0; i < 15; i++) {
                writeFile3 << "50" << endl;
            }

            ofstream writeFile4("LatestOrderSummary.txt", ios::trunc);
            writeFile4 << "No Latest Order Summary.";

        }

        ofstream writeFile5("SalesTransactionLog.txt", ios::trunc);
        writeFile5 << "No Sales.";

        ofstream writeFile6("PurchasesTransactionLog.txt", ios::trunc);
        writeFile6 << "No Purchase Data.";
    

    }
    ~Inventory() {}

};

class CompanyFunctions : public Inventory {

private:

    int inttemp{}, quantity{}, orderinput{}, orderamount[15]{}, temp{}, value{};;
    struct Node* head = NULL; 
    string stringtemp, stringdata{};

    int IntValidation(int inttemp) //validation for number of processes input
    {
        //data type validation
        while ((cin.fail()) || (inttemp < 1 || inttemp > 6  ))
        {
            cout << "\nInvalid Input. Try Again. " << endl;
            system("pause");
            system("cls");
            cin.clear();
            cin.ignore(123, '\n');
            cout << "ABC Trading Company\n";
            cout << "Lipa City, Batangas\n";
            cout << "------------------------------------------------------------------------------------------------------------------------";
            cout << "\nFunctions: \n[1] Perform Wholesale Transaction \n[2] View Inventory Stocks \n[3] Perform Stock Purchases \n[4] View Sales Transaction Data \n[5] View Purchases Transaction Data \n[6] Exit " << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "\nOption: ";
            cin >> inttemp; //reentry of input, process repeats if the value given to cin fails the condition
        }
        return inttemp;
    }

    int IntValidation2(int inttemp) { //validation for order quantity input

        while ((cin.fail()) || (inttemp < 0 || inttemp > 15))
        {
            system("CLS");
            cout << "Product Number input is invalid. Please try again. " << endl;
            system("pause");
            system("CLS");
            printitemmenu(); // prints the item menu for saletransaction() method
            cout << "\nProduct No (Enter the Number): ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> inttemp;
        }
        return inttemp;
    }

    int IntValidation3(int inttemp) { //validation for order quantity input
       
        while ((cin.fail()) || temp - inttemp < 0)
        {
            system("CLS");
            cout << "Quantity input is invalid. Please try again. " << endl;
            system("pause");
            system("CLS");
            printitemmenu(); // prints the item menu for saletransaction() method
            cout << "\nProduct No (Enter the Number): " << orderinput;
            cout << "\nQuantity: ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> inttemp;
        }
        return inttemp;
    }

    void printitemmenu() { // prints the item menu for saletransaction() method

        cout << "ABC Trading Company\n";
        cout << "Lipa City, Batangas\n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Please type your order. \n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(15) << "ProductID" << setw(25) << "Description" << setw(25) << "Supplier Name" << setw(16) << "Item Price" << setw(28) << "Stock Quantity" << setw(25) << "UOM" << endl;
        for (int i = 0; i < 15; i++) {
            cout << "[P-" << ProductID[i] << "] \t" << left << setw(30) << Description[i] << setw(30) << SupplierName[i] << "P" << setw(18) << ItemPrice[i] << setw(15) << ItemQty[i] << " (" << UOM[i] << ")" << endl;

        }

        cout << "\n[0]: Finalize Order\n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void updatemasterinventory() { // updates the master inventory file with new stock/quantity values
        ofstream writeFile("MasterInventory.txt", ios::trunc);
        writeFile << left << setw(20) << "Product ID" << setw(20) << "Description" << setw(25) << "\tSupplier Name" << setw(24) << "Item Price" << setw(25) << "\tItem Qty" << setw(35) << "Reorder Point (ROP)" << setw(24) << "\tCategory" << setw(30) << "Unit of Measurement (UOM)" << endl << endl;

        for (int i = 0; i < 15; i++) {
            writeFile << "P-" << setw(20) << ProductID[i] << setw(25) << Description[i] << setw(30) << SupplierName[i] << "P" << setw(30) << ItemPrice[i] << setw(30) << ItemQty[i] << setw(30) << ReorderPt[i] << setw(30) << Category[i] << setw(30) << UOM[i] << endl;
        }
    }

    void writequantityinventory() { // updates the quantity inventory file with new quantity values

        ofstream writeFile("QuantityInventory.txt", ios::trunc);
        for (int i = 0; i < 15; i++) {
            writeFile << ItemQty[i] << endl;
        }
    }

    void updatequantityinventory() { // updates program’s product quantities from text file data
        int i = 0;
        fstream readFile("QuantityInventory.txt", ios_base::in);

        while (readFile >> value && i < 15) {
            ItemQty[i] = value;
            i++;
        }

        readFile.close();
    }

    void insert(int newdata) { // inserts into a linked list the list of productIDs which products are considered out of stock
        struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
        if (newnode)
        {
            newnode->data = newdata;
            newnode->prev = NULL;
            newnode->next = head;
            if (head != NULL)
                head->prev = newnode;
            head = newnode;
        }
    }

    void takestringdata() { // takes text data from LatestOrderSummary.txt, combines it with the new sale order data, and inserts it into the SalesTransactionLog.txt
        int line_no = 0;
        string sLine = "";
        ifstream read("LatestOrderSummary.txt");

        while (line_no != 2 && getline(read, sLine)) {
            ++line_no;
        }

        while (getline(read, sLine) && !read.eof() ) {
            stringtemp = stringtemp + sLine + "\n";
        }

        stringdata = stringtemp;

        read.close();

        fstream generateFile;
        generateFile.open("SalesTransactionLog.txt");

        generateFile << "Sales Transaction Log: " << endl;
        generateFile << "------------------------------------------------------------------------------------------------------------------------";
        
        generateFile << stringdata << endl;

        generateFile.close();

    }

    void display() { // displays out of stock products based on the linked list contents
        struct Node* ptr; 
        ptr = head; 
        cout << "Products needed to be restocked:" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        if (ptr == NULL) {
            cout << "All items have enough stocks." << endl;
        }
        else if (ptr != NULL) {
            cout << "ProductID\tDescription" << endl << endl;
        }
        while (ptr != NULL) {
            cout << left << "P-" << setw(13) << ptr->data << setw(30) << Description[ptr->data - 1] << "\n"; 
            ptr = ptr->next; 
        } 
    }

    bool search(Node* head, int x) // provides a bool value depending if the current node is equal to the product ID value, which filters which productID to be inputted into the linked list to avoid repetition
    {
        Node* current = head; // Initialize current  
            while (current != NULL)
            {
                if (current->data == x)
                    return true;
                current = current->next;
            }
        return false;
    }

    bool isEmpty(Node* head) // checks whether the linked list is empty or not
    {
        if (!head)
            return true;
        return false;
    }

    void refillstock(Node** head_ref) // refills out of stock products in the program and fills up PurchasesTransactionLog.txt file with purchase data
    {

        fstream generateFile;
        generateFile.open("PurchasesTransactionLog.txt");
        generateFile << "Purchases Transaction Log: " << endl;
        generateFile << "------------------------------------------------------------------------------------------------------------------------" << endl;
        /* deref head_ref to get the real head */
        Node* current = *head_ref;
        Node* next;

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "# of Item Stocks Refilled: " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(15) << "ProductID" << setw(25) << "Description" << setw(25) << "Item Quantity" << endl << endl;
        generateFile << left << setw(15) << "ProductID" << setw(25) << "Description" << setw(25) << "Item Quantity" << endl << endl;
        while (current != NULL)
        {
            next = current->next;
            value = current->data;
            cout << left << "P-" << setw(13) << ProductID[value - 1] << setw(30) << Description[value - 1] << setw(25) << 50 - ItemQty[value - 1] << endl; 
            generateFile << left << "P-" << setw(13) << ProductID[value - 1] << setw(30) << Description[value - 1] << setw(25) << 50 - ItemQty[value - 1] << endl;
            ItemQty[value - 1] = 50;
            free(current);
            current = next;
        }
        /* deref head_ref to affect the real head back
            in the caller. */
        *head_ref = NULL;
        generateFile << "\n------------------------------------------------------------------------------------------------------------------------";
        cout << "\n------------------------------------------------------------------------------------------------------------------------";
        generateFile.close();
    }

    void menuinitializations() { // method that calls product quantity update from text file, reviews and inserts out of stock products in the linked list, and fills up the OutofStockLog.txt file with out of stock data
    
        bool condition{};

        ifstream readFile("QuantityInventory.txt");
        if (readFile.is_open()) {
            updatequantityinventory(); // updates program’s product quantities from text file data
        }
        readFile.close();

        ofstream writeFile("OutofStockLog.txt");

        for (int i = 0; i < 15; i++) {

            if (i == 0) {
                writeFile << left << setw(15) << "ProductID" << setw(25) << "Description" << setw(25) << "Item Quantity" << endl << endl;
            }

            if (ItemQty[i] <= ReorderPt[i]) {

                // provides a bool value depending if the current node is equal to the product ID value, which filters which productID to be inputted into the linked list to avoid repetition
                condition = search(head, ProductID[i]); // 
                if (condition == false) {
                    insert(ProductID[i]); // inserts into a linked list the list of productIDs which products are considered out of stock
                }

                writeFile << left << "P-" << setw(13) << i + 1 << setw(30) << Description[i] << setw(25) << ItemQty[i] << endl;

            }
        }

        writeFile.close();

    }

public:

    void menuselection() { //presents the initial menu option of the program

        menuinitializations(); // method that calls product quantity update from text file, reviews and inserts out of stock products in the linked list, and fills up the OutofStockLog.txt file with out of stock data

        cout << "ABC Trading Company\n";
        cout << "Lipa City, Batangas\n";
        cout << "------------------------------------------------------------------------------------------------------------------------";
        cout << "\nFunctions: \n[1] Perform Wholesale Transaction \n[2] View Inventory Stocks \n[3] Perform Stock Purchases \n[4] View Sales Transaction Data \n[5] View Purchases Transaction Data \n[6] Exit " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\nOption: ";

        cin >> inttemp;
        inttemp = IntValidation(inttemp);

        system("cls");

        if (inttemp == 6) {
            cout << "ABC Trading Company\n";
            cout << "Lipa City, Batangas\n";
            cout << "\nProgram exit." << endl;
            exit(0); //exit program
        }
            
    }

    int getmenuoption() { // menu option accessor
        return inttemp;
    }

    void saletransaction() { // method to perform wholesale transaction

        bool order_loop = true;

        while (order_loop) {

            cin.clear();
            cin.ignore(123, '\n');
            printitemmenu();

            cout << "\nProduct No (Enter the Number): ";
            cin >> orderinput;
            inttemp = orderinput;
            orderinput = IntValidation2(inttemp);
            temp = ItemQty[orderinput - 1];

            if (orderinput == 0) {
                order_loop = false;
            }
            else if ((orderinput > 0 && orderinput < 16) && temp > 0) {
                cout << "Quantity: ";
                cin >> quantity;
                inttemp = quantity;
                quantity = IntValidation3(inttemp);
                orderamount[orderinput - 1 ] += quantity;
                ItemQty[orderinput - 1] -= quantity;
            }
            else if ((orderinput > 0 && orderinput < 16) && temp <= 0) {
                cout << "\nWrong input or there are no stock for this product. Provide a different input, or exit the process with [0]." << endl;
                system("pause");
            }
            else {
                system("CLS");
                cout << "Order Input is invalid. Please try again. " << endl;
                system("pause");
                system("CLS");
            }

            system("cls");

        }

    }

    void printsummary() { // method that prints wholesale transaction summary and fills up data for LatestOrderSummary.txt file

        system("CLS");
        fstream generateFile;
        float summarycost{};
        time_t today = time(0);
        char* t = ctime(&today);

        updatemasterinventory(); // updates the master inventory file with new stock/quantity values
        writequantityinventory(); // updates program’s product quantities from text file data

        generateFile.open("LatestOrderSummary.txt");
        cout << "ABC Trading Company\n";
        cout << "Lipa City, Batangas\n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\nSummary of Orders: " << endl << "Date: " << t << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        generateFile << "\nSummary of Orders: " << endl << "\n\nDate: " << t << endl;
        cout << left << setw(15) << "ProductID" << setw(25) << "Description" << setw(25) << "Supplier Name" << setw(16) << "Item Price" << setw(28) << "Order Amount" << setw(25) << "UOM" << endl;    
        generateFile << left << setw(15) << "ProductID" << setw(25) << "Description" << setw(25) << "Supplier Name" << setw(16) << "Item Price" << setw(28) << "Order Amount" << setw(25) << "UOM" << endl << endl;

        for (int i = 0; i < 15; i++) {

                if (orderamount[i] > 0) {
                    cout << "[P-" << ProductID[i] << "] \t" << left << setw(30) << Description[i] << setw(30) << SupplierName[i] << "P" << setw(18) << ItemPrice[i] << setw(15) << orderamount[i] << " (" << UOM[i] << ")" << endl;   
                    generateFile << "[P-" << ProductID[i] << "] \t" << left << setw(30) << Description[i] << setw(30) << SupplierName[i] << "P" << setw(18) << ItemPrice[i] << setw(15) << orderamount[i] << " (" << UOM[i] << ")" << endl;
                    summarycost += (ItemPrice[i] * orderamount[i]);
                    orderamount[i] = 0;
                }

        }
        cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Total: Php " << summarycost << endl;
        generateFile << endl << "Total: Php " << summarycost << endl;
        totalcost += summarycost;   

        takestringdata(); // takes text data from LatestOrderSummary.txt, combines it with the new sale order data, and inserts it into the SalesTransactionLog.txt
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        system("pause");
        system("CLS");

    }

    void viewmasterinventory() { // method that prints out the master inventory and the products that needs to be restocked
        time_t today = time(0);
        char* t = ctime(&today);

        cout << "ABC Trading Company\n";
        cout << "Lipa City, Batangas\n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\nSummary of Orders: " << endl << "Date: " << t << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(15) << "ProductID" << setw(25) << "Description" << setw(25) << "Supplier Name" << setw(16) << "Item Price" << setw(18) << "Item Quantity" << setw(25) << "Reorder Point" << endl;

        for (int i = 0; i < 15; i++) {

            cout << "[P-" << ProductID[i] << "] \t" << left << setw(30) << Description[i] << setw(30) << SupplierName[i] << "P" << setw(18) << ItemPrice[i] << setw(15) << ItemQty[i] << " (" << ReorderPt[i] << ")" << endl;

        }
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        display(); // displays out of stock products based on the linked list contents
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        system("pause");
        system("cls");
    }
    
    void viewsalestransaction() { // method that prints out sales transaction log data from SalesTransactionLog.txt file
        
        string line;

        ifstream read("SalesTransactionLog.txt");

        cout << "ABC Trading Company\n";
        cout << "Lipa City, Batangas\n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        while (getline(read, line) && !read.eof()) {
            cout << line << endl;
        }


        if (line == "No Sales.") {
            cout << "No Sales Transaction Log." << endl;
        }

        read.close();
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        cout << endl;

        system("pause");
        system("cls");
    }

    void performstockpurchases() { //method that replenishes program’s product stock data, updating the master and quantity inventory in the process

        bool condition{};

        condition = isEmpty(head); //checks whether the linked list is empty or not

        cout << "ABC Trading Company\n";
        cout << "Lipa City, Batangas\n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        if (condition == true) {
            cout << "No stocks needed for replenishing." << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        }
        else if (condition == false) {
            display(); // displays out of stock products based on the linked list contents
            refillstock(&head); // refills out of stock products in the program and fills up PurchasesTransactionLog.txt file with purchase data
            updatemasterinventory(); // updates the master inventory file with new stock/quantity values
            writequantityinventory(); // updates the quantity inventory file with new quantity values
            ofstream writeFile5("OutofStockLog.txt", ios::trunc);
            writeFile5 << "No out of stock product.";
        }

        cout << endl;

        system("pause");
        system("cls");
    }

    void viewpurchasestransaction() { // method that prints out purchase transaction log data from PurchasesTransactionLog.txt file

        string line;

        ifstream read("PurchasesTransactionLog.txt");

        cout << "ABC Trading Company\n";
        cout << "Lipa City, Batangas\n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        while (getline(read, line) && !read.eof()) {
            cout << line << endl;
        }

        if (line == "No Purchase Data.") {
            cout << "No Purchase Transaction Log." << endl;
        }

        read.close();
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;

        system("pause");
        system("cls");

    }

};

int main()
{
    
    Inventory Items;
    CompanyFunctions CompanyProcess;
    bool programloop = true;

    srand(time(NULL));

    while (programloop) {
        CompanyProcess.menuselection();

        switch (CompanyProcess.getmenuoption()) {
        case 1:
            CompanyProcess.saletransaction();
            CompanyProcess.printsummary();
            break;
        case 2:
            CompanyProcess.viewmasterinventory();
            break;
        case 3:
            CompanyProcess.performstockpurchases();
            break;
        case 4:
            CompanyProcess.viewsalestransaction();
            break;
        case 5:
            CompanyProcess.viewpurchasestransaction();
            break;
        }

    }
}
