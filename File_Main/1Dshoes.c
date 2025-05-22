#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_PRODUCTS 100
#define MAX_TRANSACTIONS 100
#define MAX_REVIEWS 100
#define MAX_STRING_LENGTH 50

// Struktur data untuk User
typedef struct {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    float balance;
    int is_seller;
    int active;
} User;

// Struktur data untuk Product
typedef struct {
    char brand[MAX_STRING_LENGTH];
    int size;
    float price;
    char color[MAX_STRING_LENGTH];
    int stock;
    char seller[MAX_STRING_LENGTH];
    int active;
} Product;


// Struktur data untuk Transaction
typedef struct {
    char customer[MAX_STRING_LENGTH];
    char product_brand[MAX_STRING_LENGTH];
    int product_size;
    char product_color[MAX_STRING_LENGTH];
    float amount;
    time_t timestamp;
} Transaction;

// Struktur data untuk Review
typedef struct {
    char customer[MAX_STRING_LENGTH];
    char product_brand[MAX_STRING_LENGTH];
    char comment[MAX_STRING_LENGTH * 2];
    int rating;
    time_t timestamp;
} Review;

// Variabel global
User users[MAX_USERS];
Product products[MAX_PRODUCTS];
Transaction transactions[MAX_TRANSACTIONS];
Review reviews[MAX_REVIEWS];
int user_count = 0;
int product_count = 0;
int transaction_count = 0;
int review_count = 0;
User *current_user = NULL;

// Fungsi utilitas
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void print_header(const char *title) {
    printf("\n=== %s ===\n", title);
}

void press_enter_to_continue() {
    printf("\nPress Enter to continue...");
    clear_input_buffer();
    getchar();
}

// Fungsi manajemen data
void load_data() {
    // Implementasi loading data dari file (disederhanakan)
    // Dalam implementasi nyata, ini akan membaca dari file
    printf("Loading data...\n");
    
    // Contoh data dummy untuk testing
    if (user_count == 0) {
        strcpy(users[0].username, "seller1");
        strcpy(users[0].password, "pass1");
        users[0].balance = 0;
        users[0].is_seller = 1;
        users[0].active = 1;
        
        strcpy(users[1].username, "customer1");
        strcpy(users[1].password, "pass1");
        users[1].balance = 1000;
        users[1].is_seller = 0;
        users[1].active = 1;
        
        user_count = 2;
    }
    
    if (product_count == 0) {
        strcpy(products[0].brand, "Nike");
        products[0].size = 42;
        products[0].price = 500;
        strcpy(products[0].color, "Black");
        products[0].stock = 10;
        strcpy(products[0].seller, "seller1");
        products[0].active = 1;
        
        product_count = 1;
    }
}

void save_data() {
    // Implementasi penyimpanan data ke file (disederhanakan)
    printf("Saving data...\n");
}

// Fungsi autentikasi
int register_user(int is_seller) {
    if (user_count >= MAX_USERS) {
        printf("Maximum user limit reached.\n");
        return 0;
    }
    
    User new_user;
    new_user.is_seller = is_seller;
    new_user.balance = 0;
    new_user.active = 1;
    
    printf("Enter username: ");
    scanf("%49s", new_user.username);
    clear_input_buffer();
    
    // Cek username sudah ada
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, new_user.username) == 0) {
            printf("Username already exists.\n");
            return 0;
        }
    }
    
    printf("Enter password: ");
    scanf("%49s", new_user.password);
    clear_input_buffer();
    
    users[user_count++] = new_user;
    printf("Registration successful!\n");
    
    save_data();
    return 1;
}

int login_user() {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    
    printf("Enter username: ");
    scanf("%49s", username);
    clear_input_buffer();
    
    printf("Enter password: ");
    scanf("%49s", password);
    clear_input_buffer();
    
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && 
            strcmp(users[i].password, password) == 0 &&
            users[i].active) {
            current_user = &users[i];
            printf("Login successful! Welcome, %s.\n", username);
            return 1;
        }
    }
    
    printf("Invalid username or password.\n");
    return 0;
}

void logout() {
    current_user = NULL;
    printf("Logged out successfully.\n");
}

