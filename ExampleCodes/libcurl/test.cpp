#include <curl.h>
#include <string>
#include <iostream>
#include <cstring>

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

	std::string strTargetURL = "http://127.0.0.1:11502/AuthCheck";
	std::string strResourceJSON = "{\"AuthID\": \"TEST1\", \"AuthToken\":\"Test\"}";

	curl_slist* headerlist = NULL;
	headerlist = curl_slist_append(headerlist, "Content-Type: application/json");

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	string chunk;

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, strTargetURL.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strResourceJSON.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strResourceJSON.length());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunk);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		curl_slist_free_all(headerlist);

		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		std::cout << "------------Result" << std::endl;
		std::cout << chunk << std::endl;
	}
}

