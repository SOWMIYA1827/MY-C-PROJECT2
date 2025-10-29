#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure for product information
struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
    char category[30];
};

// Structure for customer information
struct Customer {
    int id;
    char name[50];
    char phone[15];
    float totalSpent;
};

// Global arrays to store data
struct Product products[100];
struct Customer customers[100];
int productCount = 0;
int customerCount = 0;

// Function prototypes
void displayMenu();
void addProduct();
void displayProducts();
void searchProduct();
void updateProduct();
void addCustomer();
void displayCustomers();
void processSale();
void generateReport();
void saveData();
void loadData();

int main() {
    int choice;
    
    // Load existing data
    loadData();
    
    printf("=== DEPARTMENT STORE MANAGEMENT SYSTEM ===\n");
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                addCustomer();
                break;
            case 6:
                displayCustomers();
                break;
            case 7:
                processSale();
                break;
            case 8:
                generateReport();
                break;
            case 9:
                saveData();
                printf("Data saved successfully!\n");
                break;
            case 10:
                saveData();
                printf("Thank you for using Department Store System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 10);
    
    return 0;
}

void displayMenu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Add New Product\n");
    printf("2. Display All Products\n");
    printf("3. Search Product\n");
    printf("4. Update Product Quantity\n");
    printf("5. Add New Customer\n");
    printf("6. Display All Customers\n");
    printf("7. Process Sale\n");
    printf("8. Generate Report\n");
    printf("9. Save Data\n");
    printf("10. Exit\n");
    printf("=================\n");
}

void addProduct() {
    if(productCount >= 100) {
        printf("Product storage full!\n");
        return;
    }
    
    printf("\n=== ADD NEW PRODUCT ===\n");
    products[productCount].id = productCount + 1;
    
    printf("Enter product name: ");
    scanf(" %[^\n]", products[productCount].name);
    
    printf("Enter price: ");
    scanf("%f", &products[productCount].price);
    
    printf("Enter quantity: ");
    scanf("%d", &products[productCount].quantity);
    
    printf("Enter category: ");
    scanf(" %[^\n]", products[productCount].category);
    
    productCount++;
    printf("Product added successfully!\n");
}

void displayProducts() {
    if(productCount == 0) {
        printf("No products available!\n");
        return;
    }
    
    printf("\n=== ALL PRODUCTS ===\n");
    printf("ID\tName\t\tPrice\tQuantity\tCategory\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < productCount; i++) {
        printf("%d\t%-15s\t$%.2f\t%d\t\t%-15s\n", 
               products[i].id, 
               products[i].name, 
               products[i].price, 
               products[i].quantity, 
               products[i].category);
    }
}

void searchProduct() {
    if(productCount == 0) {
        printf("No products available!\n");
        return;
    }
    
    int choice;
    printf("\n=== SEARCH PRODUCT ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    if(choice == 1) {
        int id;
        printf("Enter product ID: ");
        scanf("%d", &id);
        
        for(int i = 0; i < productCount; i++) {
            if(products[i].id == id) {
                printf("\nProduct Found:\n");
                printf("ID: %d\n", products[i].id);
                printf("Name: %s\n", products[i].name);
                printf("Price: $%.2f\n", products[i].price);
                printf("Quantity: %d\n", products[i].quantity);
                printf("Category: %s\n", products[i].category);
                return;
            }
        }
        printf("Product not found!\n");
    }
    else if(choice == 2) {
        char name[50];
        printf("Enter product name: ");
        scanf(" %[^\n]", name);
        
        for(int i = 0; i < productCount; i++) {
            if(strstr(products[i].name, name) != NULL) {
                printf("\nProduct Found:\n");
                printf("ID: %d\n", products[i].id);
                printf("Name: %s\n", products[i].name);
                printf("Price: $%.2f\n", products[i].price);
                printf("Quantity: %d\n", products[i].quantity);
                printf("Category: %s\n", products[i].category);
                return;
            }
        }
        printf("Product not found!\n");
    }
    else {
        printf("Invalid choice!\n");
    }
}

void updateProduct() {
    if(productCount == 0) {
        printf("No products available!\n");
        return;
    }
    
    int id, newQuantity;
    printf("\n=== UPDATE PRODUCT QUANTITY ===\n");
    printf("Enter product ID: ");
    scanf("%d", &id);
    
    for(int i = 0; i < productCount; i++) {
        if(products[i].id == id) {
            printf("Current quantity: %d\n", products[i].quantity);
            printf("Enter new quantity: ");
            scanf("%d", &newQuantity);
            products[i].quantity = newQuantity;
            printf("Quantity updated successfully!\n");
            return;
        }
    }
    printf("Product not found!\n");
}

