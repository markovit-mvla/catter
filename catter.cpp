#include "util.h"

#define ROCKYOU "/usr/share/wordlists/rockyou.txt"
#define MD5     "MD5"
#define SHA1    "SHA1"
#define NET1    "NetNTLMv1"
#define NET2    "NetNTLMv2"
#define BCRYPT  "bcrypt"

std::map<std::string, uint8_t> htable = 
{
    {"MD5", 0},
    {"SHA1", 100},
    {"NetNTLMv1", 5500},
    {"NetNTLMv2", 5600},
    {"bcrypt", 3200},
};

void hashcat(uint8_t type, std::string hash) {
    std::string com = "hashcat -a 0 -m " + std::to_string(type) + " " + hash + " " + ROCKYOU; 
    exec(com.c_str());
}

int main(void)
{
    std::string id = "hashid ";
    std::string hash;
    std::cout<<"Enter hash: "<<"\n";
    std::cin>>hash;

    std::string com = id.append(hash);
    std::string result = exec(com.c_str());
    if (result.find(MD5))         { hashcat(htable[MD5],  hash);   }
    else if (result.find(SHA1))   { hashcat(htable[SHA1], hash);   }
    else if (result.find(NET1))   { hashcat(htable[NET1], hash);   }
    else if (result.find(NET2))   { hashcat(htable[NET2], hash);   }
    else if (result.find(BCRYPT)) { hashcat(htable[BCRYPT], hash); }

    return 0;
}