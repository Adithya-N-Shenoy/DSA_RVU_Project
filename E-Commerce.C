#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 10
#define HASH_MAP_SIZE 10

typedef struct {
    int productId;
    char productName[50];
    float price;
} Product;

typedef struct {
    int productId;
    int quantity;
    float price;
} CartItem;

Product products[MAX_PRODUCTS] = {
    {1, "Laptop", 50000.0},
    {2, "Smartphone", 20000.0},
    {3, "Headphones", 2000.0},
    {4, "Smartwatch", 3000.0},
    {5, "Camera", 15000.0}
};

CartItem cart[HASH_MAP_SIZE];

int hash(int productId) {
    return productId % HASH_MAP_SIZE;
}

void showAvailableProducts() {
    printf("\nAvailable Products:\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].productId != 0)
            printf("ID: %d | Name: %s | Price: %.2f\n",
                   products[i].productId, products[i].productName, products[i].price);
    }
}

void addItemToCart(int productId, int quantity) {
    int index = hash(productId);
    int found = 0;

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].productId == productId) {
            cart[index].productId = productId;
            cart[index].quantity += quantity;
            cart[index].price = products[i].price;
            found = 1;
            printf("Added %d x %s to cart.\n", quantity, products[i].productName);
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
}

void removeItemFromCart(int productId) {
    int index = hash(productId);
    if (cart[index].productId == productId && cart[index].quantity > 0) {
        printf("Removed %d x product ID %d from cart.\n", cart[index].quantity, productId);
        cart[index].quantity = 0;
        cart[index].price = 0.0;
        cart[index].productId = 0;
    } else {
        printf("Product not found in cart.\n");
    }
}

void viewCart() {
    float total = 0.0;
    int itemFound = 0;

    printf("\nCart Items:\n");
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        if (cart[i].quantity > 0) {
            for (int j = 0; j < MAX_PRODUCTS; j++) {
                if (products[j].productId == cart[i].productId) {
                    printf("Product: %s | Quantity: %d | Price: %.2f | Total: %.2f\n",
                           products[j].productName, cart[i].quantity,
                           cart[i].price, cart[i].quantity * cart[i].price);
                    total += cart[i].quantity * cart[i].price;
                    itemFound = 1;
                }
            }
        }
    }

    if (!itemFound) {
        printf("Your cart is empty.\n");
    } else {
        printf("Total Amount: %.2f\n", total);
    }
}

void checkout() {
    float total = 0.0;
    int itemFound = 0;

    printf("\nCheckout Summary:\n");
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        if (cart[i].quantity > 0) {
            for (int j = 0; j < MAX_PRODUCTS; j++) {
                if (products[j].productId == cart[i].productId) {
                    printf("Product: %s | Quantity: %d | Price: %.2f | Total: %.2f\n",
                           products[j].productName, cart[i].quantity,
                           cart[i].price, cart[i].quantity * cart[i].price);
                    total += cart[i].quantity * cart[i].price;
                    itemFound = 1;
                }
            }
        }
    }

    if (!itemFound) {
        printf("Your cart is empty. Add items before checking out.\n");
    } else {
        printf("Total Amount to Pay: %.2f\n", total);
        printf("Proceeding to payment...\n");
    }
}

int main() {
    int choice, productId, quantity;

    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        cart[i].quantity = 0;
        cart[i].price = 0.0;
        cart[i].productId = 0;
    }

    printf("E-Commerce Cart and Checkout System\n");

    do {
        printf("\nMenu:\n");
        printf("1. Add Item to Cart\n");
        printf("2. Remove Item from Cart\n");
        printf("3. View Cart\n");
        printf("4. Checkout\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showAvailableProducts();
                printf("Enter product ID: ");
                scanf("%d", &productId);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                addItemToCart(productId, quantity);
                break;
            case 2:
                printf("Enter product ID to remove: ");
                scanf("%d", &productId);
                removeItemFromCart(productId);
                break;
            case 3:
                viewCart();
                break;
            case 4:
                checkout();
                break;
            case 5:
                printf("Exiting E-Commerce System.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