void addCustomer() {
    if(customerCount >= 100) {
        printf("Customer storage full!\n");
        return;
    }
    
    printf("\n=== ADD NEW CUSTOMER ===\n");
    customers[customerCount].id = customerCount + 1;
    
    printf("Enter customer name: ");
    scanf(" %[^\n]", customers[customerCount].name);
    
    printf("Enter phone number: ");
    scanf(" %[^\n]", customers[customerCount].phone);
    
    customers[customerCount].totalSpent = 0.0;
    
    customerCount++;
    printf("Customer added successfully!\n");
}

void displayCustomers() {
    if(customerCount == 0) {
        printf("No customers available!\n");
        return;
    }
    
    printf("\n=== ALL CUSTOMERS ===\n");
    printf("ID\tName\t\tPhone\t\tTotal Spent\n");
    printf("----------------------------------------\n");
    
    for(int i = 0; i < customerCount; i++) {
        printf("%d\t%-15s\t%-12s\t$%.2f\n", 
               customers[i].id, 
               customers[i].name, 
               customers[i].phone, 
               customers[i].totalSpent);
    }
}

void processSale() {
    if(productCount == 0 || customerCount == 0) {
        printf("Need products and customers to process sale!\n");
        return;
    }
    
    int customerId, productId, quantity;
    float total = 0;
    char choice;
    
    printf("\n=== PROCESS SALE ===\n");
    displayCustomers();
    printf("Enter customer ID: ");
    scanf("%d", &customerId);
    
    if(customerId < 1 || customerId > customerCount) {
        printf("Invalid customer ID!\n");
        return;
    }
    
    printf("\nSale for customer: %s\n", customers[customerId-1].name);
    
    do {
        displayProducts();
        printf("Enter product ID: ");
        scanf("%d", &productId);
        
        if(productId < 1 || productId > productCount) {
            printf("Invalid product ID!\n");
            continue;
        }
        
        printf("Enter quantity: ");
        scanf("%d", &quantity);
        
        if(quantity > products[productId-1].quantity) {
            printf("Insufficient stock! Available: %d\n", products[productId-1].quantity);
            continue;
        }
        
        // Update product quantity
        products[productId-1].quantity -= quantity;
        
        // Calculate amount
        float amount = products[productId-1].price * quantity;
        total += amount;
        
        printf("Added: %s x %d = $%.2f\n", products[productId-1].name, quantity, amount);
        
        printf("Add more products? (y/n): ");
        scanf(" %c", &choice);
        
    } while(choice == 'y' || choice == 'Y');
    
    // Update customer total spent
    customers[customerId-1].totalSpent += total;
    
    printf("\n=== RECEIPT ===\n");
    printf("Customer: %s\n", customers[customerId-1].name);
    printf("Total Amount: $%.2f\n", total);
    printf("Thank you for shopping!\n");
}

void generateReport() {
    printf("\n=== STORE REPORT ===\n");
    printf("Total Products: %d\n", productCount);
    printf("Total Customers: %d\n", customerCount);
    
    // Calculate total inventory value
    float totalInventory = 0;
    for(int i = 0; i < productCount; i++) {
        totalInventory += products[i].price * products[i].quantity;
    }
    printf("Total Inventory Value: $%.2f\n", totalInventory);
    
    // Find low stock items
    printf("\nLow Stock Items (less than 10):\n");
    for(int i = 0; i < productCount; i++) {
        if(products[i].quantity < 10) {
            printf("- %s: %d left\n", products[i].name, products[i].quantity);
        }
    }
}

void saveData() {
    FILE *file = fopen("store_data.txt", "w");
    if(file == NULL) {
        printf("Error saving data!\n");
        return;
    }
    
    // Save products
    fprintf(file, "%d\n", productCount);
    for(int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %.2f %d %s\n", 
                products[i].id, 
                products[i].name, 
                products[i].price, 
                products[i].quantity, 
                products[i].category);
    }
    
    // Save customers
    fprintf(file, "%d\n", customerCount);
    for(int i = 0; i < customerCount; i++) {
        fprintf(file, "%d %s %s %.2f\n", 
                customers[i].id, 
                customers[i].name, 
                customers[i].phone, 
                customers[i].totalSpent);
    }
    
    fclose(file);
}

void loadData() {
    FILE *file = fopen("store_data.txt", "r");
    if(file == NULL) {
        printf("No previous data found. Starting fresh.\n");
        return;
    }
    
    // Load products
    fscanf(file, "%d", &productCount);
    for(int i = 0; i < productCount; i++) {
        fscanf(file, "%d %[^ ] %f %d %[^\n]", 
               &products[i].id, 
               products[i].name, 
               &products[i].price, 
               &products[i].quantity, 
               products[i].category);
    }
    
    // Load customers
    fscanf(file, "%d", &customerCount);
    for(int i = 0; i < customerCount; i++) {
        fscanf(file, "%d %[^ ] %[^ ] %f", 
               &customers[i].id, 
               customers[i].name, 
               customers[i].phone, 
               &customers[i].totalSpent);
    }
    
    fclose(file);
    printf("Previous data loaded successfully!\n");
}