void change_password() {
    if (!current_user) {
        printf("You must be logged in to change password.\n");
        return;
    }
    
    char old_password[MAX_STRING_LENGTH];
    char new_password[MAX_STRING_LENGTH];
    
    printf("Enter old password: ");
    scanf("%49s", old_password);
    clear_input_buffer();
    
    if (strcmp(current_user->password, old_password) != 0) {
        printf("Incorrect old password.\n");
        return;
    }
    
    printf("Enter new password: ");
    scanf("%49s", new_password);
    clear_input_buffer();
    
    strcpy(current_user->password, new_password);
    printf("Password changed successfully.\n");
    
    save_data();
}

// Fungsi customer
void view_catalog() {
    print_header("PRODUCT CATALOG");
    
    if (product_count == 0) {
        printf("No products available.\n");
        return;
    }
    
    printf("%-20s %-10s %-10s %-15s %-10s %-15s\n", 
           "Brand", "Size", "Price", "Color", "Stock", "Seller");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < product_count; i++) {
        if (products[i].active) {
            printf("%-20s %-10d %-10.2f %-15s %-10d %-15s\n", 
                   products[i].brand, products[i].size, products[i].price, 
                   products[i].color, products[i].stock, products[i].seller);
        }
    }
}

void top_up_balance() {
    if (!current_user || current_user->is_seller) {
        printf("Only customers can top up balance.\n");
        return;
    }
    
    float amount;
    printf("Enter amount to top up: ");
    scanf("%f", &amount);
    clear_input_buffer();
    
    if (amount <= 0) {
        printf("Amount must be positive.\n");
        return;
    }
    
    current_user->balance += amount;
    printf("Top up successful. New balance: %.2f\n", current_user->balance);
    
    save_data();
}

void purchase_shoe() {
    if (!current_user || current_user->is_seller) {
        printf("Only customers can purchase shoes.\n");
        return;
    }
    
    view_catalog();
    
    char brand[MAX_STRING_LENGTH];
    int size;
    char color[MAX_STRING_LENGTH];
    
    printf("\nEnter brand of shoe to purchase: ");
    scanf("%49s", brand);
    clear_input_buffer();
    
    printf("Enter size: ");
    scanf("%d", &size);
    clear_input_buffer();
    
    printf("Enter color: ");
    scanf("%49s", color);
    clear_input_buffer();
    
    // Cari produk
    int product_index = -1;
    for (int i = 0; i < product_count; i++) {
        if (products[i].active && 
            strcasecmp(products[i].brand, brand) == 0 &&
            products[i].size == size &&
            strcasecmp(products[i].color, color) == 0) {
            product_index = i;
            break;
        }
    }
    
    if (product_index == -1) {
        printf("Product not found.\n");
        return;
    }
    
    if (products[product_index].stock <= 0) {
        printf("Product out of stock.\n");
        return;
    }
    
    if (current_user->balance < products[product_index].price) {
        printf("Insufficient balance. Please top up first.\n");
        return;
    }
    
    // Proses pembelian
    current_user->balance -= products[product_index].price;
    
    // Tambahkan ke saldo penjual
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, products[product_index].seller) == 0) {
            users[i].balance += products[product_index].price;
            break;
        }
    }
    
    products[product_index].stock--;
    
    // Catat transaksi
    if (transaction_count < MAX_TRANSACTIONS) {
        strcpy(transactions[transaction_count].customer, current_user->username);
        strcpy(transactions[transaction_count].product_brand, products[product_index].brand);
        transactions[transaction_count].product_size = products[product_index].size;
        strcpy(transactions[transaction_count].product_color, products[product_index].color);
        transactions[transaction_count].amount = products[product_index].price;
        transactions[transaction_count].timestamp = time(NULL);
        transaction_count++;
    }
    
    printf("Purchase successful! Remaining balance: %.2f\n", current_user->balance);
    
    save_data();
}

void view_purchase_history() {
    if (!current_user || current_user->is_seller) {
        printf("Only customers can view purchase history.\n");
        return;
    }
    
    print_header("PURCHASE HISTORY");
    
    int found = 0;
    for (int i = 0; i < transaction_count; i++) {
        if (strcmp(transactions[i].customer, current_user->username) == 0) {
            found = 1;
            char time_str[20];
            strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&transactions[i].timestamp));
            
            printf("Date: %s\n", time_str);
            printf("Product: %s (Size: %d, Color: %s)\n", 
                   transactions[i].product_brand, transactions[i].product_size, transactions[i].product_color);
            printf("Amount: %.2f\n\n", transactions[i].amount);
        }
    }
    
    if (!found) {
        printf("No purchase history found.\n");
    }
}

