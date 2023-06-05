#include <string>
#include <iostream>
#include <cstring>
#include <curl/curl.h>

using namespace std;

size_t callBackFunk(char* ptr, size_t size, size_t nmemb, string* stream)
{
	int realsize = size * nmemb;
	stream->append(ptr, realsize);

	return realsize;
}

void main()
{
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();

	std::string URL = "http://127.0.0.1:11502/AuthCheck";
	std::string body = "{\"AuthID\": \"TEST1\", \"AuthToken\":\"Test\"}";

	// Header ¼¼ÆÃ
	curl_slist* header = NULL;
	header = curl_slist_append(header, "Content-Type: application/json");

	string chunk;

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunk);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		curl_slist_free_all(header);

		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		std::cout << "------------Result" << std::endl;
		std::cout << chunk << std::endl;
	}
}