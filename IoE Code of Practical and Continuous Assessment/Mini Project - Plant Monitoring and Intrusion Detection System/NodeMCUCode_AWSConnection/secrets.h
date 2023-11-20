#include <pgmspace.h>

#define SECRET
#define THINGNAME " **Your Thing Name on AWS** "

const char WIFI_SSID[] = " **Your SSID/Wifi Name** ";
const char WIFI_PASSWORD[] = " **Your SSID/Wifi Password** ";

const char AWS_IOT_ENDPOINT[] = " **Your AWS EndPoint found in AWS IoT Core/Settings** ";

int8_t TIME_ZONE = -5; //NYC(USA): -5 UTC

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
** ... Your AmazonRootCA1 Certificate **
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
** ... Your Device Certificate **
-----END CERTIFICATE-----

)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
** ... Your RSA Private Key **
-----END RSA PRIVATE KEY-----

)KEY";