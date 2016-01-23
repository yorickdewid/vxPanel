#include "domain_validator.h"
#include "../exceptions.h"

/*

A domain name consists of one or more parts, technically called labels, that are conventionally concatenated, and delimited by dots, such as example.com.

    The right-most label conveys the top-level domain; for example, the domain name www.example.com belongs to the top-level domain com.
    The hierarchy of domains descends from the right to the left label in the name; each label to the left specifies a subdivision, 
    or subdomain of the domain to the right. For example: the label example specifies a node example.com as a subdomain of the com domain, 
    and www is a label to create www.example.com, a subdomain of example.com. This tree of labels may consist of 127 levels.
    Each label may contain from 1 to 63 octets. The empty label is reserved for the root node. 
    
    The full domain name may not exceed a total length of 253 ASCII characters in its textual representation.[5] In practice, some domain registries may have shorter limits.
    A hostname is a domain name that has at least one associated IP address. For example, the domain names www.example.com and example.com are also hostnames, 
    whereas the com domain is not. However, other top-level domains, particularly country code top-level domains, may indeed have an IP address, and if so, they are also hostnames.
    Hostnames impose restrictions on the characters allowed in the corresponding domain name. A valid hostname is also a valid domain name, 
    but a valid domain name may not necessarily be valid as a hostname.


*/


void domain_validator::validate_domain(std::string domain_name)
{
	// a-z 0-9 , on or more '-' and '.'

	std::vector<char> white_list;

	white_list.push_back('a');
	white_list.push_back('b');
	white_list.push_back('c');
	white_list.push_back('d');
	white_list.push_back('e');
	white_list.push_back('f');
	white_list.push_back('g');
	white_list.push_back('h');
	white_list.push_back('i');
	white_list.push_back('j');
	white_list.push_back('k');
	white_list.push_back('l');
	white_list.push_back('m');
	white_list.push_back('n');
	white_list.push_back('o');
	white_list.push_back('p');
	white_list.push_back('q');
	white_list.push_back('r');
	white_list.push_back('s');
	white_list.push_back('t');
	white_list.push_back('u');
	white_list.push_back('v');
	white_list.push_back('w');
	white_list.push_back('x');
	white_list.push_back('y');
	white_list.push_back('z'); // abc

	white_list.push_back('-'); // may appear multiple times even subsequently
	white_list.push_back('.'); // may appeare multiple times but not subsequently

	white_list.push_back('0');
	white_list.push_back('1');
	white_list.push_back('2');
	white_list.push_back('3');
	white_list.push_back('4');
	white_list.push_back('5');
	white_list.push_back('6');
	white_list.push_back('7');
	white_list.push_back('8');
	white_list.push_back('9');

	int count = 0;
	int length = domain_name.size();
	if( length > 253) 
	{
		throw domain_length_ex();
	}

	for( auto it = domain_name.begin(); it != domain_name.end(); ++it )
	{
		bool good = false;
		for( auto w = white_list.begin(); w != white_list.end(); ++w ) {
			if( *it == *w ) {
				good = true;
			}
		}
		if (good) {
			count++;
			continue;
		}
	}

	if( length != count ) {
		throw invalid_domain_ex();
	}
}

