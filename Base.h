// Author: Alisa
//Structures C (TLS)

#pragma once
#include <stdlib.h>
// NEW Data Types (use: Handshake struct -> variable "lenght")
typedef struct uint24 { int uint24[3]; } uint24;
typedef struct uint16 { int uint16[2]; } uint16;
typedef struct uint8 { int uint8[1]; } uint8;

//  MAXSIZE = 0xFF (optional in standart (page 9))
typedef enum {
	client_hello = 0x01,
	server_helo = 0x02,
	new_session_ticket = 0x04,
	end_of_early_data = 0x05,
	encrypted_extensions = 0x08,
	setrificate = 0x0B,
	sertificate_request = 0x0D,
	certificate_verify = 0x0F,
	finished = 0x14,
	key_update = 0x18,
	message_hash = 0xFE
} HandshakeType;
//HandshakeType msg_type; (http://cppprosto.blogspot.com/2017/10/cLanguageenum.html)
//msg_type = client_hello; 
typedef struct Handshake {
	HandshakeType msg_type;
	uint24 lenght;
	switch (msg_type) //???????????????????????????
	{
	case client_hello : char* ClientHello;
		break;
	case server_hello : char* ServerHello;
		break;
	case end_of_early_data : char* EndOfEarlyData;
		break;
	case encrypted_extensions : char* encrypted_extensions;
		break;
	case sertificate_request : char* sertificate_request;
		break;
	case certificate_verify : char* certificate_verify;
		break;
	case finished: char* finished;
		break;
	case new_session_ticket : char* new_session_ticket;
		break;
	case key_update : char* key_update;
		break;
	};
} Handshake;

//New Types for ClientHello struct
typedef struct Random { char Random[32]; } Random;
typedef struct ChiperSuite { uint8 ChiperSuite[2]; } ChiperSuite;

typedef enum ExtentionType {
	server_name = 0x0000,
	supported_groups = 0x000A,
	signature_algoritms = 0x000D,
	pre_shared_key = 0x0029,
	supported_versions = 0x002B,
	cookie = 0x002C,
	psk_key_exchange_modes = 0x002D,
	post_handshake_auth = 0x0031,
	signature_algoritms_cert = 0x0032,
	key_share = 0x0033
} ExtentionType;

typedef struct Extension {
	ExtentionType extention_type;
	char* ectantion_dsta; // size is [(2 ^ 16) - 1] ;
} Extension;

struct ClientHello {
	uint16 client_protocol_version; //= 0x0303 for TLS1.2
	Random client_random;
	char* legacy_session_id; //size is [32]; should be equel 0 if TLS1.3
	ChiperSuite* ciper_suites; // size shold be from 2 to 2^16-2 (it should be list???) (Standsrt, page 22)
	char* legasy_compression_methods; // size from 1 to 2^8-1 
	Extension* extensions; //size from 8 to 2^16-1

};

struct ServerHello {
	uint16 server_legasy_version; //= 0x0303 for TLS1.2
	Random server_random;
	char* legaci_session_id_echo;// size is [32] ;
	ChiperSuite supported_ciper_suite;
	uint8 leccasy_compression_metod ;// = 0 (I cant initialize structure field in C)
	Extension* supported_extensions; // size from 6 to 2^16-1
};

struct SupportedVersions {
	HandshakeType msg_type;
	switch (msg_type) {
	case client_hello:
		uint16* versions;// size is [254] ( почему - то не светится тииииппппп АААААААААА...)
	case server_hello:
		uint16* selected_version;
	}
}//?????????