void add_review() {
    if (!current_user || current_user->is_seller) {
        printf("Only customers can add reviews.\n");
        return;
    }
    
    // Cek apakah customer pernah membeli produk
    int has_purchases = 0;
    for (int i = 0; i < transaction_count; i++) {
        if (strcmp(transactions[i].customer, current_user->username) == 0) {
            has_purchases = 1;
            break;
        }
    }
    
    if (!has_purchases) {
        printf("You haven't made any purchases yet.\n");
        return;
    }
    
    view_purchase_history();
    
    char brand[MAX_STRING_LENGTH];
    int size;
    char color[MAX_STRING_LENGTH];
    
    printf("\nEnter brand of shoe to review: ");
    scanf("%49s", brand);
    clear_input_buffer();
    
    printf("Enter size: ");
    scanf("%d", &size);
    clear_input_buffer();
    
    printf("Enter color: ");
    scanf("%49s", color);
    clear_input_buffer();
    
    // Cek apakah customer pernah membeli produk ini
    int has_purchased = 0;
    for (int i = 0; i < transaction_count; i++) {
        if (strcmp(transactions[i].customer, current_user->username) == 0 &&
            strcasecmp(transactions[i].product_brand, brand) == 0 &&
            transactions[i].product_size == size &&
            strcasecmp(transactions[i].product_color, color) == 0) {
            has_purchased = 1;
            break;
        }
    }
    
    if (!has_purchased) {
        printf("You haven't purchased this product.\n");
        return;
    }
    
    // Cek apakah sudah ada review untuk produk ini
    for (int i = 0; i < review_count; i++) {
        if (strcmp(reviews[i].customer, current_user->username) == 0 &&
            strcasecmp(reviews[i].product_brand, brand) == 0) {
            printf("You've already reviewed this product.\n");
            return;
        }
    }
    
    if (review_count >= MAX_REVIEWS) {
        printf("Maximum reviews limit reached.\n");
        return;
    }
    
    Review new_review;
    strcpy(new_review.customer, current_user->username);
    strcpy(new_review.product_brand, brand);
    new_review.timestamp = time(NULL);
    
    printf("Enter rating (1-5): ");
    scanf("%d", &new_review.rating);
    clear_input_buffer();
    
    if (new_review.rating < 1 || new_review.rating > 5) {
        printf("Rating must be between 1 and 5.\n");
        return;
    }
    
    printf("Enter your review comment: ");
    fgets(new_review.comment, MAX_STRING_LENGTH * 2, stdin);
    new_review.comment[strcspn(new_review.comment, "\n")] = 0; // Remove newline
    
    reviews[review_count++] = new_review;
    printf("Review added successfully!\n");
    
    save_data();
}

// Fungsi seller
void add_product() {
    if (!current_user || !current_user->is_seller) {
        printf("Only sellers can add products.\n");
        return;
    }
    
    if (product_count >= MAX_PRODUCTS) {
        printf("Maximum product limit reached.\n");
        return;
    }
    
    Product new_product;
    strcpy(new_product.seller, current_user->username);
    new_product.active = 1;
    
    printf("Enter brand: ");
    scanf("%49s", new_product.brand);
    clear_input_buffer();
    
    printf("Enter size: ");
    scanf("%d", &new_product.size);
    clear_input_buffer();
    
    printf("Enter price: ");
    scanf("%f", &new_product.price);
    clear_input_buffer();
    
    printf("Enter color: ");
    scanf("%49s", new_product.color);
    clear_input_buffer();
    
    printf("Enter stock quantity: ");
    scanf("%d", &new_product.stock);
    clear_input_buffer();
    
    products[product_count++] = new_product;
    printf("Product added successfully!\n");
    
    save_data();
}

void view_sales_balance() {
    if (!current_user || !current_user->is_seller) {
        printf("Only sellers can view sales balance.\n");
        return;
    }
    
    print_header("SALES BALANCE");
    printf("Your current balance: %.2f\n", current_user->balance);
    
    // Tampilkan riwayat penjualan
    printf("\nSales History:\n");
    int found = 0;
    for (int i = 0; i < transaction_count; i++) {
        for (int j = 0; j < product_count; j++) {
            if (strcmp(products[j].seller, current_user->username) == 0 &&
                strcmp(transactions[i].product_brand, products[j].brand) == 0 &&
                transactions[i].product_size == products[j].size &&
                strcmp(transactions[i].product_color, products[j].color) == 0) {
                found = 1;
                char time_str[20];
                strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&transactions[i].timestamp));
                
                printf("Date: %s\n", time_str);
                printf("Product: %s (Size: %d, Color: %s)\n", 
                       transactions[i].product_brand, transactions[i].product_size, transactions[i].product_color);
                printf("Amount: %.2f\n", transactions[i].amount);
                printf("Sold to: %s\n\n", transactions[i].customer);
            }
        }
    }
    
    if (!found) {
        printf("No sales history found.\n");
    }
}

