#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UTILS_H  
#define UTILS_H  

void print_utility_message();  


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





// Function to filter dishes by country
Dish* filter_by_country(Dish* dishes, int num_dishes, const char* country_filter) {
    // Create a new array to store the filtered dishes
    Dish* filtered_dishes = (Dish*)malloc(num_dishes * sizeof(Dish));
    int filtered_count = 0;

    // Iterate through the dishes
    for (int i = 0; i < num_dishes; i++) {
        // Check if the country name matches the filter
        if (strcmp(dishes[i].country.name, country_filter) == 0) {
            // Copy the dish to the filtered array
            filtered_dishes[filtered_count] = dishes[i];
            filtered_count++;
        }
    }

    // Resize the filtered array to the actual number of filtered dishes
    filtered_dishes = (Dish*)realloc(filtered_dishes, filtered_count * sizeof(Dish));

    return filtered_dishes;
}
#endif // UTILS_H
