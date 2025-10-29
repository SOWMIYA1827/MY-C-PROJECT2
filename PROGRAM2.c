#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50
#define MAX_CART_ITEMS 50

// Structure for product
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int stock;
} Product;

// Structure for cart item
typedef struct {
    int productId;
    char productName[MAX_NAME_LENGTH];
    float price;
    int quantity;
    float total;
} CartItem;

// Global arrays
Product products[MAX_PRODUCTS];
CartItem cart[MAX_CART_ITEMS];
int productCount = 0;
int cartCount = 0;

// Function prototypes
void initializeProducts();
void displayMenu();
void displayProducts();
void addToCart();
void viewCart();
void updateCart();
void removeFromCart();
void checkout();
int findProductById(int id);
int findCartItemById(int id);
void saveProductsToFile();
void loadProductsFromFile();
void adminMenu();
void addProduct();
void updateProduct();
void deleteProduct();

int main() {
    int choice;
    
    // Load products from file at startup
    loadProductsFromFile();
    
    // If no products loaded, initialize with sample data
    if (productCount == 0) {
        initializeProducts();
    }
    
    printf("=== Welcome to Shopping Cart System ===\n");
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                displayProducts();
                break;
            case 2:
                addToCart();
                break;
            case 3:
                viewCart();
                break;
            case 4:
                updateCart();
                break;
            case 5:
                removeFromCart();
                break;
            case 6:
                checkout();
                break;
            case 7:
                adminMenu();
                break;
            case 8:
                printf("Thank you for shopping with us!\n");
                saveProductsToFile();
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 8);
    
    return 0;
}

void initializeProducts() {
    // Sample products
    products[0] = (Product){1, "Laptop", 999.99, 10};
    products[1] = (Product){2, "Smartphone", 599.99, 25};
    products[2] = (Product){3, "Headphones", 99.99, 30};
    products[3] = (Product){4, "Mouse", 29.99, 50};
    products[4] = (Product){5, "Keyboard", 49.99, 40};
    productCount = 5;
}

void displayMenu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Display Products\n");
    printf("2. Add to Cart\n");
    printf("3. View Cart\n");
    printf("4. Update Cart Item\n");
    printf("5. Remove from Cart\n");
    printf("6. Checkout\n");
    printf("7. Admin Menu\n");
    printf("8. Exit\n");
}

void displayProducts() {
    printf("\n=== AVAILABLE PRODUCTS ===\n");
    printf("ID\tName\t\tPrice\t\tStock\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < productCount; i++) {
        printf("%d\t%-15s\t$%.2f\t\t%d\n", 
               products[i].id, 
               products[i].name, 
               products[i].price, 
               products[i].stock);
    }
}

void addToCart() {
    int productId, quantity;
    
    displayProducts();
    printf("\nEnter Product ID to add to cart: ");
    scanf("%d", &productId);
    
    int productIndex = findProductById(productId);
    if(productIndex == -1) {
        printf("Product not found!\n");
        return;
    }
    
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    
    if(quantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }
    
    if(products[productIndex].stock < quantity) {
        printf("Insufficient stock! Available: %d\n", products[productIndex].stock);
        return;
    }
    
    // Check if product already in cart
    int cartIndex = findCartItemById(productId);
    if(cartIndex != -1) {
        // Update existing cart item
        if(products[productIndex].stock >= cart[cartIndex].quantity + quantity) {
            cart[cartIndex].quantity += quantity;
            cart[cartIndex].total = cart[cartIndex].quantity * cart[cartIndex].price;
            printf("Product quantity updated in cart!\n");
        } else {
            printf("Cannot add more than available stock!\n");
        }
    } else {
        // Add new item to cart
        if(cartCount < MAX_CART_ITEMS) {
            cart[cartCount].productId = productId;
            strcpy(cart[cartCount].productName, products[productIndex].name);
            cart[cartCount].price = products[productIndex].price;
            cart[cartCount].quantity = quantity;
            cart[cartCount].total = quantity * products[productIndex].price;
            cartCount++;
            printf("Product added to cart successfully!\n");
        } else {
            printf("Cart is full!\n");
        }
    }
}

void viewCart() {
    if(cartCount == 0) {
        printf("Your cart is empty!\n");
        return;
    }
    
    float grandTotal = 0;
    printf("\n=== YOUR SHOPPING CART ===\n");
    printf("ID\tName\t\tPrice\t\tQty\tTotal\n");
    printf("--------------------------------------------------------\n");
    
    for(int i = 0; i < cartCount; i++) {
        printf("%d\t%-15s\t$%.2f\t\t%d\t$%.2f\n", 
               cart[i].productId,
               cart[i].productName,
               cart[i].price,
               cart[i].quantity,
               cart[i].total);
        grandTotal += cart[i].total;
    }
    
    printf("--------------------------------------------------------\n");
    printf("Grand Total: $%.2f\n", grandTotal);
}

