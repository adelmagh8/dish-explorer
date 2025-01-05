#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to represent the country data
typedef struct {
    char *name;
} Country;

// Define a struct to represent the ingredient data
typedef struct {
    char *ingredient;
    char *amount;
} Ingredient;

// Define a struct to represent the category data
typedef struct {
    char *_id;
    char *name;
} Category;

// Define a struct to represent the dish data
typedef struct {
    char *_id;
    char *name;
    Country country;
    char *cookingTime;
    char *recipe;
    Ingredient *ingredients; // Array of ingredients
    int numIngredients;
    Category category;
} Dish;

// Function to filter dishes by category
Dish* filter_by_category(Dish* dishes, int num_dishes, const char* category_filter) {
    // Create a new array to store the filtered dishes
    Dish* filtered_dishes = (Dish*)malloc(num_dishes * sizeof(Dish));
    int filtered_count = 0;

    // Iterate through the dishes
    for (int i = 0; i < num_dishes; i++) {
        // Check if the category name matches the filter
        if (strcmp(dishes[i].category.name, category_filter) == 0) {
            // Copy the dish to the filtered array
            filtered_dishes[filtered_count] = dishes[i];
            filtered_count++;
        }
    }

    // Resize the filtered array to the actual number of filtered dishes
    filtered_dishes = (Dish*)realloc(filtered_dishes, filtered_count * sizeof(Dish));

    return filtered_dishes;
}

int main() {
    // Example usage:
    Dish dishes[] = {
        // ... (your dish data here) ...
    };
    int num_dishes = sizeof(dishes) / sizeof(dishes[0]);
    const char* category_filter = "test category 1"; 

    Dish* filtered_dishes = filter_by_category(dishes, num_dishes, category_filter);
    int num_filtered_dishes = sizeof(filtered_dishes) / sizeof(filtered_dishes[0]);

    // Print the filtered dishes
    for (int i = 0; i < num_filtered_dishes; i++) {
        printf("Dish Name: %s\n", filtered_dishes[i].name);
        // ... (print other relevant information) ...
    }

    // Free allocated memory
    free(filtered_dishes);

    return 0;
}