void manage_products() {
    if (!current_user || !current_user->is_seller) {
        printf("Only sellers can manage products.\n");
        return;
    }
    
    print_header("MANAGE PRODUCTS");
    
    printf("Your Products:\n");
    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (products[i].active && strcmp(products[i].seller, current_user->username) == 0) {
            found = 1;
            printf("%d. %s (Size: %d, Color: %s) - Price: %.2f - Stock: %d\n", 
                   i+1, products[i].brand, products[i].size, 
                   products[i].color, products[i].price, products[i].stock);
        }
    }
    
    if (!found) {
        printf("You have no products listed.\n");
        return;
    }
    
    printf("\n1. Update product\n2. Remove product\n3. Back\n");
    printf("Choose option: ");
    int option;
    scanf("%d", &option);
    clear_input_buffer();
    
    if (option == 1) {
        printf("Enter product number to update: ");
        int product_num;
        scanf("%d", &product_num);
        clear_input_buffer();
        
        if (product_num < 1 || product_num > product_count) {
            printf("Invalid product number.\n");
            return;
        }
        
        // Cari produk yang dimiliki seller ini
        int actual_index = -1;
        int count = 0;
        for (int i = 0; i < product_count; i++) {
            if (products[i].active && strcmp(products[i].seller, current_user->username) == 0) {
                count++;
                if (count == product_num) {
                    actual_index = i;
                    break;
                }
            }
        }
        
        if (actual_index == -1) {
            printf("Invalid product selection.\n");
            return;
        }
        
        printf("Enter new price (current: %.2f): ", products[actual_index].price);
        scanf("%f", &products[actual_index].price);
        clear_input_buffer();
        
        printf("Enter new stock (current: %d): ", products[actual_index].stock);
        scanf("%d", &products[actual_index].stock);
        clear_input_buffer();
        
        printf("Product updated successfully!\n");
        save_data();
    } else if (option == 2) {
        printf("Enter product number to remove: ");
        int product_num;
        scanf("%d", &product_num);
        clear_input_buffer();
        
        if (product_num < 1 || product_num > product_count) {
            printf("Invalid product number.\n");
            return;
        }
        
        // Cari produk yang dimiliki seller ini
        int actual_index = -1;
        int count = 0;
        for (int i = 0; i < product_count; i++) {
            if (products[i].active && strcmp(products[i].seller, current_user->username) == 0) {
                count++;
                if (count == product_num) {
                    actual_index = i;
                    break;
                }
            }
        }
        
        if (actual_index == -1) {
            printf("Invalid product selection.\n");
            return;
        }
        
        products[actual_index].active = 0;
        printf("Product removed successfully!\n");
        save_data();
    }
}

void view_customer_accounts() {
    if (!current_user || !current_user->is_seller) {
        printf("Only sellers can view customer accounts.\n");
        return;
    }
    
    print_header("CUSTOMER ACCOUNTS");
    
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (!users[i].is_seller && users[i].active) {
            found = 1;
            printf("Username: %s\n", users[i].username);
            printf("Balance: %.2f\n\n", users[i].balance);
        }
    }
    
    if (!found) {
        printf("No customer accounts found.\n");
    }
}

void delete_customer_account() {
    if (!current_user || !current_user->is_seller) {
        printf("Only sellers can delete customer accounts.\n");
        return;
    }
    
    view_customer_accounts();
    
    char username[MAX_STRING_LENGTH];
    printf("\nEnter username to delete (or 'cancel' to abort): ");
    scanf("%49s", username);
    clear_input_buffer();
    
    if (strcasecmp(username, "cancel") == 0) {
        return;
    }
    
    for (int i = 0; i < user_count; i++) {
        if (!users[i].is_seller && strcmp(users[i].username, username) == 0 && users[i].active) {
            users[i].active = 0;
            printf("Customer account deleted successfully.\n");
            save_data();
            return;
        }
    }
    
    printf("Customer account not found or invalid.\n");
}

