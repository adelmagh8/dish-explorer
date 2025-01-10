#include <stdio.h>
#include <stdlib.h>
#include "./cJSON.h"
#include "./utils.h"

int main() {
  cJSON *root;

  int result = make_api_request("https://introduction-to-software-api.onrender.com", "/dishes", &root);

  if (result == 0) {
    // Access JSON data using cJSON API
    // cJSON *userId = cJSON_GetObjectItemCaseSensitive(root, "userId");
    // if (userId && userId->type == cJSON_Number) {
    //   printf("userId: %d\n", userId->valueint);
    // }

    // Access other fields similarly

    cJSON_Delete(root); // Free the JSON object
  }


	return 0;
}
