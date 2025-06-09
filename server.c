#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdbool.h>

#define API_KEY "ec44f6d713bc454d894135917250205"

#define PORT 8080
#define RECV_BUFFER_SIZE 512

const char *htmlBuffer =
    "<!DOCTYPE html>\n"
    "<html>\n"
    "\n"
    "<head>\n"
    "<style>\n"
    "body {\n"
    "background-color: aliceblue;\n"
    "display: flex;\n"
    "align-items: center;\n"
    "justify-content: center;\n"
    "flex-direction: column;\n"
    "padding: 20px 20px;\n"
    "}\n"
    "\n"
    "h1 {\n"
    "font-size: 300%;\n"
    "}\n"
    "\n"
    "h2 {\n"
    "font-size: 200%;\n"
    "}\n"
    "\n"
    "select {\n"
    "width: 200px;\n"
    "font-size: 120%;\n"
    "}\n"
    "\n"
    "button {\n"
    "margin-top: 20px;\n"
    "font-size: 120%;\n"
    "}\n"
    "\n"
    "#weatherResult {\n"
    "display: none;\n"
    "margin-top: 30px;\n"
    "padding: 20px;\n"
    "background-color: #fff8dc;\n"
    "border: 1px solid #ddd;\n"
    "border-radius: 10px;\n"
    "width: fit-content;\n"
    "max-width: 90%;\n"
    "box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);\n"
    "font-size: 120%;\n"
    "flex-direction: column;\n"
    "align-items: center;\n"
    "}\n"
    "\n"
    "#weatherTable td:first-child {\n"
    "font-weight: bold;\n"
    "width: 150px;\n"
    "padding-right: 10px;\n"
    "}\n"
    "\n"
    "#weatherIcon {\n"
    "height: 128px;\n"
    "width: 128px;\n"
    "margin-left: 30px;\n"
    "align-self: center;\n"
    "}\n"
    "\n"
    "#weatherTable td {\n"
    "padding: 5px 10px;\n"
    "vertical-align: top;\n"
    "}\n"
    "\n"
    "#weatherTable td:nth-child(2) {\n"
    "max-width: 300px;\n"
    "word-wrap: break-word;\n"
    "white-space: normal;\n"
    "}\n"
    "</style>\n"
    "</head>\n"
    "\n"
    "<body>\n"
    "<h1>Weather Services</h1>\n"
    "<br />\n"
    "<h2>Please select country:</h2>\n"
    "<br />\n"
    "<select class=\"form-select\" autocomplete=\"country\" id=\"country\" name=\"country\">\n"
    "<option value=\"\">select country</option>\n"
    "<option value=\"FR\">France</option>\n"
    "<option value=\"DE\">Germany</option>\n"
    "<option value=\"IT\">Italy</option>\n"
    "<option value=\"NO\">Norway</option>\n"
    "<option value=\"PL\">Poland</option>\n"
    "</select>\n"
    "\n"
    "<h2>Please select city:</h2>\n"
    "<br />\n"
    "<select class=\"form-select\" autocomplete=\"city\" id=\"city\" name=\"city\" disabled>\n"
    "<option value=\"\">select city</option>\n"
    "</select>\n"
    "\n"
    "<br><br>\n"
    "<button type=\"button\" id=\"button\">Accept</button>\n"
    "\n"
    "<div id=\"weatherResult\" style=\"display: none;\"></div>\n"
    "\n"
    "<script>\n"
    "const countrySelect = document.getElementById(\"country\");\n"
    "const citySelect = document.getElementById(\"city\");\n"
    "const button = document.getElementById(\"button\");\n"
    "const resultContainer = document.getElementById(\"weatherResult\");\n"
    "\n"
    "const cityOptions = {\n"
    "FR: [\"Paris\", \"Lyon\", \"Marseille\", \"Toulouse\", \"Nice\"],\n"
    "DE: [\"Berlin\", \"Munich\", \"Hamburg\", \"Cologne\", \"Frankfurt\"],\n"
    "IT: [\"Rome\", \"Milan\", \"Naples\", \"Turin\", \"Florence\"],\n"
    "NO: [\"Oslo\", \"Bergen\", \"Trondheim\", \"Stavanger\", \"Tromsø\"],\n"
    "PL: [\"Warsaw\", \"Cracow\", \"Lodz\", \"Wroclaw\", \"Lublin\"]\n"
    "};\n"
    "\n"
    "countrySelect.addEventListener(\"change\", function () {\n"
    "const selectedCountry = this.value;\n"
    "\n"
    "// Reset city select\n"
    "citySelect.innerHTML = \"<option value=\\\"\\\">select city</option>\";\n"
    "\n"
    "if (selectedCountry && cityOptions[selectedCountry]) {\n"
    "cityOptions[selectedCountry].forEach(city => {\n"
    "const option = document.createElement(\"option\");\n"
    "option.value = city;\n"
    "option.textContent = city;\n"
    "citySelect.appendChild(option);\n"
    "});\n"
    "citySelect.disabled = false;\n"
    "} else {\n"
    "citySelect.disabled = true;\n"
    "}\n"
    "});\n"
    "\n"
    "button.addEventListener(\"click\", function () {\n"
    "const country = countrySelect.value;\n"
    "const city = citySelect.value;\n"
    "const apiKey = '" API_KEY "';\n"
    "\n"
    "if (country && city) {\n"
    "const url = `http://api.weatherapi.com/v1/current.json?q=${city}&lang=pl&key=${apiKey}`;\n"
    "fetch(url)\n"
    ".then(response => {\n"
    "if (!response.ok) {\n"
    "throw new Error(\"Network response was not ok\");\n"
    "}\n"
    "return response.json();\n"
    "})\n"
    ".then(data => {\n"
    "const location = data.location;\n"
    "const weather = data.current;\n"
    "\n"
    "const resultContainer = document.getElementById(\"weatherResult\");\n"
    "resultContainer.style.display = \"flex\";\n"
    "\n"
    "resultContainer.innerHTML = `\n"
    "<div style=\"display: flex; justify-content: space-between; align-items: center;\">\n"
    "<table id=\"weatherTable\">\n"
    "<tr><td>Country:</td><td>${location.country}</td></tr>\n"
    "<tr><td>City:</td><td>${location.name}</td></tr>\n"
    "<tr><td>Weather:</td><td>${weather.condition.text}</td></tr>\n"
    "<tr><td>Temperature:</td><td>${weather.temp_c} °C</td></tr>\n"
    "<tr><td>Wind:</td><td>${weather.wind_kph} km/h</td></tr>\n"
    "<tr><td>Humidity:</td><td>${weather.humidity} %</td></tr>\n"
    "</table>\n"
    "${weather.condition.icon ? `<img id=\"weatherIcon\" src=\"https:${weather.condition.icon}\" alt=\"weather icon\">` : \"\"}\n"
    "</div>\n"
    "`;\n"
    "})\n"
    "\n"
    ".catch(error => {\n"
    "console.error(\"Fetch error:\", error);\n"
    "resultContainer.innerHTML = \"<p style='color: red;'>Failed to fetch weather data. Try again later.</p>\";\n"
    "});\n"
    "} else {\n"
    "console.log(\"Please select both country and a city\");\n"
    "resultContainer.innerHTML = \"<p style='color: orange;'>Please select both country and city first.</p>\";\n"
    "}\n"
    "});\n"
    "</script>\n"
    "</body>\n"
    "\n"
    "</html>\n";

