#include <string>
#include <iostream>
#include <cstring>
#include <curl/curl.h>

size_t OnResponseData(char* ptr, size_t size, size_t nmemb, std::string* stream)
{
	int realsize = size * nmemb;

	std::cout << ptr << std::endl;

	return realsize;
}

void SendJsonRequestMethodGet(const std::string& URL, const std::string& body)
{
	CURL* curl;
	curl = curl_easy_init();

	if (curl == NULL)
	{
		printf("Failed intialize curl instance");
		return;
	}

	CURLcode res;

	// Header 세팅
	curl_slist* header = NULL;
	header = curl_slist_append(header, "Content-Type: application/json");

	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnResponseData);

	res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	curl_slist_free_all(header);

	if (res != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	}
}

void SendJsonRequestMethodPost(const std::string& URL, const std::string& body)
{
	CURL* curl;
	curl = curl_easy_init();

	if(curl == NULL)
	{
		printf("Failed intialize curl instance");
		return;
	}

	CURLcode res;

	// Header 세팅
	curl_slist* header = NULL;
	header = curl_slist_append(header, "Content-Type: application/json");

	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

	curl_easy_setopt(curl, CURLOPT_POST, 1L);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnResponseData);

	res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	curl_slist_free_all(header);

	if (res != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	}
}

void main()
{
	const std::string AUTH_CHECK_URL = "http://127.0.0.1:11502/AuthCheck";
	std::string authCheckData = "{\"AuthID\": \"test01\", \"AuthToken\":\"DUWPQCFN5DQF4P\"}";
	SendJsonRequestMethodGet(AUTH_CHECK_URL, authCheckData);
	SendJsonRequestMethodPost(AUTH_CHECK_URL, authCheckData);

	const std::string INAPP_CHECK_URL = "http://127.0.0.1:11502/InAppCheck";
	std::string inAppCheckData = "{\"Receipt\": \"WkuOATWDQ909OET9cBjVEXEgI3KqTTbThNFe206bywlkSBiUD1hgrCltj3g1a84d\"}";
	SendJsonRequestMethodPost(INAPP_CHECK_URL, inAppCheckData);
}