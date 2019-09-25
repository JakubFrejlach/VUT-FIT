#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>
#include <regex.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <netinet/if_ether.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <pcap.h>
#include <unistd.h>

#define TCP 1
#define UDP 2
#define MAX_ATTEMPTS_UDP 3
#define MAX_ATTEMPTS_TCP 1
#define SOURCE_PORT 7543
#define PCKT_LEN 8192

using namespace std;

vector<int> handle_ports(char* ports_arg);
int create_socket();
unsigned short check_sum(unsigned short *buf, int nwords);
struct in6_addr convert_IPv6(char *str_address);

string get_domain_address(int ipv_type, char *domain);
string get_interface(string *interface);
string get_source_address(char *interface, int type);

void init_regex(regex_t *regex, char *pattern);
void IP_header(struct ip* header, struct address_data a_data, int type);
void ipv4_process(struct address_data a_data);
void ipv6_process(struct address_data a_data);
void udp_handler(pcap_t *handle, bool *was_received);

struct address_data
{
  vector<int> udp_ports;
  vector<int> tcp_ports;
  string interface;
  string source_address_ipv4;
  string source_address_ipv6;
  string host_ipv4;
  string host_ipv6;
  string domain;
};

struct pseudo_tcp_header
{
  uint32_t src_address;
  uint32_t dst_address;
  uint8_t reserved;
  uint8_t protocol;
  uint16_t len;
};
