#include "util.h"

#define ROCKYOU "/usr/share/wordlists/rockyou.txt"
#define MD5     "MD5"
#define SHA1    "SHA1"
#define NET1    "NetNTLMv1"
#define NET2    "NetNTLMv2"
#define BCRYPT  "bcrypt"

#define DICTIONARY  0
#define PERMUTATION 3
#define HYBRID      6
#define RHYBRID     7

std::map<std::string, uint8_t> htable = 
{
    {"MD5", 0},
    {"SHA1", 100},
    {"NetNTLMv1", 5500},
    {"NetNTLMv2", 5600},
    {"bcrypt", 3200},
};

void hashcat(uint8_t type, uint8_t mode, std::string hash, std::string rule) 
{
    std::string com;
    if (sizeof(rule)/sizeof(std::string)) {
        com = "hashcat -a " + std::to_string(mode) + " -m " + std::to_string(type) + " " + hash + " " + ROCKYOU + " -r " + rule;
    } else {
        com = "hashcat -a " + std::to_string(mode) + " -m " + std::to_string(type) + " " + hash + " " + ROCKYOU; 
    }
    exec(com.c_str());
}

int main(void)
{
    std::string id = "hashid ";

    std::string hash;
    uint8_t mode;
    std::string rule;

    std::cout<<"Enter hash: "<<"\n";
    std::cin>>hash;
    std::cout<<"Enter mode (0 - Dictionary/Rule, 3 - Permutation, 6 - Hybrid, 7 - Hybrid/Rule): "<<"\n";
    std::cin>>mode;
    if (mode == DICTIONARY || mode == RHYBRID) {
        std::cout<<"Optional: Enter path to rule file: ";
        std::cin>>rule;
    }

    std::string com = id.append(hash);
    std::string result = exec(com.c_str());
    if (result.find(MD5))         { hashcat(htable[MD5],  mode, hash, rule);   }
    else if (result.find(SHA1))   { hashcat(htable[SHA1], mode, hash, rule);   }
    else if (result.find(NET1))   { hashcat(htable[NET1], mode, hash, rule);   }
    else if (result.find(NET2))   { hashcat(htable[NET2], mode, hash, rule);   }
    else if (result.find(BCRYPT)) { hashcat(htable[BCRYPT], mode, hash, rule); }

    return 0;
}