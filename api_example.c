#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Winsock kütüphanesini bağlar

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    const char *host = "jsonplaceholder.typicode.com";
    const char *path = "/todos/1";
    char request[1024], response[4096];
    int received;

    // Winsock başlat
    printf("Winsock başlatılıyor...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Başlatma hatası. Hata kodu: %d\n", WSAGetLastError());
        return 1;
    }

    // Soket oluştur
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Soket oluşturma başarısız. Hata kodu: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Soket oluşturuldu.\n");

    // Sunucu adresini çöz (IP olarak kullanmak için)
    struct hostent *he = gethostbyname(host);
    if (he == NULL) {
        printf("Host adı çözülemedi.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Sunucu adresini ayarla
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    memcpy(&server.sin_addr.s_addr, he->h_addr, he->h_length);

    // Bağlan
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Bağlantı başarısız. Hata kodu: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Bağlantı başarılı.\n");

    // HTTP GET isteği oluştur ve gönder
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n\r\n",
             path, host);

    if (send(sock, request, strlen(request), 0) < 0) {
        printf("İstek gönderme başarısız.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("İstek gönderildi.\n");

    // Yanıtı oku
    while ((received = recv(sock, response, sizeof(response) - 1, 0)) > 0) {
        response[received] = '\0'; // Null-terminate string
        printf("%s", response);
    }

    if (received < 0) {
        printf("Yanıt alma hatası.\n");
    }

    // Kaynakları temizle
    closesocket(sock);
    WSACleanup();
    printf("\nBağlantı kapatıldı.\n");

    return 0;
}