void handle_request(int client_socket)
{
    char recvBuffer[RECV_BUFFER_SIZE];
    read(client_socket, recvBuffer, sizeof(recvBuffer) - 1);
    printf("Request:\n%s\n", recvBuffer);

    int htmlBufferSize = strlen(htmlBuffer);

    const char *headerTemplate =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "\r\n";

    // Getting size of headerTemplate where %d is htmlBufferSize
    int headerSize = snprintf(NULL, 0, headerTemplate, htmlBufferSize);

    int totalResponseSize = headerSize + htmlBufferSize + 1;
    char *response = malloc(totalResponseSize);
    if (!response)
    {
        fprintf(stderr, "Failed to allocate memory for response\n");
        close(client_socket);
        return;
    }

    snprintf(response, totalResponseSize,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %d\r\n"
             "\r\n"
             "%s",
             htmlBufferSize, htmlBuffer);

    write(client_socket, response, strlen(response));
    free(response);
    close(client_socket);
}

void log_info()
{
    time_t now = time(0);
    if (now == ((time_t)-1))
    {
        perror("time failed");
        return;
    }

    char time_str[70];
    struct tm *curr_time = localtime(&now);
    if (curr_time == NULL)
    {
        perror("localtime failed");
        return;
    }

    if (strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", curr_time) == 0)
    {
        fprintf(stderr, "strftime failed\n");
        return;
    }

    // using fflush to unbuffer stdout, since it's not automatically done after a newline character in Scratch
    printf("App started on %s\n", time_str);
    fflush(stdout);
    printf("Author: AuthorName AuthorSurname\n");
    fflush(stdout);
    printf("TCP Port: %d\n", PORT);
    fflush(stdout);
}

int main()
{
    log_info();

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    printf("Server listening on port %d\n", PORT);
    fflush(stdout);

    while (1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        handle_request(client_socket);
    }

    close(server_socket);

    return 0;
}