void view_product_reviews() {
    if (!current_user || !current_user->is_seller) {
        printf("Only sellers can view product reviews.\n");
        return;
    }
    
    print_header("PRODUCT REVIEWS");
    
    // Tampilkan produk yang dijual oleh seller ini
    printf("Your Products:\n");
    int found_products = 0;
    for (int i = 0; i < product_count; i++) {
        if (products[i].active && strcmp(products[i].seller, current_user->username) == 0) {
            found_products = 1;
            printf("- %s (Size: %d, Color: %s)\n", 
                   products[i].brand, products[i].size, products[i].color);
        }
    }
    
    if (!found_products) {
        printf("You have no products listed.\n");
        return;
    }
    
    char brand[MAX_STRING_LENGTH];
    printf("\nEnter product brand to view reviews: ");
    scanf("%49s", brand);
    clear_input_buffer();
    
    // Cek apakah produk milik seller ini
    int is_own_product = 0;
    for (int i = 0; i < product_count; i++) {
        if (products[i].active && 
            strcmp(products[i].seller, current_user->username) == 0 &&
            strcasecmp(products[i].brand, brand) == 0) {
            is_own_product = 1;
            break;
        }
    }
    
    if (!is_own_product) {
        printf("You don't own this product or it doesn't exist.\n");
        return;
    }
    
    // Tampilkan review untuk produk ini
    int found_reviews = 0;
    for (int i = 0; i < review_count; i++) {
        if (strcasecmp(reviews[i].product_brand, brand) == 0) {
            found_reviews = 1;
            char time_str[20];
            strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&reviews[i].timestamp));
            
            printf("\nReview by: %s\n", reviews[i].customer);
            printf("Date: %s\n", time_str);
            printf("Rating: %d/5\n", reviews[i].rating);
            printf("Comment: %s\n", reviews[i].comment);
        }
    }
    
    if (!found_reviews) {
        printf("No reviews found for this product.\n");
    }
}

// Menu utama
void customer_menu() {
    int choice;
    do {
        print_header("CUSTOMER MENU");
        printf("1. View Shoe Catalog\n");
        printf("2. Top Up Balance\n");
        printf("3. Purchase Shoes\n");
        printf("4. View Purchase History\n");
        printf("5. Add Product Review\n");
        printf("6. Change Password\n");
        printf("7. Logout\n");
        printf("Choose option: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1: view_catalog(); break;
            case 2: top_up_balance(); break;
            case 3: purchase_shoe(); break;
            case 4: view_purchase_history(); break;
            case 5: add_review(); break;
            case 6: change_password(); break;
            case 7: logout(); break;
            default: printf("Invalid option.\n");
        }
        
        if (choice != 7) {
            press_enter_to_continue();
        }
    } while (choice != 7);
}

void seller_menu() {
    int choice;
    do {
        print_header("SELLER MENU");
        printf("1. Add Product\n");
        printf("2. View Sales Balance\n");
        printf("3. Manage Products\n");
        printf("4. View Customer Accounts\n");
        printf("5. Delete Customer Account\n");
        printf("6. View Product Reviews\n");
        printf("7. Change Password\n");
        printf("8. Logout\n");
        printf("Choose option: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1: add_product(); break;
            case 2: view_sales_balance(); break;
            case 3: manage_products(); break;
            case 4: view_customer_accounts(); break;
            case 5: delete_customer_account(); break;
            case 6: view_product_reviews(); break;
            case 7: change_password(); break;
            case 8: logout(); break;
            default: printf("Invalid option.\n");
        }
        
        if (choice != 8) {
            press_enter_to_continue();
        }
    } while (choice != 8);
}

void main_menu() {
    int choice;
    do {
        print_header("MAIN MENU");
        printf("1. Register as Customer\n");
        printf("2. Register as Seller\n");
        printf("3. Login\n");
        printf("4. Exit\n");
        printf("Choose option: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1: 
                register_user(0); 
                press_enter_to_continue();
                break;
            case 2: 
                register_user(1); 
                press_enter_to_continue();
                break;
            case 3: 
                if (login_user()) {
                    if (current_user->is_seller) {
                        seller_menu();
                    } else {
                        customer_menu();
                    }
                } else {
                    press_enter_to_continue();
                }
                break;
            case 4: 
                printf("Exiting...\n"); 
                break;
            default: 
                printf("Invalid option.\n");
                press_enter_to_continue();
        }
    } while (choice != 4);
}

int main() {
    load_data();
    main_menu();
    save_data();
    return 0;
}