void updateCart() {
    if(cartCount == 0) {
        printf("Your cart is empty!\n");
        return;
    }
    
    int productId, newQuantity;
    viewCart();
    
    printf("Enter Product ID to update: ");
    scanf("%d", &productId);
    
    int cartIndex = findCartItemById(productId);
    if(cartIndex == -1) {
        printf("Product not found in cart!\n");
        return;
    }
    
    printf("Enter new quantity: ");
    scanf("%d", &newQuantity);
    
    if(newQuantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }
    
    int productIndex = findProductById(productId);
    if(products[productIndex].stock < newQuantity) {
        printf("Insufficient stock! Available: %d\n", products[productIndex].stock);
        return;
    }
    
    cart[cartIndex].quantity = newQuantity;
    cart[cartIndex].total = newQuantity * cart[cartIndex].price;
    printf("Cart updated successfully!\n");
}

void removeFromCart() {
    if(cartCount == 0) {
        printf("Your cart is empty!\n");
        return;
    }
    
    int productId;
    viewCart();
    
    printf("Enter Product ID to remove: ");
    scanf("%d", &productId);
    
    int cartIndex = findCartItemById(productId);
    if(cartIndex == -1) {
        printf("Product not found in cart!\n");
        return;
    }
    
    // Shift items to remove the selected one
    for(int i = cartIndex; i < cartCount - 1; i++) {
        cart[i] = cart[i + 1];
    }
    cartCount--;
    printf("Product removed from cart!\n");
}

void checkout() {
    if(cartCount == 0) {
        printf("Your cart is empty!\n");
        return;
    }
    
    viewCart();
    
    char confirm;
    printf("\nConfirm purchase? (y/n): ");
    scanf(" %c", &confirm);
    
    if(tolower(confirm) == 'y') {
        // Update stock and clear cart
        for(int i = 0; i < cartCount; i++) {
            int productIndex = findProductById(cart[i].productId);
            if(productIndex != -1) {
                products[productIndex].stock -= cart[i].quantity;
            }
        }
        
        printf("Purchase completed successfully! Thank you!\n");
        cartCount = 0; // Clear cart
        saveProductsToFile(); // Save updated products
    } else {
        printf("Purchase cancelled.\n");
    }
}

int findProductById(int id) {
    for(int i = 0; i < productCount; i++) {
        if(products[i].id == id) {
            return i;
        }
    }
    return -1;
}

int findCartItemById(int id) {
    for(int i = 0; i < cartCount; i++) {
        if(cart[i].productId == id) {
            return i;
        }
    }
    return -1;
}

void adminMenu() {
    int choice;
    char password[20] = "admin123"; // Simple password protection
    char input[20];
    
    printf("Enter admin password: ");
    scanf("%s", input);
    
    if(strcmp(input, password) != 0) {
        printf("Invalid password!\n");
        return;
    }
    
    do {
        printf("\n=== ADMIN MENU ===\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Display Products\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                displayProducts();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 5);
}

void addProduct() {
    if(productCount >= MAX_PRODUCTS) {
        printf("Product limit reached!\n");
        return;
    }
    
    Product newProduct;
    printf("Enter Product ID: ");
    scanf("%d", &newProduct.id);
    
    // Check if ID already exists
    if(findProductById(newProduct.id) != -1) {
        printf("Product ID already exists!\n");
        return;
    }
    
    printf("Enter Product Name: ");
    scanf("%s", newProduct.name);
    printf("Enter Price: ");
    scanf("%f", &newProduct.price);
    printf("Enter Stock: ");
    scanf("%d", &newProduct.stock);
    
    products[productCount] = newProduct;
    productCount++;
    printf("Product added successfully!\n");
    saveProductsToFile();
}

void updateProduct() {
    int productId;
    displayProducts();
    
    printf("Enter Product ID to update: ");
    scanf("%d", &productId);
    
    int index = findProductById(productId);
    if(index == -1) {
        printf("Product not found!\n");
        return;
    }
    
    printf("Enter new Name (current: %s): ", products[index].name);
    scanf("%s", products[index].name);
    printf("Enter new Price (current: %.2f): ", products[index].price);
    scanf("%f", &products[index].price);
    printf("Enter new Stock (current: %d): ", products[index].stock);
    scanf("%d", &products[index].stock);
    
    printf("Product updated successfully!\n");
    saveProductsToFile();
}

void deleteProduct() {
    int productId;
    displayProducts();
    
    printf("Enter Product ID to delete: ");
    scanf("%d", &productId);
    
    int index = findProductById(productId);
    if(index == -1) {
        printf("Product not found!\n");
        return;
    }
    
    // Shift products to remove the selected one
    for(int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }
    productCount--;
    printf("Product deleted successfully!\n");
    saveProductsToFile();
}

void saveProductsToFile() {
    FILE *file = fopen("products.dat", "wb");
    if(file == NULL) {
        printf("Error saving products to file!\n");
        return;
    }
    
    fwrite(&productCount, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), productCount, file);
    fclose(file);
}

void loadProductsFromFile() {
    FILE *file = fopen("products.dat", "rb");
    if(file == NULL) {
        printf("No existing product data found.\n");
        return;
    }
    
    fread(&productCount, sizeof(int), 1, file);
    fread(products, sizeof(Product), productCount, file);
    fclose(file);
    printf("Products loaded successfully!\n");
}