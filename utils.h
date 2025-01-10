#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h" // Include cJSON library for JSON parsing

#ifndef UTILS_H  
#define UTILS_H

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
Dish* search_by_name(Dish* dishes, int dishes_length, const char* search_value) {
    // Create a new array to store the filtered dishes
    Dish* filtered_dishes = (Dish*)malloc(dishes_length * sizeof(Dish));
    int filtered_count = 0;

    // Iterate through the dishes
    for (int i = 0; i < dishes_length; i++) {
        // Check if the category name matches the filter
        if (strcmp(dishes[i].name, search_value) == 0) {
            // Copy the dish to the filtered array
            filtered_dishes[filtered_count] = dishes[i];
            filtered_count++;
        }
    }

    // Resize the filtered array to the actual number of filtered dishes
    filtered_dishes = (Dish*)realloc(filtered_dishes, filtered_count * sizeof(Dish));

    return filtered_dishes;
}


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


typedef struct {
  char *readBuffer;
  size_t size;
} MemoryBuffer;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t realsize = size * nmemb;
  MemoryBuffer *mem = (MemoryBuffer *)userdata;

  char *ptr1 = (char *)realloc(mem->readBuffer, mem->size + realsize + 1);
  if(!ptr1) { 
    /* out of memory! */ 
    printf("not enough memory\n"); 
    return 0; 
  }

  mem->readBuffer = ptr1;
  memcpy(&(mem->readBuffer[mem->size]), ptr, realsize);
  mem->size += realsize;
  mem->readBuffer[mem->size] = 0; 

  return realsize;
}

// Function to make an API request and parse the JSON response
int make_api_request(const char* url, const char* path, cJSON **root) {
  CURL *curl;
  CURLcode res;
  MemoryBuffer chunk;
  chunk.size = 0;
  chunk.readBuffer = malloc(1); 
  chunk.readBuffer[0] = 0;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);

    if (path != NULL) {
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, path);
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      free(chunk.readBuffer);
      curl_easy_cleanup(curl);
      return 1;
    }

    *root = cJSON_Parse(chunk.readBuffer);
    if (*root == NULL) {
      fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
      free(chunk.readBuffer);
      curl_easy_cleanup(curl);
      return 1;
    }

    free(chunk.readBuffer); 
    curl_easy_cleanup(curl);
    return 0;
  }

  fprintf(stderr, "curl_easy_init() failed\n");
  return 1;
}


#endif // UTILS_H