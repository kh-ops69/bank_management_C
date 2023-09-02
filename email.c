#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>

/*
 * For an SMTP example using the multi interface please see smtp-multi.c.
 */

/* The libcurl options want plain addresses, the viewable headers in the mail
 * can very well get a full name as well.
 */
#define FROM_ADDR    "testingout123451@outlook.com"
#define TO_ADDR      "appbrewery132@yahoo.com"

//#define FROM_MAIL "outlook tests" FROM_ADDR
//#define TO_MAIL   "app brewery" TO_ADDR

static const char *payload_text =
        "Date: Mon, 28 Jul 2023\r\n"
        "To: " TO_ADDR "\r\n"
        "From: " FROM_ADDR "\r\n"
        "Subject: SMTP example message\r\n"
        "\r\n" /* empty line to divide headers from body, see RFC 5322 */
        "The body of the message starts here.\r\n"
        "\r\n"
        "It could be a lot of lines, could be MIME encoded, whatever.\r\n"
        "Check RFC 5322.\r\n";


struct upload_status {
    size_t bytes_read;
};

static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp) {
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;
    size_t room = size * nmemb;

    if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
        return 0;
    }

    data = &payload_text[upload_ctx->bytes_read];

    if (data) {
        size_t len = strlen(data);
        if (room < len)
            len = room;
        memcpy(ptr, data, len);
        upload_ctx->bytes_read += len;

        return len;
    }

    return 0;
}

int main(void) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx = {0};

    curl = curl_easy_init();
    if (curl) {
        /* Set the URL of your mailserver's SMTP endpoint (Gmail's SMTP server) */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.office365.com:587");

        /* Set the username and password for SMTP authentication */
        curl_easy_setopt(curl, CURLOPT_USERNAME, FROM_ADDR);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "testOutlook12.");

        /* Add recipients */
        recipients = curl_slist_append(recipients, TO_ADDR);
//        recipients = curl_slist_append(recipients, CC_ADDR);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        /* Use the payload_source function to provide the email payload */
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        /* Enable SSL/TLS for secure communication */
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        /* Send the message */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        /* Free the list of recipients */
        curl_slist_free_all(recipients);

        /* Clean up */
        curl_easy_cleanup(curl);
    }

    return (int)res;
}

